import numpy as np
import scipy.fftpack # For DCT/IDCT
import cv2 # For color conversion (easier than manual)
import imageio.v3 as iio
import os
import math
import matplotlib.pyplot as plt
import sys # Import sys for exit calls

# --- Configuration ---
# ADD PATHS TO YOUR 4 LARGE TEST IMAGES HERE
IMAGE_PATHS = [
    './obrazy_jpeg/1.jpeg', # Replace with your actual image paths
    './obrazy_jpeg/2.jpeg',
    './obrazy_jpeg/3.jpeg',
    './obrazy_jpeg/4.jpeg',
]
# Define fragments to extract (e.g., top-left corner, center, area with detail, area with flat color)
# Format: (row_start, col_start, size) - size assumed to be square 128x128
FRAGMENT_SPECS = [
    (0, 0, 128),
    (500, 500, 128), # Adjust coordinates based on your image sizes
    (100, 800, 128),
    (800, 100, 128)
]
OUTPUT_DIR = './jpeg_results/'
os.makedirs(OUTPUT_DIR, exist_ok=True)

# --- Standard JPEG Quantization Tables (Quality 50 approx) ---
QY_STD = np.array([
    [16, 11, 10, 16, 24, 40, 51, 61],
    [12, 12, 14, 19, 26, 58, 60, 55],
    [14, 13, 16, 24, 40, 57, 69, 56],
    [14, 17, 22, 29, 51, 87, 80, 62],
    [18, 22, 37, 56, 68, 109, 103, 77],
    [24, 36, 55, 64, 81, 104, 113, 92],
    [49, 64, 78, 87, 103, 121, 120, 101],
    [72, 92, 95, 98, 112, 100, 103, 99]
], dtype=np.float64) # Use float for division/multiplication later

QC_STD = np.array([
    [17, 18, 24, 47, 99, 99, 99, 99],
    [18, 21, 26, 66, 99, 99, 99, 99],
    [24, 26, 56, 99, 99, 99, 99, 99],
    [47, 66, 99, 99, 99, 99, 99, 99],
    [99, 99, 99, 99, 99, 99, 99, 99],
    [99, 99, 99, 99, 99, 99, 99, 99],
    [99, 99, 99, 99, 99, 99, 99, 99],
    [99, 99, 99, 99, 99, 99, 99, 99]
], dtype=np.float64)

# Quantization table of ones (minimal quantization)
QN = np.ones((8, 8), dtype=np.float64)

# --- Zigzag Scan Pattern ---
ZIGZAG_TEMPLATE = np.array([
    [ 0,  1,  5,  6, 14, 15, 27, 28],
    [ 2,  4,  7, 13, 16, 26, 29, 42],
    [ 3,  8, 12, 17, 25, 30, 41, 43],
    [ 9, 11, 18, 24, 31, 40, 44, 53],
    [10, 19, 23, 32, 39, 45, 52, 54],
    [20, 22, 33, 38, 46, 51, 55, 60],
    [21, 34, 37, 47, 50, 56, 59, 61],
    [35, 36, 48, 49, 57, 58, 62, 63]
])

# --- Helper Functions ---

def zigzag_scan(block_8x8):
    vector_64 = np.zeros(64, dtype=block_8x8.dtype) # Match dtype
    for r in range(8):
        for c in range(8):
            vector_64[ZIGZAG_TEMPLATE[r, c]] = block_8x8[r, c]
    return vector_64

def inverse_zigzag_scan(vector_64):
    block_8x8 = np.zeros((8, 8), dtype=vector_64.dtype) # Match dtype
    if len(vector_64) != 64:
        raise ValueError(f"Inverse zigzag needs a vector of length 64, got {len(vector_64)}")
    for r in range(8):
        for c in range(8):
            block_8x8[r, c] = vector_64[ZIGZAG_TEMPLATE[r, c]]
    return block_8x8

def apply_dct(block_8x8):
    centered_block = block_8x8.astype(np.float64) - 128.0
    return scipy.fftpack.dct(scipy.fftpack.dct(centered_block, axis=0, norm='ortho'), axis=1, norm='ortho')

