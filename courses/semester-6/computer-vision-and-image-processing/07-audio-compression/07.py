import numpy as np
import scipy.io.wavfile as wav
import os
import sys
import glob
from tqdm import tqdm # Progress bars are nice

AUDIO_DIR = './Pliki_Sing/'
EPS = np.finfo(np.float32).eps

def quantize_float(signal, bits):
    """ Simulates quantizing a float signal [-1, 1] to a specific number of bits. """
    if bits < 1:
        raise ValueError("Number of bits must be at least 1.")
    if bits >= 32: # Practically no quantization for float32/64
        return signal.astype(np.float32) # Just ensure float32

    levels = 2**bits
    scaled_signal = ((signal + 1.0) / 2.0) * (levels - 1)
    quantized_levels = np.round(scaled_signal)
    quantized_signal = ((quantized_levels / (levels - 1)) * 2.0) - 1.0
    quantized_signal = np.clip(quantized_signal, -1.0, 1.0)
    return quantized_signal.astype(np.float32)


def alaw_compress(x, A=87.6):
    """ Applies A-law compression to signal x in range [-1, 1]. Vectorized. """
    abs_x = np.abs(x)
    lnA = np.log(A) # Precalculate ln(A)
    y = np.zeros_like(x, dtype=np.float32)

    idx_low = abs_x < (1.0 / A)
    y[idx_low] = np.sign(x[idx_low]) * (A * abs_x[idx_low]) / (1.0 + lnA)

    idx_high = ~idx_low # Faster than recalculating the condition
    y[idx_high] = np.sign(x[idx_high]) * (1.0 + np.log(A * abs_x[idx_high] + EPS)) / (1.0 + lnA)

    return y

def alaw_expand(y, A=87.6):
    """ Applies A-law expansion to signal y in range [-1, 1]. Vectorized. """
    abs_y = np.abs(y)
    lnA = np.log(A) # Precalculate ln(A)
    x = np.zeros_like(y, dtype=np.float32)
    one_plus_lnA = 1.0 + lnA # Precalculate

    idx_low = abs_y < (1.0 / one_plus_lnA)
    x[idx_low] = np.sign(y[idx_low]) * (abs_y[idx_low] * one_plus_lnA) / A

    idx_high = ~idx_low
    x[idx_high] = np.sign(y[idx_high]) * (np.exp(abs_y[idx_high] * one_plus_lnA - 1.0)) / A

    return x

def mulaw_compress(x, mu=255.0):
    """ Applies µ-law compression to signal x in range [-1, 1]. Vectorized. """
    return np.sign(x) * np.log(1.0 + mu * np.abs(x) + EPS) / np.log(1.0 + mu + EPS)

def mulaw_expand(y, mu=255.0):
    """ Applies µ-law expansion to signal y in range [-1, 1]. Vectorized. """
    return np.sign(y) * (1.0 / mu) * ((1.0 + mu)**np.abs(y) - 1.0)


def dpcm_no_predict_encode(x, quantizer_func, bits):
    """ Encodes signal x using DPCM without prediction, quantizing difference. """
    y = np.zeros_like(x, dtype=np.float32) # Stores quantized differences
    e = np.zeros_like(x, dtype=np.float32) # Stores reconstructed signal based on quantized diff
    e_prev = 0.0 # Initial estimate/previous reconstructed value
    for i in tqdm(range(len(x)), desc="DPCM NoPred Encode", leave=False, unit="samples"):
        diff = x[i] - e_prev      # Calculate difference from previous reconstruction
        y[i] = quantizer_func(diff, bits) # Quantize the difference
        e[i] = y[i] + e_prev      # Reconstruct current sample using quantized difference
        e_prev = e[i]             # Update previous reconstruction for next step
    return y # Return the stream of quantized differences

def dpcm_no_predict_decode(y):
    """ Decodes a DPCM signal (quantized differences) without prediction. """
    x_rec = np.zeros_like(y, dtype=np.float32) # Stores reconstructed signal
    e_prev = 0.0 # Initial estimate/previous reconstructed value
    for i in tqdm(range(len(y)), desc="DPCM NoPred Decode", leave=False, unit="samples"):
        x_rec[i] = y[i] + e_prev # Reconstruct by adding quantized diff to previous reconstruction
        e_prev = x_rec[i]        # Update previous reconstruction
    return x_rec

def dpcm_simple_predict_encode(x, quantizer_func, bits):
    """ Encodes signal x using DPCM with previous sample prediction. """
    y = np.zeros_like(x, dtype=np.float32) # Stores quantized differences
    e = 0.0 # Prediction (initialized to 0) / Last reconstructed value
    for i in tqdm(range(len(x)), desc="DPCM SimplePred Encode", leave=False, unit="samples"):
        diff = x[i] - e           # Difference from prediction
        y[i] = quantizer_func(diff, bits) # Quantize the difference
        x_rec = y[i] + e          # Reconstruct current sample
        e = x_rec                 # Update prediction to be the last reconstructed value
    return y

def dpcm_simple_predict_decode(y):
    """ Decodes a DPCM signal with previous sample prediction. """
    x_rec = np.zeros_like(y, dtype=np.float32)
    e = 0.0 # Prediction (initialized to 0) / Last reconstructed value
    for i in tqdm(range(len(y)), desc="DPCM SimplePred Decode", leave=False, unit="samples"):
        x_rec[i] = y[i] + e       # Reconstruct current sample
        e = x_rec[i]              # Update prediction
    return x_rec

