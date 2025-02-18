import numpy as np
import imageio.v3 as iio
import os
import sys
import glob
from tqdm import tqdm

# --- Configuration ---
IMAGE_FILES = {
    'technical': './obrazy/technical.jpg', # Path from first error log
    'document': './obrazy/document.png',  # Path from second error log
    'photo': './obrazy/color.jpg'         # Path from third error log (assuming you want the jpg)
    # If you specifically want the 800x600 png from the last run:
    # 'photo': './obrazy/color.png'
}
OUTPUT_DIR = './skompresowane/'
# os.makedirs(OUTPUT_DIR, exist_ok=True)

# --- Metadata and Type Handling ---
METADATA_DTYPE = np.int64 # Type for storing header info (num_dims, dtype_num, shape)

# Dictionary to map common dtype numbers back to NumPy types
NUM_TO_DTYPE = {
    # Based on common np.dtype().num values
    np.dtype(np.int8).num: np.int8,     # 0
    np.dtype(np.uint8).num: np.uint8,   # 1
    np.dtype(np.int16).num: np.int16,   # 2 - Error might be here if np.dtype(2) fails directly
    np.dtype(np.uint16).num: np.uint16, # 3 - Or here
    np.dtype(np.int32).num: np.int32,   # 4
    np.dtype(np.uint32).num: np.uint32, # 5
    np.dtype(np.int64).num: np.int64,   # 6
    np.dtype(np.uint64).num: np.uint64, # 7
    np.dtype(np.float16).num: np.float16,# 23 (might differ)
    np.dtype(np.float32).num: np.float32,# 11
    np.dtype(np.float64).num: np.float64,# 12
    # Add bool if needed
    np.dtype(bool).num: bool           # ? (often 0, but handled separately)
}
# Let's refine NUM_TO_DTYPE based on standard numbers:
NUM_TO_DTYPE = {
    0: np.int8, 1: np.uint8,
    2: np.int16, 3: np.uint16, # Standard numbers for 16-bit ints
    4: np.int32, 5: np.uint32,
    6: np.int64, 7: np.uint64,
    11: np.float32, 12: np.float64,
    23: np.float16, # Often 23 for half-precision float
    # Boolean often maps to 0, be careful if distinguishing from int8
    # np.dtype(bool).num might vary. Let's handle bool explicitly if needed.
}


def save_metadata(data_shape, data_dtype):
    """Creates a metadata header array: [num_dims, dtype_num, dim1, dim2, ...]"""
    shape_list = list(data_shape)
    dtype_number = data_dtype.num
    metadata_header = np.array([len(shape_list), dtype_number] + shape_list, dtype=METADATA_DTYPE)
    return metadata_header

def load_metadata(compressed_with_meta):
    """Extracts original shape, dtype, and data start index from combined array."""
    if not isinstance(compressed_with_meta, np.ndarray) or compressed_with_meta.size < 2:
         raise ValueError("Invalid or empty compressed data for metadata loading.")

    # Assume the header part can be read as METADATA_DTYPE
    try:
        num_dims = int(compressed_with_meta[0])
        dtype_num = int(compressed_with_meta[1])
    except (IndexError, ValueError):
        raise ValueError("Could not read initial metadata (num_dims, dtype_num).")

    # --- FIX: Use the mapping ---
    original_dtype = NUM_TO_DTYPE.get(dtype_num)
    if original_dtype is None:
        # Handle boolean separately? np.bool_ often has num=0 like np.int8
        if dtype_num == np.dtype(bool).num:
             original_dtype = bool
        else:
             raise TypeError(f"Cannot interpret dtype number '{dtype_num}' read from metadata. Unknown type.")

    header_len = 2 + num_dims
    if num_dims < 0 or header_len > len(compressed_with_meta):
         raise ValueError(f"Invalid number of dimensions ({num_dims}) or metadata length derived from header.")

    original_shape = tuple(int(x) for x in compressed_with_meta[2:header_len])
    data_start_index = header_len
    return original_shape, original_dtype, data_start_index