def apply_idct(dct_block_8x8):
    inversed = scipy.fftpack.idct(scipy.fftpack.idct(dct_block_8x8, axis=0, norm='ortho'), axis=1, norm='ortho')
    return inversed + 128.0

def quantize_block(dct_block_8x8, q_table):
    return np.round(dct_block_8x8 / q_table)

def dequantize_block(quantized_block_8x8, q_table):
    return quantized_block_8x8 * q_table

def chroma_subsample_422(Cb, Cr):
    Cb_sub = Cb[:, ::2]
    Cr_sub = Cr[:, ::2]
    return Cb_sub, Cr_sub

def chroma_upsample_422(Cb_sub, Cr_sub):
    Cb_up = np.repeat(Cb_sub, 2, axis=1)
    Cr_up = np.repeat(Cr_sub, 2, axis=1)
    return Cb_up, Cr_up

# --- Data Structure for Compressed Data ---
class JpegData:
    def __init__(self, Y, Cb, Cr, original_shape, chroma_ratio, QY, QC):
        self.Y = Y
        self.Cb = Cb
        self.Cr = Cr
        self.original_shape = original_shape
        self.chroma_ratio = chroma_ratio
        self.QY = QY
        self.QC = QC

# --- Core Compression/Decompression Functions ---

def process_layer(layer_data, Q_table, target_shape_for_decode=None, compress=True):
    processed_blocks_list = []

    if compress:
        rows, cols = layer_data.shape
        reconstructed_layer = None
    else:
        if target_shape_for_decode is None:
            raise ValueError("target_shape_for_decode must be provided for decompression.")
        rows, cols = target_shape_for_decode
        # Crucial: Initialize with the correct target shape for reconstruction
        reconstructed_layer = np.zeros(target_shape_for_decode, dtype=np.float64)

    num_blocks_wide = math.ceil(cols / 8.0) # Number of blocks horizontally

    for r in range(0, rows, 8):
        for c in range(0, cols, 8):
            if compress:
                block = layer_data[r:min(r+8, rows), c:min(c+8, cols)]
                if block.shape != (8, 8):
                    padded_block = np.zeros((8,8), dtype=block.dtype)
                    padded_block[:block.shape[0], :block.shape[1]] = block
                    block = padded_block

                dct_block = apply_dct(block)
                quantized_block = quantize_block(dct_block, Q_table)
                zigzag_vector = zigzag_scan(quantized_block)
                processed_blocks_list.append(zigzag_vector)
            else: # Decompress
                # Calculate the linear index of the current block
                block_r_idx = r // 8
                block_c_idx = c // 8
                block_index = block_r_idx * num_blocks_wide + block_c_idx

                if block_index < len(layer_data):
                    vector_64 = layer_data[block_index]
                    quantized_block = inverse_zigzag_scan(vector_64)
                    dequantized_block = dequantize_block(quantized_block, Q_table)
                    idct_block = apply_idct(dequantized_block)

                    rows_to_take = min(8, rows - r) # Use target_shape rows here
                    cols_to_take = min(8, cols - c) # Use target_shape cols here
                    reconstructed_layer[r:r+rows_to_take, c:c+cols_to_take] = idct_block[:rows_to_take, :cols_to_take]
                else:
                    print(f"Warning: Decompression block index {block_index} out of bounds for data list of length {len(layer_data)}. Target shape: {target_shape_for_decode}, R={r}, C={c}")

    if compress:
        return processed_blocks_list
    else:
        return reconstructed_layer