def load_and_normalize(filepath):
    """ Loads a WAV file and normalizes it to float32 [-1, 1]. """
    try:
        fs, data = wav.read(filepath)
        print(f"  Loaded '{os.path.basename(filepath)}': Fs={fs}, Shape={data.shape}, dtype={data.dtype}")

        # Handle stereo -> mono (take first channel)
        if data.ndim > 1:
            print("    Converting stereo to mono (using first channel).")
            data = data[:, 0]

        if data.dtype == np.int16:
            norm_factor = np.iinfo(np.int16).max
        elif data.dtype == np.int8:
            norm_factor = np.iinfo(np.int8).max
        elif data.dtype == np.uint8:
            data = data.astype(np.float32) - 128.0
            norm_factor = 128.0
        elif data.dtype == np.float32:
             norm_factor = 1.0 # Assume already in range if float32
        elif data.dtype == np.int32:
             norm_factor = np.iinfo(np.int32).max # Handle int32 if necessary
        else:
            print(f"    Warning: Unsupported dtype {data.dtype}. Attempting direct float conversion.")
            norm_factor = np.max(np.abs(data))
            if norm_factor < EPS: norm_factor = 1.0 # Avoid division by zero for silence

        signal_float = data.astype(np.float32) / norm_factor
        signal_float = np.clip(signal_float, -1.0, 1.0)

        return fs, signal_float

    except FileNotFoundError:
        print(f"ERROR: File not found - {filepath}")
        return None, None
    except Exception as e:
        print(f"ERROR loading/normalizing {filepath}: {e}")
        return None, None

def analyze_compression(filepath, bits_to_test=[8, 7, 6, 5, 4, 3, 2]):
    """ Runs all compression methods for various bit depths and stores results (simulated). """
    fs, signal = load_and_normalize(filepath)
    if signal is None:
        return None

    results = {} # Store results like { algo: { bits: quality_description } }

    print(f"\n--- Analyzing {os.path.basename(filepath)} ---")

    print("  Processing A-law...")
    results['A-law'] = {}
    compressed_alaw = alaw_compress(signal)
    for bits in bits_to_test:
        quantized_alaw = quantize_float(compressed_alaw, bits) # Simulate quantization
        expanded_alaw = alaw_expand(quantized_alaw)
        results['A-law'][bits] = "Processed"
        print(f"    A-law @ {bits} bits: Processed")

    print("  Processing µ-law...")
    results['mu-law'] = {}
    compressed_mulaw = mulaw_compress(signal)
    for bits in bits_to_test:
        quantized_mulaw = quantize_float(compressed_mulaw, bits) # Simulate quantization
        expanded_mulaw = mulaw_expand(quantized_mulaw)
        results['mu-law'][bits] = "Processed"
        print(f"    µ-law @ {bits} bits: Processed")

    print("  Processing DPCM (No Prediction)...")
    results['DPCM_NoPred'] = {}
    for bits in bits_to_test:
        encoded_diffs_np = dpcm_no_predict_encode(signal, quantize_float, bits)
        reconstructed_np = dpcm_no_predict_decode(encoded_diffs_np)
        results['DPCM_NoPred'][bits] = "Processed"
        print(f"    DPCM NoPred @ {bits} bits: Processed")

    print("  Processing DPCM (Simple Prediction)...")
    results['DPCM_SimplePred'] = {}
    for bits in bits_to_test:
        encoded_diffs_sp = dpcm_simple_predict_encode(signal, quantize_float, bits)
        reconstructed_sp = dpcm_simple_predict_decode(encoded_diffs_sp)
        results['DPCM_SimplePred'][bits] = "Processed"
        print(f"    DPCM SimplePred @ {bits} bits: Processed")

    print(f"--- Analysis finished for {os.path.basename(filepath)} ---")
    return results # Returning results dictionary, though it's just placeholders now

if __name__ == "__main__":
    files_low = sorted(glob.glob(os.path.join(AUDIO_DIR, 'sing_low*.wav')))
    files_medium = sorted(glob.glob(os.path.join(AUDIO_DIR, 'sing_medium*.wav')))
    files_high = sorted(glob.glob(os.path.join(AUDIO_DIR, 'sing_high*.wav')))

    files_to_process = []
    if files_low: files_to_process.append(files_low[0])
    if files_medium: files_to_process.append(files_medium[0])
    if files_high: files_to_process.append(files_high[0])

    if not files_to_process:
        print(f"ERROR: No suitable sing_*.wav files found in '{AUDIO_DIR}'")
        print("Please ensure the directory exists and contains audio files.")
        sys.exit(1)

    print(f"Found files to process: {[os.path.basename(f) for f in files_to_process]}")

    all_results = {}
    for filepath in files_to_process:
        analyze_compression(filepath)

    print("\n--- Script finished ---")
    print("NOTE: This script simulates quantization effects.")
    print("Actual audio quality assessment requires listening to the reconstructed audio.")
    print("The 'results' dictionary returned by analyze_compression is currently just a placeholder.")