# --- RLE Implementation ---
RLE_ARRAY_DTYPE = np.int64 # Must hold counts and values

def rle_encode(data: np.ndarray):
    """Encodes a NumPy array using Run-Length Encoding."""
    metadata_header = save_metadata(data.shape, data.dtype)

    if data.size == 0:
        return metadata_header.astype(RLE_ARRAY_DTYPE)

    flat_data = data.flatten()
    encoded_list = []

    if flat_data.size == 0:
         return metadata_header.astype(RLE_ARRAY_DTYPE)

    count = 1
    current_val = flat_data[0]
    for i in tqdm(range(1, flat_data.size), desc="RLE Encoding", leave=False, unit="pixels"):
        if flat_data[i] == current_val and count < np.iinfo(RLE_ARRAY_DTYPE).max : # Prevent count overflow within the loop
            count += 1
        else:
            encoded_list.extend([count, current_val])
            current_val = flat_data[i]
            count = 1
    encoded_list.extend([count, current_val])

    encoded_array = np.array(encoded_list, dtype=RLE_ARRAY_DTYPE)
    combined = np.concatenate((metadata_header.astype(RLE_ARRAY_DTYPE), encoded_array))
    return combined

def rle_decode(compressed_data: np.ndarray):
    """Decodes RLE encoded data back into a NumPy array with original shape."""
    if compressed_data.size <= 1 :
         raise ValueError("Compressed data too small to contain metadata.")

    original_shape, original_dtype, data_start_index = load_metadata(compressed_data)
    encoded_part = compressed_data[data_start_index:]

    if len(encoded_part) % 2 != 0:
        raise ValueError("Invalid RLE data: odd number of elements.")

    decoded_list = []
    total_decoded_size = 0 # Keep track of expected size
    for i in tqdm(range(0, len(encoded_part), 2), desc="RLE Decoding", leave=False, unit="runs"):
        count = int(encoded_part[i])
        value = encoded_part[i+1] # Keep value in RLE_ARRAY_DTYPE for now
        if count < 0 :
            raise ValueError(f"Invalid RLE count encountered: {count}")
        decoded_list.extend([value] * count)
        total_decoded_size += count # Increment expected size

    # Verify size *before* creating the final array if possible
    expected_size = np.prod(original_shape)
    if total_decoded_size != expected_size:
         raise ValueError(f"Decoded element count {total_decoded_size} does not match expected size {expected_size} from shape {original_shape}")

    # Convert list to NumPy array using the ORIGINAL dtype
    decoded_array = np.array(decoded_list, dtype=original_dtype)

    # Reshape (size check already done)
    try:
        reshaped_array = decoded_array.reshape(original_shape)
    except ValueError as e:
         raise ValueError(f"Reshape failed. Decoded size {decoded_array.size}, expected {expected_size}, target shape {original_shape}. Original error: {e}")

    return reshaped_array


# --- ByteRun Implementation ---
BYTERUN_ARRAY_DTYPE = np.int16 # Should hold int8 controls and uint8 data

def find_runs(flat_data, start_index, max_len=128):
    n = len(flat_data)
    if start_index >= n:
        return 0, 0

    repeat_len = 1
    val = flat_data[start_index]
    for i in range(start_index + 1, min(start_index + max_len, n)):
        if flat_data[i] == val:
            repeat_len += 1
        else:
            break

    literal_len = 0
    if start_index < n:
        literal_len = 1
        for i in range(start_index + 1, min(start_index + max_len, n)):
             # More robust check for end of literal run: stop if *next* element starts a repeat of length >= 2
            is_repeat_next = False
            if i + 1 < n and flat_data[i] == flat_data[i+1]:
                is_repeat_next = True # Potential repeat of length >= 2 starts at i

            if is_repeat_next:
                break # End literal run *before* the repeat starts

            # Otherwise, continue the literal run
            literal_len += 1

    return literal_len, repeat_len