def compress_jpeg(rgb_image, chroma_ratio="4:4:4", use_standard_q=True):
    if rgb_image.dtype != np.uint8:
        print("Warning: Input image not uint8. Converting, results might be unexpected.")
        rgb_image = np.clip(rgb_image, 0, 255).astype(np.uint8)

    original_shape = rgb_image.shape # Define before use

    # --- Step 1: Color Conversion ---
    ycbcr_image = cv2.cvtColor(rgb_image, cv2.COLOR_RGB2YCrCb).astype(np.float64) # Corrected placement
    Y_layer  = ycbcr_image[:, :, 0]
    Cr_layer = ycbcr_image[:, :, 1]
    Cb_layer = ycbcr_image[:, :, 2]

    # --- Step 2: Chroma Subsampling (Optional) ---
    if chroma_ratio == "4:2:2":
        Cb_layer_proc, Cr_layer_proc = chroma_subsample_422(Cb_layer, Cr_layer)
    elif chroma_ratio == "4:4:4":
        Cb_layer_proc, Cr_layer_proc = Cb_layer, Cr_layer # Corrected: Use original if no subsampling
    else:
        raise ValueError("Unsupported chroma ratio. Use '4:4:4' or '4:2:2'.")

    # --- Step 3-6: Process each layer ---
    QY = QY_STD if use_standard_q else QN
    QC = QC_STD if use_standard_q else QN

    Y_compressed_vectors = process_layer(Y_layer, QY, compress=True)
    Cb_compressed_vectors = process_layer(Cb_layer_proc, QC, compress=True)
    Cr_compressed_vectors = process_layer(Cr_layer_proc, QC, compress=True)

    # --- Step 7: Store Compressed Data ---
    jpeg_data = JpegData(Y_compressed_vectors, Cb_compressed_vectors, Cr_compressed_vectors,
                         original_shape, chroma_ratio, QY, QC)
    return jpeg_data

def decompress_jpeg(jpeg_data):
    Y_vectors = jpeg_data.Y
    Cb_vectors = jpeg_data.Cb
    Cr_vectors = jpeg_data.Cr
    QY = jpeg_data.QY
    QC = jpeg_data.QC
    original_shape = jpeg_data.original_shape
    chroma_ratio = jpeg_data.chroma_ratio

    rows, cols, _ = original_shape
    Y_target_shape = (rows, cols)

    if chroma_ratio == "4:2:2":
        Cb_target_shape_before_upsample = (rows, math.ceil(cols / 2.0))
        Cr_target_shape_before_upsample = (rows, math.ceil(cols / 2.0))
    else: # 4:4:4
        Cb_target_shape_before_upsample = (rows, cols)
        Cr_target_shape_before_upsample = (rows, cols)

    # Corrected Calls to process_layer
    Y_decompressed = process_layer(Y_vectors, QY, target_shape_for_decode=Y_target_shape, compress=False)
    Cb_decompressed_sub = process_layer(Cb_vectors, QC, target_shape_for_decode=Cb_target_shape_before_upsample, compress=False)
    Cr_decompressed_sub = process_layer(Cr_vectors, QC, target_shape_for_decode=Cr_target_shape_before_upsample, compress=False)

    # --- Step 6: Chroma Upsampling ---
    if chroma_ratio == "4:2:2":
        Cb_decompressed, Cr_decompressed = chroma_upsample_422(Cb_decompressed_sub, Cr_decompressed_sub)
        # Trim potential extra column from np.repeat if original cols was odd
        if Cb_decompressed.shape[1] > cols:
            Cb_decompressed = Cb_decompressed[:, :cols]
        if Cr_decompressed.shape[1] > cols:
            Cr_decompressed = Cr_decompressed[:, :cols]
    else:
        Cb_decompressed = Cb_decompressed_sub
        Cr_decompressed = Cr_decompressed_sub

    # --- Step 7: Color Conversion ---
    Y_final = np.clip(Y_decompressed, 0, 255)
    Cb_final = np.clip(Cb_decompressed, 0, 255)
    Cr_final = np.clip(Cr_decompressed, 0, 255)

    ycrcb_image = np.dstack((Y_final, Cr_final, Cb_final)).astype(np.uint8)
    rgb_image = cv2.cvtColor(ycrcb_image, cv2.COLOR_YCrCb2RGB)
    return rgb_image

# --- Analysis and Plotting ---
def plot_comparison(original, reconstructed, title, filename):
    fig, axs = plt.subplots(1, 2, figsize=(10, 5))
    fig.suptitle(title, fontsize=14)
    axs[0].imshow(original)
    axs[0].set_title("Original")
    axs[0].axis('off')
    axs[1].imshow(reconstructed)
    axs[1].set_title("Reconstructed")
    axs[1].axis('off')
    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.savefig(filename)
    plt.close(fig)

