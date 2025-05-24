Pimport numpy as np
import scipy.io.wavfile as wav
from scipy.interpolate import interp1d
import matplotlib.pyplot as plt
import glob
import os
import math
import warnings

# --- Configuration ---
INPUT_SIN_DIR = './SOUND_SIN/SIN/'  # Directory with sin_*.wav files
INPUT_SING_DIR = './SOUND_SING/' # Directory with sing_*.wav files (for listening)
OUTPUT_PLOT_DIR = './images/SING'   # Directory to save generated plots
TIME_SEGMENT_MS = 100           # Duration of time segment to plot (in ms)
EPS = np.finfo(np.float32).eps  # Epsilon for dB calculation

# --- Quantization Function ---
def Kwant(data, bit):
    """
    Simulates quantization of 'data' signal to 'bit' bits.
    Handles int and float types, automatically detecting range for common cases.
    """
    if not (2 <= bit <= 32):
        raise ValueError("Bit depth must be between 2 and 32")

    input_dtype = data.dtype
    data_float = data.astype(np.float64) # Use float64 for calculations

    if np.issubdtype(input_dtype, np.integer):
        info = np.iinfo(input_dtype)
        m = info.min
        n = info.max
        range_val = n - m
        if range_val == 0: # Handle case where min == max (e.g., silent file)
            return data # Return original data if range is zero
    elif np.issubdtype(input_dtype, np.floating):
        # Try to determine common float ranges
        min_val, max_val = np.min(data_float), np.max(data_float)
        if min_val >= -1.01 and max_val <= 1.01 and min_val < -0.01 : # Check approx <-1, 1>
             m = -1.0
             n = 1.0
        elif min_val >= -0.01 and max_val <= 1.01: # Check approx <0, 1>
             m = 0.0
             n = 1.0
        else:
             warnings.warn(f"Unknown float range [{min_val:.2f}, {max_val:.2f}]. Assuming [-1, 1]. Quantization might be incorrect.")
             m = -1.0
             n = 1.0
        range_val = n - m
        if abs(range_val) < EPS:
             return data # Return original data if range is effectively zero
    else:
        raise TypeError(f"Unsupported data type: {input_dtype}")

    # Number of quantization levels (max value for the target bit depth)
    levels = 2**bit
    d = levels - 1 # Max value after scaling to <0, d>

    # --- Steps ---
    # 1. Normalize to <0, 1>
    # Ensure we handle the range correctly, especially for integers
    if np.issubdtype(input_dtype, np.integer):
        # Correct integer normalization: (value - min) / (max - min + 1) is wrong for levels
        # We map min to 0 and max to d
        data_norm = (data_float - m) / range_val # Maps to approx <0, 1>
    else: # Float
        data_norm = (data_float - m) / range_val # Maps exactly to <0, 1>

    # Clamp data_norm to [0, 1] to avoid issues due to precision or range assumption
    data_norm = np.clip(data_norm, 0.0, 1.0)

    # 2. Scale to <0, d>
    data_scaled = data_norm * d

    # 3. Round to nearest integer level
    data_rounded = np.round(data_scaled)

    # 4. Scale back to <0, 1> based on quantized levels
    data_norm_quant = data_rounded / d

    # 5. Scale back to original range <m, n>
    data_quant_float = data_norm_quant * range_val + m

    # 6. Convert back to original dtype (or appropriate float type)
    if np.issubdtype(input_dtype, np.integer):
        # Clamp before converting to int to prevent wrap-around/errors
        data_quant_final = np.clip(data_quant_float, m, n).astype(input_dtype)
    else:
        data_quant_final = data_quant_float.astype(input_dtype) # Keep float type

    return data_quant_final

# --- Decimation Function ---
def Decimate(data, fs, n):
    """Decimates the signal by factor n."""
    if n <= 0:
        raise ValueError("Decimation factor n must be positive")
    if n == 1:
        return data, fs # No change
    y_dec = data[::n]
    fs_new = fs / n
    return y_dec, fs_new