def byterun_encode(data: np.ndarray):
    metadata_header = save_metadata(data.shape, data.dtype)

    if data.size == 0:
        return metadata_header.astype(BYTERUN_ARRAY_DTYPE)

    flat_data = data.flatten()
    encoded_list = []
    n = flat_data.size
    i = 0

    pbar = tqdm(total=n, desc="ByteRun Encoding", leave=False, unit="pixels")

    while i < n:
        literal_len, repeat_len = find_runs(flat_data, i)

        # Heuristic: Prefer repeat run if length is 2 or more
        if repeat_len >= 2:
            run_len_to_encode = repeat_len
            while run_len_to_encode > 0:
                chunk_len = min(run_len_to_encode, 128)
                control_byte = -(chunk_len - 1)
                encoded_list.append(control_byte)
                encoded_list.append(flat_data[i])
                run_len_to_encode -= chunk_len
            i += repeat_len
            pbar.update(repeat_len)
        else:
            # Literal run: ensure literal_len from find_runs is used correctly
            # Need to ensure we don't create empty literal runs
            run_len_to_encode = literal_len # Use the calculated literal len
            if run_len_to_encode == 0 and i < n: # Should not happen if find_runs is correct, but safety
                run_len_to_encode = 1

            current_chunk_start = i
            while run_len_to_encode > 0:
                chunk_len = min(run_len_to_encode, 128)
                control_byte = chunk_len - 1
                encoded_list.append(control_byte)
                encoded_list.extend(flat_data[current_chunk_start : current_chunk_start + chunk_len])
                run_len_to_encode -= chunk_len
                current_chunk_start += chunk_len # Advance chunk start
            i += literal_len # Advance main index by the total literal length processed
            pbar.update(literal_len)

    pbar.close()

    encoded_array = np.array(encoded_list, dtype=BYTERUN_ARRAY_DTYPE)
    combined = np.concatenate((metadata_header.astype(BYTERUN_ARRAY_DTYPE), encoded_array))
    return combined


def byterun_decode(compressed_data: np.ndarray):
    if compressed_data.size <= 1 :
         raise ValueError("Compressed data too small to contain metadata.")

    original_shape, original_dtype, data_start_index = load_metadata(compressed_data)
    encoded_part = compressed_data[data_start_index:]

    decoded_list = []
    i = 0
    n_encoded = len(encoded_part)
    total_decoded_size = 0

    pbar = tqdm(total=n_encoded, desc="ByteRun Decoding", leave=False, unit="bytes")

    while i < n_encoded:
        control_byte = int(encoded_part[i])
        i += 1
        pbar.update(1)

        if control_byte >= 0: # Literal run
            run_len = control_byte + 1
            if i + run_len > n_encoded:
                 raise ValueError(f"ByteRun decode error: Literal run of length {run_len} exceeds data bounds at index {i}.")
            chunk = encoded_part[i : i + run_len]
            decoded_list.extend(chunk)
            total_decoded_size += run_len
            i += run_len
            pbar.update(run_len)
        else: # Repeat run
            run_len = -control_byte + 1
            if i >= n_encoded:
                 raise ValueError(f"ByteRun decode error: Repeat run control byte {control_byte} found at end of data.")
            value = encoded_part[i]
            decoded_list.extend([value] * run_len)
            total_decoded_size += run_len
            i += 1
            pbar.update(1)

    pbar.close()

    # Verify size *before* creating the final array
    expected_size = np.prod(original_shape)
    if total_decoded_size != expected_size:
         raise ValueError(f"Decoded element count {total_decoded_size} does not match expected size {expected_size} from shape {original_shape}")

    decoded_array = np.array(decoded_list, dtype=original_dtype)

    # Reshape (size check already done)
    try:
        reshaped_array = decoded_array.reshape(original_shape)
    except ValueError as e:
         raise ValueError(f"Reshape failed. Decoded size {decoded_array.size}, expected {expected_size}, target shape {original_shape}. Original error: {e}")

    return reshaped_array