# ... (cały kod do funkcji plot_comparison bez zmian) ...

# --- Main Execution Loop ---
if __name__ == "__main__":
    # Check dependencies (optional but good practice)
    try:
        import cv2
        import scipy.fftpack
        import matplotlib.pyplot
        import imageio.v3 as iio # Upewnij się, że iio jest zaimportowane
    except ImportError as e:
        print(f"Error: Missing dependency - {e}. Please install required libraries (opencv-python, scipy, matplotlib, imageio).")
        sys.exit(1)

    valid_images = [p for p in IMAGE_PATHS if os.path.exists(p)]
    if not valid_images:
        print("Error: No valid image paths found in IMAGE_PATHS. Please check.")
        sys.exit(1)

    print(f"Processing {len(valid_images)} images...")

    for img_index, img_path in enumerate(valid_images):
        base_img_name = os.path.splitext(os.path.basename(img_path))[0]
        print(f"\n--- Image: {base_img_name} ---")
        try:
            image_orig_full = iio.imread(img_path)
            if image_orig_full.shape[2] == 4:
                print(f"  Removing alpha channel from {base_img_name}")
                image_orig_full = image_orig_full[:, :, :3]
            if image_orig_full.ndim != 3 or image_orig_full.shape[2] != 3:
                 print(f"  Skipping non-RGB image: {base_img_name} (Shape: {image_orig_full.shape})")
                 continue

            print(f"  Full size: {image_orig_full.shape}")

            for frag_index, (r, c, size) in enumerate(FRAGMENT_SPECS):
                 if r+size > image_orig_full.shape[0] or c+size > image_orig_full.shape[1]:
                     print(f"  Skipping fragment {frag_index+1}: Out of bounds (Start:{r},{c} Size:{size} vs Image:{image_orig_full.shape[0]},{image_orig_full.shape[1]}).")
                     continue

                 fragment_orig = image_orig_full[r:r+size, c:c+size, :].copy()
                 print(f"  Processing Fragment {frag_index+1} (start: {r},{c} size: {size}x{size})")

                 # === DODANA LINIA DO ZAPISU ORYGINALNEGO FRAGMENTU ===
                 original_frag_filename = os.path.join(OUTPUT_DIR, f"{base_img_name}_Frag{frag_index+1}_Original.png")
                 iio.imwrite(original_frag_filename, fragment_orig)
                 print(f"      Saved original fragment: {original_frag_filename}")
                 # ======================================================

                 for ratio in ["4:4:4", "4:2:2"]:
                     for use_q in [False, True]:
                         q_desc = "StdQ" if use_q else "OnesQ"
                         print(f"    Testing: Ratio={ratio}, Quant={q_desc}")

                         try:
                            jpeg_compressed_data = compress_jpeg(fragment_orig, chroma_ratio=ratio, use_standard_q=use_q)
                            fragment_reconstructed = decompress_jpeg(jpeg_compressed_data)

                            # Nazwa pliku dla porównania (oryginał vs zrekonstruowany)
                            comparison_plot_title = f"{base_img_name}_Frag{frag_index+1}_{ratio.replace(':','')}_{q_desc}"
                            comparison_plot_filename = os.path.join(OUTPUT_DIR, f"{comparison_plot_title}.png")
                            plot_comparison(fragment_orig, fragment_reconstructed, comparison_plot_title, comparison_plot_filename)
                            print(f"      Saved comparison plot: {comparison_plot_filename}")

                         except Exception as e_inner:
                             print(f"      ERROR during JPEG processing for {ratio}/{q_desc}: {e_inner}")
                             import traceback
                             traceback.print_exc()

        except FileNotFoundError:
            print(f"  ERROR: Cannot find image file {img_path}")
        except Exception as e_outer:
            print(f"  ERROR processing image {img_path}: {e_outer}")
            import traceback
            traceback.print_exc()

    print("\n--- JPEG Analysis Script Finished ---")