# --- Interpolation Function ---
def Interpolate(data, fs, fs_new, kind='linear'):
    """Interpolates the signal to a new sampling rate fs_new."""
    if fs_new <= 0:
        raise ValueError("New sampling rate must be positive")
    if fs == fs_new:
        return data, fs # No change

    N = len(data)
    duration = N / fs
    t_original = np.linspace(0, duration, N, endpoint=False) # Original time vector

    N_new = int(N * fs_new / fs) # Calculate new number of samples
    t_new = np.linspace(0, duration, N_new, endpoint=False) # New time vector

    # Ensure input data type compatibility with interp1d
    data_interp_input = data.astype(np.float64)

    try:
        interp_func = interp1d(t_original, data_interp_input, kind=kind, fill_value="extrapolate", bounds_error=False)
        y_interp = interp_func(t_new)
    except ValueError as e:
         warnings.warn(f"Interpolation failed ({kind}, {fs} -> {fs_new} Hz): {e}. Returning empty array.")
         return np.array([], dtype=data.dtype), fs_new # Return empty on error

    # Convert back to original data type (or appropriate type)
    if np.issubdtype(data.dtype, np.integer):
        # Need to handle potential clipping if interpolation goes out of bounds
        info = np.iinfo(data.dtype)
        y_interp_final = np.clip(y_interp, info.min, info.max).astype(data.dtype)
    else:
        y_interp_final = y_interp.astype(data.dtype)

    return y_interp_final, fs_new

# --- Plotting Function ---
def PlotSignalAndSpectrum(y, fs, title_suffix, base_filename, segment_ms=TIME_SEGMENT_MS):
    """Generates and saves a plot of the signal segment and its spectrum."""
    N = len(y)
    if N == 0:
        print(f"Skipping plot for {base_filename}_{title_suffix} - Empty signal")
        return

    fig, axs = plt.subplots(2, 1, figsize=(10, 6))
    fig.suptitle(f'{base_filename} - {title_suffix}', y=0.98) # Adjust title position

    # -- Time Domain Plot --
    samples_in_segment = min(N, int(segment_ms * fs / 1000))
    if samples_in_segment < 2: # Need at least 2 samples to plot a line
        samples_in_segment = min(N, 2)
        warnings.warn(f"Time segment too short for plotting {base_filename}_{title_suffix}. Showing first {samples_in_segment} samples.")


    time_axis = np.arange(samples_in_segment) / fs * 1000 # Time in ms

    axs[0].plot(time_axis, y[:samples_in_segment])
    axs[0].set_title(f'Time Domain (First {segment_ms} ms or less)')
    axs[0].set_xlabel('Time [ms]')
    axs[0].set_ylabel('Amplitude')
    axs[0].grid(True)

    # -- Frequency Domain Plot --
    # Ensure we handle potential Nyquist issues after modifications
    nyquist = fs / 2

    try:
        # Use the full signal for FFT
        yf = np.fft.fft(y.astype(np.float64)) # Use float64 for FFT
        xf = np.fft.fftfreq(N, 1 / fs)

        # Keep only positive frequencies
        pos_mask = (xf >= 0) & (xf <= nyquist)
        xf_pos = xf[pos_mask]
        yf_pos_mag = np.abs(yf[pos_mask])

        # Convert magnitude to dB (handle log(0))
        yf_db = 20 * np.log10(yf_pos_mag + EPS) # Add epsilon

        axs[1].plot(xf_pos, yf_db)
        axs[1].set_title('Frequency Domain (Spectrum)')
        axs[1].set_xlabel('Frequency [Hz]')
        axs[1].set_ylabel('Magnitude [dB]')
        axs[1].set_xlim(0, nyquist) # Show up to Nyquist frequency
        # Try to set a sensible y-axis limit, e.g., based on max dB
        if len(yf_db) > 0:
           max_db = np.max(yf_db)
           axs[1].set_ylim(max(max_db - 100, np.min(yf_db) -10), max_db + 5) # Show range below max
        axs[1].grid(True)

    except Exception as e:
         axs[1].set_title(f'Frequency Domain (Error: {e})')
         print(f"Error plotting spectrum for {base_filename}_{title_suffix}: {e}")


    plt.tight_layout(rect=[0, 0.03, 1, 0.95]) # Adjust layout to prevent title overlap
    plot_filename = os.path.join(OUTPUT_PLOT_DIR, f'{base_filename}_{title_suffix}.png')
    plt.savefig(plot_filename)
    plt.close(fig)
    print(f'Saved plot: {plot_filename}')