# --- Metrics Calculation ---
def calculate_metrics(original_data: np.ndarray, compressed_array: np.ndarray):
    """Calculates CR and PR based on .nbytes"""
    original_size = original_data.nbytes
    if not isinstance(compressed_array, np.ndarray):
         compressed_size = sys.getsizeof(compressed_array)
    else:
         compressed_size = compressed_array.nbytes

    if original_size == 0: return 0, 100.0
    if compressed_size == 0: return float('inf'), 0.0

    cr = original_size / compressed_size
    pr = (compressed_size / original_size) * 100.0
    return cr, pr

# --- Main Execution ---
def main():
    results = {}
    original_sizes = {}

    for category, img_path in IMAGE_FILES.items():
        print(f"\n--- Processing: {category} image ({os.path.basename(img_path)}) ---")
        if not os.path.exists(img_path):
            print(f"ERROR: Image file not found: {img_path}")
            continue
        try:
            original_image = iio.imread(img_path)
            # Optional: Force uint8 if needed, but metadata should handle original type now
            # if original_image.dtype != np.uint8:
            #    original_image = original_image.astype(np.uint8) # Add proper scaling/clipping if used

            print(f"  Original shape: {original_image.shape}, dtype: {original_image.dtype}, size: {original_image.nbytes} bytes")
            original_sizes[category] = original_image.nbytes
            results[category] = {}

            # --- RLE Test ---
            print("  Testing RLE...")
            rle_compressed = rle_encode(original_image.copy()) # Use copy to be safe
            rle_decoded = rle_decode(rle_compressed)

            rle_lossless = np.array_equal(original_image, rle_decoded)
            print(f"  RLE Lossless: {rle_lossless}")
            if not rle_lossless:
                 print("  ERROR: RLE Decompression failed verification!")
                 print(f"  Original shape: {original_image.shape}, Decoded shape: {rle_decoded.shape}")

            rle_cr, rle_pr = calculate_metrics(original_image, rle_compressed)
            print(f"  RLE Compressed size: {rle_compressed.nbytes} bytes")
            print(f"  RLE CR: {rle_cr:.4f}, PR: {rle_pr:.2f}%")
            results[category]['RLE'] = {'lossless': rle_lossless, 'size': rle_compressed.nbytes, 'cr': rle_cr, 'pr': rle_pr}

            # --- ByteRun Test ---
            print("  Testing ByteRun...")
            byterun_compressed = byterun_encode(original_image.copy()) # Use copy
            byterun_decoded = byterun_decode(byterun_compressed)

            byterun_lossless = np.array_equal(original_image, byterun_decoded)
            print(f"  ByteRun Lossless: {byterun_lossless}")
            if not byterun_lossless:
                 print("  ERROR: ByteRun Decompression failed verification!")
                 print(f"  Original shape: {original_image.shape}, Decoded shape: {byterun_decoded.shape}")

            byterun_cr, byterun_pr = calculate_metrics(original_image, byterun_compressed)
            print(f"  ByteRun Compressed size: {byterun_compressed.nbytes} bytes")
            print(f"  ByteRun CR: {byterun_cr:.4f}, PR: {byterun_pr:.2f}%")
            results[category]['ByteRun'] = {'lossless': byterun_lossless, 'size': byterun_compressed.nbytes, 'cr': byterun_cr, 'pr': byterun_pr}


        except Exception as e:
            print(f"ERROR processing {category} image: {e}")
            import traceback
            traceback.print_exc()

    # --- Print Summary Table ---
    print("\n--- Compression Results Summary ---")
    print(f"{'Category':<12} {'Algorithm':<10} {'Lossless':<10} {'Orig Size (B)':>15} {'Comp Size (B)':>15} {'CR':>10} {'PR (%)':>10}")
    print("-" * 75)
    for category, methods in results.items():
        orig_size_bytes = original_sizes.get(category, -1)
        for algo, metrics in methods.items():
            lossless = metrics.get('lossless', 'N/A')
            comp_size = metrics.get('size', -1)
            cr = metrics.get('cr', float('nan'))
            pr = metrics.get('pr', float('nan'))
            print(f"{category:<12} {algo:<10} {str(lossless):<10} {orig_size_bytes:>15} {comp_size:>15} {cr:>10.4f} {pr:>10.2f}")
    print("-" * 75)

if __name__ == "__main__":
    main()