# --- Main Processing Logic ---
def main():
    # Create output directory if it doesn't exist
    os.makedirs(OUTPUT_PLOT_DIR, exist_ok=True)

    # Get list of sin_ files
    sin_files = sorted(glob.glob(os.path.join(INPUT_SIN_DIR, 'sin_*.wav')))
    if not sin_files:
        print(f"Error: No 'sin_*.wav' files found in '{INPUT_SIN_DIR}'")
        return

    print(f"Found {len(sin_files)} sin files to process: {sin_files}")

    # Define modifications
    quant_bits = [4, 8, 16, 24]
    decim_factors = [2, 4, 6, 10, 24]
    interp_freqs = [2000, 4000, 8000, 11999, 16000, 16953, 24000, 41000]
    interp_kinds = ['linear', 'cubic'] # 'cubic' represents non-linear

    for filepath in sin_files:
        base_filename = os.path.splitext(os.path.basename(filepath))[0]
        print(f"\n--- Processing: {base_filename} ---")

        try:
            fs_orig, data_orig = wav.read(filepath)
            # Optional: Convert to a standard type like int32 if needed, but be careful
            # if data_orig.dtype == np.int16:
            #     data_orig = data_orig.astype(np.int32) * (2**16) # Example scaling
            # elif data_orig.dtype == np.uint8: # PCM standard is often signed
            #      data_orig = (data_orig.astype(np.int32) - 128) * (2**24) # Example scaling

            print(f"  Original Fs: {fs_orig} Hz, Shape: {data_orig.shape}, dtype: {data_orig.dtype}")
            if len(data_orig.shape) > 1:
                 print("  Warning: Stereo file detected. Processing only the first channel.")
                 data_orig = data_orig[:, 0] # Process only the left channel

            # --- Original Signal Plot ---
            PlotSignalAndSpectrum(data_orig, fs_orig, "original", base_filename)


            # --- Apply Quantization ---
            print("  Applying Quantization...")
            for bits in quant_bits:
                print(f"    Quantizing to {bits} bits...")
                try:
                    if np.issubdtype(data_orig.dtype, np.integer) and bits > np.iinfo(data_orig.dtype).bits:
                         print(f"    Skipping quantization to {bits} bits: requested bits > original bits ({np.iinfo(data_orig.dtype).bits})")
                         continue
                    elif np.issubdtype(data_orig.dtype, np.floating) and bits == 32: # Approx float32
                         print(f"    Skipping quantization to {bits} bits: similar to original float32")
                         continue

                    data_quant = Kwant(data_orig, bits)
                    title = f"quant_{bits}bit"
                    # Spectrum depends on Fs, Data shape for FFT and sample values for magnitude
                    PlotSignalAndSpectrum(data_quant, fs_orig, title, base_filename)
                except Exception as e:
                    print(f"    ERROR quantizing to {bits} bits: {e}")

            # --- Apply Decimation ---
            print("  Applying Decimation...")
            for n in decim_factors:
                print(f"    Decimating by factor {n}...")
                try:
                    data_dec, fs_dec = Decimate(data_orig, fs_orig, n)
                    if len(data_dec) < 2:
                         print(f"    Skipping decimation n={n}: Resulting signal too short.")
                         continue
                    title = f"decim_n{n}"
                    PlotSignalAndSpectrum(data_dec, fs_dec, title, base_filename)
                except Exception as e:
                    print(f"    ERROR decimating by factor {n}: {e}")

            # --- Apply Interpolation ---
            print("  Applying Interpolation...")
            for fs_new in interp_freqs:
                # Check if new fs is significantly different
                 if abs(fs_new - fs_orig) < 1:
                     print(f"    Skipping interpolation to {fs_new} Hz: Too close to original Fs {fs_orig} Hz")
                     continue
                 # Basic check for Nyquist violation before interpolation attempt
                 if fs_new < 2 * (fs_orig / 2): # Check if new Fs can represent original bandwidth
                     pass # Allow downsampling, but be aware of aliasing potential

                 print(f"    Interpolating to {fs_new} Hz...")
                 for kind in interp_kinds:
                    print(f"      Kind: {kind}...")
                    try:
                        data_interp, fs_interp = Interpolate(data_orig, fs_orig, fs_new, kind=kind)
                        if len(data_interp) < 2:
                             print(f"      Skipping interpolation ({kind}, {fs_new} Hz): Resulting signal too short.")
                             continue
                        title = f"interp_{kind}_{fs_new}Hz"
                        PlotSignalAndSpectrum(data_interp, fs_interp, title, base_filename)
                    except Exception as e:
                        print(f"      ERROR interpolating ({kind}, {fs_new} Hz): {e}")

        except FileNotFoundError:
            print(f"Error: File not found - {filepath}")
        except Exception as e:
            print(f"Error processing file {filepath}: {e}")

    print("\nProcessing finished.")

if __name__ == "__main__":
    main()