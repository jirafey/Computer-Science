import cv2
import numpy as np
import matplotlib.pyplot as plt
import os
import sys
import math


# --- Implementacja RLE (zakładamy, że jest poprawna z poprzednich wersji) ---
def rle_encode_layer(flat_data):
    if not isinstance(flat_data, np.ndarray) or flat_data.ndim != 1:
        if isinstance(flat_data, np.ndarray):
            flat_data = flat_data.flatten()
        else:
            flat_data = np.array(flat_data).flatten()
    if flat_data.size == 0: return np.array([], dtype=np.int64)
    encoded_list = [];
    count = 1;
    current_val = flat_data[0]
    for i in range(1, flat_data.size):
        if flat_data[i] == current_val:
            count += 1
        else:
            encoded_list.extend([count, current_val]); current_val = flat_data[i]; count = 1
    encoded_list.extend([count, current_val])
    return np.array(encoded_list, dtype=np.int64)


def rle_decode_layer(encoded_data, original_size, dtype_out=np.float64):
    if not isinstance(encoded_data, np.ndarray): encoded_data = np.array(encoded_data)
    if encoded_data.size == 0:
        return np.array([], dtype=dtype_out)  # Reshape should happen outside
    if encoded_data.size % 2 != 0: raise ValueError("Invalid RLE data size, must be even.")
    decoded_list = [];
    current_decoded_size = 0
    for i in range(0, encoded_data.size, 2):
        try:
            count = int(encoded_data[i]); assert count >= 0
        except (ValueError, AssertionError):
            raise ValueError(f"Invalid count in RLE data: {encoded_data[i]}")
        value = encoded_data[i + 1];
        decoded_list.extend([value] * count);
        current_decoded_size += count

    decoded_array = np.array(decoded_list, dtype=dtype_out)
    if original_size is not None and current_decoded_size != original_size:
        # print(f"Warning: RLE decoded size {current_decoded_size} != expected {original_size}. Adjusting.")
        if current_decoded_size > original_size:
            decoded_array = decoded_array[:original_size]
        else:  # current_decoded_size < original_size
            padding_value = dtype_out(0)
            padding = np.full(original_size - current_decoded_size, padding_value, dtype=dtype_out)
            decoded_array = np.concatenate((decoded_array, padding))
    return decoded_array


# --- Ustawienia Główne ---
kat = '.'
pliki_wideo = ["clip_1.mp4", "clip_2.mp4"]
ile = -1  # -1 przetwarza całe wideo
ROI_LIST = [[100, 228, 100, 228]]  # Lista ROI, np. [[y1,y2,x1,x2]]
OUTPUT_DIR = './video_results_corrected'  # Nowy katalog wyjściowy
os.makedirs(OUTPUT_DIR, exist_ok=True)
EPS = np.finfo(np.float32).eps

# --- Ustawienia Trybu Pracy ---
# TRYB = 1 # 1: Analiza Jakości (bez RLE, generuje plot_diff)
TRYB = 2  # 2: Analiza Skuteczności RLE

# --- Zmienne konfiguracyjne (wspólne) ---
default_key_frame_interval = 8  # Dla TRYB=1, można to nadpisać w pętli, jeśli potrzeba
# Klatki do analizy wizualnej w TRYB=1 (I-frame, P tuż przed I, następny I, P dalej, P najdalej)
# Jeśli KF co 4, to klatka 31 jest (32-1), czyli tuż przed 8-mą klatką kluczową (0,4,8,12,16,20,24,28,32)
# Jeśli KF co 8, to klatka 31 jest tuż przed 4-tą klatką kluczową (0,8,16,24,32)
# Dostosuj `plot_frames` do swoich interwałów KF i długości klipów
default_plot_frames_kf8 = np.array([0, 7, 8, 15, 23, 31])  # Dla KF=8 (0, 8, 16, 24, 32...)
default_plot_frames_kf4 = np.array([0, 3, 4, 7, 11, 15, 31])  # Dla KF=4 (0, 4, 8, 12, 16...)
wyswietlaj_klatki_live = False

# Parametry specyficzne dla Trybu 1 (Analiza Jakości)
if TRYB == 1:
    print("--- TRYB 1: ANALIZA JAKOŚCI (BEZ RLE) ---")
    # Zgodnie z PDF: 4:4:4, 4:2:2, 4:4:0, 4:2:0, 4:1:1, 4:1:0
    SUBSAMPLING_LIST_FULL = ["4:4:4", "4:2:2", "4:2:0", "4:4:0", "4:1:1", "4:1:0"]
    DZIELNIK_LIST_QUALITY = [1, 2, 4]  # stopień kompresji informacji o różnicy

    PARAM_SETS = []
    # Użyj stałego interwału KF dla części 1, np. 8
    # Jeśli chcesz testować np. klatkę 31 dla KF=4, musisz to inaczej zorganizować lub mieć osobny przebieg
    key_frame_interval_for_quality = 8
    # Wybierz odpowiedni zestaw klatek do plotowania
    plot_frames_for_quality = default_plot_frames_kf8
    if key_frame_interval_for_quality == 4:
        plot_frames_for_quality = default_plot_frames_kf4

    for ss_ratio in SUBSAMPLING_LIST_FULL:
        for div_val in DZIELNIK_LIST_QUALITY:
            PARAM_SETS.append({
                'subsampling': ss_ratio,
                'dzielnik': div_val,
                'key_frame_interval': key_frame_interval_for_quality,  # Stały dla części 1
                'use_lossless': False,
                'lossless_method': 'RLE',  # Nieużywane, ale spójność
                'plot_frames': plot_frames_for_quality
            })

# Parametry specyficzne dla Trybu 2 (Analiza Skuteczności RLE)
elif TRYB == 2:
    print("--- TRYB 2: ANALIZA SKUTECZNOŚCI RLE ---")
    PARAM_SETS = []
    # Użyj "najlepszych" ustawień z części 1: np. 4:2:0, dzielnik=2
    best_ss_for_rle = "4:2:0"
    best_div_for_rle = 2
    # Zgodnie z PDF: minimum 6 odległości z zakresu <2, 20> klatek
    # Możemy wybrać np. 2, 4, 8, 12, 16, 20
    KEY_FRAME_INTERVAL_LIST_RLE = [2, 4, 8, 12, 16, 20]

    for kf_interval in KEY_FRAME_INTERVAL_LIST_RLE:
        PARAM_SETS.append({
            'subsampling': best_ss_for_rle,
            'dzielnik': best_div_for_rle,
            'key_frame_interval': kf_interval,
            'use_lossless': True,
            'lossless_method': 'RLE',
            'plot_frames': np.array([])  # Nie generuj plotów różnic w tym trybie
        })
else:
    print("BŁĄD: Niepoprawny numer TRYBU (ustaw 1 lub 2).");
    sys.exit(1)


##############################################################################
class data:
    def __init__(self):
        self.Y = None;
        self.Cb = None;
        self.Cr = None
        self.Y_orig_shape = None;
        self.Cb_orig_shape = None;
        self.Cr_orig_shape = None
        self.Y_orig_dtype = None;
        self.Cb_orig_dtype = None;
        self.Cr_orig_dtype = None
        self.Y_compressed_size = None;
        self.Cb_compressed_size = None;
        self.Cr_compressed_size = None


def Chroma_subsampling(Layer, subsampling_ratio):
    if Layer is None: return None
    if subsampling_ratio == "4:4:4":
        return Layer
    elif subsampling_ratio == "4:2:2":
        return Layer[:, ::2]  # Y Y, Cb Cr (co drugi CbCr w poziomie)
    elif subsampling_ratio == "4:2:0":
        return Layer[::2, ::2]  # Y Y / Y Y, CbCr / 0 0 (co drugi CbCr w poziomie i pionie)
    elif subsampling_ratio == "4:4:0":
        return Layer[::2, :]  # Y Y / Y Y, CbCr / CbCr (co drugi rząd CbCr)
    elif subsampling_ratio == "4:1:1":
        return Layer[:, ::4]  # YYYY, CbCr (co czwarty CbCr w poziomie)
    elif subsampling_ratio == "4:1:0":
        return Layer[::2, ::4]  # YYYY/YYYY, CbCr/0000 (co czwarty CbCr w poziomie, co drugi w pionie)
    else:
        print(f"Warning: Unknown subsampling '{subsampling_ratio}', returning original."); return Layer


def Chroma_resampling(SubsampledLayer, subsampling_ratio, target_shape):
    rows_target, cols_target = target_shape
    if SubsampledLayer is None or SubsampledLayer.ndim != 2 or SubsampledLayer.size == 0:
        return np.zeros(target_shape, dtype=np.float64)

    current_rows, current_cols = SubsampledLayer.shape

    if subsampling_ratio == "4:4:4":
        # Ensure it matches target shape, pad if necessary
        resampled = np.zeros(target_shape, dtype=SubsampledLayer.dtype)
        copy_rows = min(current_rows, rows_target);
        copy_cols = min(current_cols, cols_target)
        resampled[:copy_rows, :copy_cols] = SubsampledLayer[:copy_rows, :copy_cols]
        return resampled.astype(np.float64)

    # Determine column and row repeat factors
    if subsampling_ratio == "4:2:2" or subsampling_ratio == "4:2:0":
        factor_col = 2
    elif subsampling_ratio == "4:1:1" or subsampling_ratio == "4:1:0":
        factor_col = 4
    else:
        factor_col = 1  # For 4:4:4 (already handled) and 4:4:0

    if subsampling_ratio == "4:4:0" or subsampling_ratio == "4:2:0" or subsampling_ratio == "4:1:0":
        factor_row = 2
    else:
        factor_row = 1  # For 4:4:4, 4:2:2, 4:1:1

    resampled_layer = SubsampledLayer
    if factor_col > 1:
        resampled_layer = np.repeat(resampled_layer, factor_col, axis=1)
    if factor_row > 1:
        resampled_layer = np.repeat(resampled_layer, factor_row, axis=0)

    # Adjust to target shape (cropping or padding if necessary)
    # This is a simple crop/pad, more sophisticated interpolation could be used for better quality
    final_resampled = np.zeros(target_shape, dtype=resampled_layer.dtype)
    copy_rows = min(resampled_layer.shape[0], rows_target)
    copy_cols = min(resampled_layer.shape[1], cols_target)
    final_resampled[:copy_rows, :copy_cols] = resampled_layer[:copy_rows, :copy_cols]

    return final_resampled.astype(np.float64)


def frame_image_to_class(frame_ycrcb, current_subsampling):
    Frame_class = data()
    Frame_class.Y = frame_ycrcb[:, :, 0].astype(np.float64)
    Frame_class.Cb = Chroma_subsampling(frame_ycrcb[:, :, 2].astype(np.float64), current_subsampling)
    Frame_class.Cr = Chroma_subsampling(frame_ycrcb[:, :, 1].astype(np.float64), current_subsampling)
    Frame_class.Y_orig_shape = Frame_class.Y.shape
    Frame_class.Cb_orig_shape = Frame_class.Cb.shape if Frame_class.Cb is not None else None
    Frame_class.Cr_orig_shape = Frame_class.Cr.shape if Frame_class.Cr is not None else None
    Frame_class.Y_orig_dtype = Frame_class.Y.dtype
    Frame_class.Cb_orig_dtype = Frame_class.Cb.dtype if Frame_class.Cb is not None else None
    Frame_class.Cr_orig_dtype = Frame_class.Cr.dtype if Frame_class.Cr is not None else None
    return Frame_class


def frame_layers_to_image(Y_layer, Cr_layer, Cb_layer, current_subsampling, target_y_shape):
    if not isinstance(Y_layer, np.ndarray) or Y_layer.ndim != 2:
        print("Error: Invalid Y_layer data for frame_layers_to_image");
        return np.zeros(target_y_shape + (3,), dtype=np.uint8)
    # Cb_layer and Cr_layer can be None if subsampling was aggressive and resulted in empty array
    # or if an error occurred. Chroma_resampling should handle None input.

    Cb_resampled = Chroma_resampling(Cb_layer, current_subsampling, target_y_shape)
    Cr_resampled = Chroma_resampling(Cr_layer, current_subsampling, target_y_shape)

    if not (Y_layer.shape[:2] == Cb_resampled.shape[:2] == Cr_resampled.shape[:2]):
        min_r = min(Y_layer.shape[0], Cb_resampled.shape[0], Cr_resampled.shape[0])
        min_c = min(Y_layer.shape[1], Cb_resampled.shape[1], Cr_resampled.shape[1])
        Y_layer = Y_layer[:min_r, :min_c]
        Cb_resampled = Cb_resampled[:min_r, :min_c]
        Cr_resampled = Cr_resampled[:min_r, :min_c]

    return np.dstack(
        [Y_layer.astype(np.float64), Cr_resampled.astype(np.float64), Cb_resampled.astype(np.float64)]).clip(0,
                                                                                                             255).astype(
        np.uint8)


def compress_KeyFrame(Frame_class, use_lossless=False, lossless_method='RLE'):
    KeyFrame = data()
    KeyFrame.Y_orig_shape = Frame_class.Y_orig_shape
    KeyFrame.Cb_orig_shape = Frame_class.Cb_orig_shape
    KeyFrame.Cr_orig_shape = Frame_class.Cr_orig_shape
    KeyFrame.Y_orig_dtype = Frame_class.Y_orig_dtype
    KeyFrame.Cb_orig_dtype = Frame_class.Cb_orig_dtype
    KeyFrame.Cr_orig_dtype = Frame_class.Cr_orig_dtype

    Y_temp = Frame_class.Y.copy()
    Cb_temp = Frame_class.Cb.copy() if Frame_class.Cb is not None else np.array([])
    Cr_temp = Frame_class.Cr.copy() if Frame_class.Cr is not None else np.array([])

    if use_lossless and lossless_method == 'RLE':
        encoded_Y = rle_encode_layer(Y_temp.flatten())
        encoded_Cb = rle_encode_layer(Cb_temp.flatten()) if Cb_temp.size > 0 else np.array([])
        encoded_Cr = rle_encode_layer(Cr_temp.flatten()) if Cr_temp.size > 0 else np.array([])
        KeyFrame.Y_compressed_size = encoded_Y.nbytes
        KeyFrame.Cb_compressed_size = encoded_Cb.nbytes
        KeyFrame.Cr_compressed_size = encoded_Cr.nbytes
        KeyFrame.Y = encoded_Y;
        KeyFrame.Cb = encoded_Cb;
        KeyFrame.Cr = encoded_Cr
    else:
        KeyFrame.Y = Y_temp;
        KeyFrame.Cb = Cb_temp;
        KeyFrame.Cr = Cr_temp
        KeyFrame.Y_compressed_size = Y_temp.nbytes
        KeyFrame.Cb_compressed_size = Cb_temp.nbytes if Cb_temp is not None else 0
        KeyFrame.Cr_compressed_size = Cr_temp.nbytes if Cr_temp is not None else 0
    return KeyFrame


def decompress_KeyFrame(KeyFrame, subsampling_ratio_local, use_lossless=False, lossless_method='RLE'):
    if KeyFrame.Y_orig_shape is None:
        raise ValueError("Missing Y_orig_shape in KeyFrame for decompression")

    Y_data, Cb_data, Cr_data = KeyFrame.Y, KeyFrame.Cb, KeyFrame.Cr
    Y_shape, Cb_shape, Cr_shape = KeyFrame.Y_orig_shape, KeyFrame.Cb_orig_shape, KeyFrame.Cr_orig_shape
    Y_dtype, Cb_dtype, Cr_dtype = KeyFrame.Y_orig_dtype, KeyFrame.Cb_orig_dtype, KeyFrame.Cr_orig_dtype

    if use_lossless and lossless_method == 'RLE':
        Y = rle_decode_layer(Y_data, math.prod(Y_shape), dtype_out=Y_dtype if Y_dtype else np.float64).reshape(Y_shape)
        Cb = rle_decode_layer(Cb_data, math.prod(Cb_shape) if Cb_shape else 0,
                              dtype_out=Cb_dtype if Cb_dtype else np.float64)
        if Cb_shape and Cb.size > 0:
            Cb = Cb.reshape(Cb_shape)
        elif Cb_shape:
            Cb = np.zeros(Cb_shape, dtype=Cb_dtype if Cb_dtype else np.float64)  # Handle empty if shape known
        else:
            Cb = np.array([])

        Cr = rle_decode_layer(Cr_data, math.prod(Cr_shape) if Cr_shape else 0,
                              dtype_out=Cr_dtype if Cr_dtype else np.float64)
        if Cr_shape and Cr.size > 0:
            Cr = Cr.reshape(Cr_shape)
        elif Cr_shape:
            Cr = np.zeros(Cr_shape, dtype=Cr_dtype if Cr_dtype else np.float64)
        else:
            Cr = np.array([])
    else:
        Y, Cb, Cr = Y_data, Cb_data, Cr_data

    return frame_layers_to_image(Y, Cr, Cb, subsampling_ratio_local, Y_shape)


def compress_not_KeyFrame(Frame_class, Last_KeyFrame_DECOMPRESSED_YCrCb_arg, current_subsampling, current_divider,
                          use_lossless=False, lossless_method='RLE'):
    Diff_Frame_Data = data()
    Last_KF_Y = Last_KeyFrame_DECOMPRESSED_YCrCb_arg[:, :, 0].astype(np.float64)
    Last_KF_Cb_orig = Last_KeyFrame_DECOMPRESSED_YCrCb_arg[:, :, 2].astype(np.float64)
    Last_KF_Cr_orig = Last_KeyFrame_DECOMPRESSED_YCrCb_arg[:, :, 1].astype(np.float64)

    Last_KF_Cb_Subsampled = Chroma_subsampling(Last_KF_Cb_orig, current_subsampling)
    Last_KF_Cr_Subsampled = Chroma_subsampling(Last_KF_Cr_orig, current_subsampling)

    # Ensure current P-frame chroma layers are not None before subtraction
    Current_Cb = Frame_class.Cb if Frame_class.Cb is not None else np.zeros_like(
        Last_KF_Cb_Subsampled) if Last_KF_Cb_Subsampled is not None else np.array([])
    Current_Cr = Frame_class.Cr if Frame_class.Cr is not None else np.zeros_like(
        Last_KF_Cr_Subsampled) if Last_KF_Cr_Subsampled is not None else np.array([])

    if Frame_class.Y.shape != Last_KF_Y.shape: raise ValueError(
        f"Y shape mismatch P-compress: {Frame_class.Y.shape} vs {Last_KF_Y.shape}")
    if Last_KF_Cb_Subsampled is not None and Current_Cb.shape != Last_KF_Cb_Subsampled.shape: raise ValueError(
        f"Cb shape mismatch P-compress: {Current_Cb.shape} vs {Last_KF_Cb_Subsampled.shape}")
    if Last_KF_Cr_Subsampled is not None and Current_Cr.shape != Last_KF_Cr_Subsampled.shape: raise ValueError(
        f"Cr shape mismatch P-compress: {Current_Cr.shape} vs {Last_KF_Cr_Subsampled.shape}")

    Diff_Y = np.round((Frame_class.Y - Last_KF_Y) / current_divider)
    Diff_Cb = np.round((
                                   Current_Cb - Last_KF_Cb_Subsampled)) / current_divider if Last_KF_Cb_Subsampled is not None and Current_Cb.size > 0 else np.array(
        [])
    Diff_Cr = np.round((
                                   Current_Cr - Last_KF_Cr_Subsampled)) / current_divider if Last_KF_Cr_Subsampled is not None and Current_Cr.size > 0 else np.array(
        [])

    Diff_Frame_Data.Y_orig_shape = Diff_Y.shape
    Diff_Frame_Data.Cb_orig_shape = Diff_Cb.shape if Diff_Cb.size > 0 else None
    Diff_Frame_Data.Cr_orig_shape = Diff_Cr.shape if Diff_Cr.size > 0 else None

    Y_diff_to_store = Diff_Y.astype(np.int16)
    Cb_diff_to_store = Diff_Cb.astype(np.int16) if Diff_Cb.size > 0 else np.array([], dtype=np.int16)
    Cr_diff_to_store = Diff_Cr.astype(np.int16) if Diff_Cr.size > 0 else np.array([], dtype=np.int16)

    Diff_Frame_Data.Y_orig_dtype = Y_diff_to_store.dtype
    Diff_Frame_Data.Cb_orig_dtype = Cb_diff_to_store.dtype
    Diff_Frame_Data.Cr_orig_dtype = Cr_diff_to_store.dtype

    if use_lossless and lossless_method == 'RLE':
        encoded_Y = rle_encode_layer(Y_diff_to_store.flatten())
        encoded_Cb = rle_encode_layer(Cb_diff_to_store.flatten()) if Cb_diff_to_store.size > 0 else np.array([])
        encoded_Cr = rle_encode_layer(Cr_diff_to_store.flatten()) if Cr_diff_to_store.size > 0 else np.array([])
        Diff_Frame_Data.Y_compressed_size = encoded_Y.nbytes
        Diff_Frame_Data.Cb_compressed_size = encoded_Cb.nbytes
        Diff_Frame_Data.Cr_compressed_size = encoded_Cr.nbytes
        Diff_Frame_Data.Y = encoded_Y;
        Diff_Frame_Data.Cb = encoded_Cb;
        Diff_Frame_Data.Cr = encoded_Cr
    else:
        Diff_Frame_Data.Y = Y_diff_to_store;
        Diff_Frame_Data.Cb = Cb_diff_to_store;
        Diff_Frame_Data.Cr = Cr_diff_to_store
        Diff_Frame_Data.Y_compressed_size = Y_diff_to_store.nbytes
        Diff_Frame_Data.Cb_compressed_size = Cb_diff_to_store.nbytes
        Diff_Frame_Data.Cr_compressed_size = Cr_diff_to_store.nbytes
    return Diff_Frame_Data


def decompress_not_KeyFrame(Diff_Frame_Data, Last_KeyFrame_DECOMPRESSED_YCrCb_arg, subsampling_ratio_local,
                            current_divider, use_lossless=False, lossless_method='RLE'):
    if Diff_Frame_Data.Y_orig_shape is None: raise ValueError(
        "Missing Y_orig_shape in Diff_Frame_Data for P-decompress")

    Y_diff_data, Cb_diff_data, Cr_diff_data = Diff_Frame_Data.Y, Diff_Frame_Data.Cb, Diff_Frame_Data.Cr
    Y_shape, Cb_shape, Cr_shape = Diff_Frame_Data.Y_orig_shape, Diff_Frame_Data.Cb_orig_shape, Diff_Frame_Data.Cr_orig_shape
    Y_dtype, Cb_dtype, Cr_dtype = Diff_Frame_Data.Y_orig_dtype, Diff_Frame_Data.Cb_orig_dtype, Diff_Frame_Data.Cr_orig_dtype

    if use_lossless and lossless_method == 'RLE':
        Y_diff = rle_decode_layer(Y_diff_data, math.prod(Y_shape), dtype_out=Y_dtype if Y_dtype else np.int16).reshape(
            Y_shape)
        Cb_diff = rle_decode_layer(Cb_diff_data, math.prod(Cb_shape) if Cb_shape else 0,
                                   dtype_out=Cb_dtype if Cb_dtype else np.int16)
        if Cb_shape and Cb_diff.size > 0:
            Cb_diff = Cb_diff.reshape(Cb_shape)
        elif Cb_shape:
            Cb_diff = np.zeros(Cb_shape, dtype=Cb_dtype if Cb_dtype else np.int16)
        else:
            Cb_diff = np.array([])

        Cr_diff = rle_decode_layer(Cr_diff_data, math.prod(Cr_shape) if Cr_shape else 0,
                                   dtype_out=Cr_dtype if Cr_dtype else np.int16)
        if Cr_shape and Cr_diff.size > 0:
            Cr_diff = Cr_diff.reshape(Cr_shape)
        elif Cr_shape:
            Cr_diff = np.zeros(Cr_shape, dtype=Cr_dtype if Cr_dtype else np.int16)
        else:
            Cr_diff = np.array([])
    else:
        Y_diff, Cb_diff, Cr_diff = Y_diff_data, Cb_diff_data, Cr_diff_data

    Last_KF_Y = Last_KeyFrame_DECOMPRESSED_YCrCb_arg[:, :, 0].astype(np.float64)
    Last_KF_Cb_orig = Last_KeyFrame_DECOMPRESSED_YCrCb_arg[:, :, 2].astype(np.float64)
    Last_KF_Cr_orig = Last_KeyFrame_DECOMPRESSED_YCrCb_arg[:, :, 1].astype(np.float64)

    Last_KF_Cb_Subsampled = Chroma_subsampling(Last_KF_Cb_orig, subsampling_ratio_local)
    Last_KF_Cr_Subsampled = Chroma_subsampling(Last_KF_Cr_orig, subsampling_ratio_local)

    # Ensure Cb_diff and Cr_diff have shapes compatible with Last_KF_Cb/Cr_Subsampled if they are not empty
    if Y_diff.shape != Last_KF_Y.shape: raise ValueError(
        f"Y shape mismatch P-decode: {Y_diff.shape} vs {Last_KF_Y.shape}")
    if Cb_diff.size > 0 and Last_KF_Cb_Subsampled is not None and Cb_diff.shape != Last_KF_Cb_Subsampled.shape: raise ValueError(
        f"Cb shape mismatch P-decode: {Cb_diff.shape} vs {Last_KF_Cb_Subsampled.shape}")
    if Cr_diff.size > 0 and Last_KF_Cr_Subsampled is not None and Cr_diff.shape != Last_KF_Cr_Subsampled.shape: raise ValueError(
        f"Cr shape mismatch P-decode: {Cr_diff.shape} vs {Last_KF_Cr_Subsampled.shape}")

    Y_recon = (Y_diff.astype(np.float64) * current_divider) + Last_KF_Y
    Cb_recon = (Cb_diff.astype(
        np.float64) * current_divider) + Last_KF_Cb_Subsampled if Cb_diff.size > 0 and Last_KF_Cb_Subsampled is not None else (
        Last_KF_Cb_Subsampled if Last_KF_Cb_Subsampled is not None else np.zeros_like(Y_recon))
    Cr_recon = (Cr_diff.astype(
        np.float64) * current_divider) + Last_KF_Cr_Subsampled if Cr_diff.size > 0 and Last_KF_Cr_Subsampled is not None else (
        Last_KF_Cr_Subsampled if Last_KF_Cr_Subsampled is not None else np.zeros_like(Y_recon))

    return frame_layers_to_image(Y_recon, Cr_recon, Cb_recon, subsampling_ratio_local, Y_recon.shape[:2])


# Global variable to help plotDiffrence construct filenames
current_video_file_for_plot = ""
current_kf_interval_for_plot = ""


def plotDiffrence(ReferenceFrame_YCrCb, DecompressedFrame_YCrCb, ROI_coords, frame_index, roi_index, save_dir_base=".",
                  suffix_params=""):
    global current_video_file_for_plot, current_kf_interval_for_plot  # Use globals
    try:
        ReferenceFrame_RGB = cv2.cvtColor(np.clip(ReferenceFrame_YCrCb, 0, 255).astype(np.uint8), cv2.COLOR_YCrCb2RGB)
        DecompressedFrame_RGB = cv2.cvtColor(np.clip(DecompressedFrame_YCrCb, 0, 255).astype(np.uint8),
                                             cv2.COLOR_YCrCb2RGB)
        y1, y2, x1, x2 = ROI_coords
        if not (0 <= y1 < y2 <= ReferenceFrame_RGB.shape[0] and 0 <= x1 < x2 <= ReferenceFrame_RGB.shape[1]):
            print(f"ERROR: ROI {ROI_coords} out of bounds. Skipping plot.");
            return

        fig, axs = plt.subplots(1, 3, sharey=True);
        fig.set_size_inches(18, 6)
        roi_slice = (slice(y1, y2), slice(x1, x2))
        axs[0].imshow(ReferenceFrame_RGB[roi_slice]);
        axs[0].set_title(f"Original ROI-{roi_index} (RGB)");
        axs[0].axis('off')
        axs[2].imshow(DecompressedFrame_RGB[roi_slice]);
        axs[2].set_title(f"Decompressed ROI-{roi_index} (RGB)");
        axs[2].axis('off')
        diff = ReferenceFrame_RGB[roi_slice].astype(np.float64) - DecompressedFrame_RGB[roi_slice].astype(np.float64)
        abs_diff = np.abs(diff);
        max_abs_diff = np.max(abs_diff)
        if max_abs_diff < EPS:
            diff_vis = np.full_like(diff, 128, dtype=np.uint8)
        else:
            diff_vis = (abs_diff / (max_abs_diff + EPS)) * 255
        axs[1].imshow(diff_vis.astype(np.uint8));
        axs[1].set_title(f"Abs Difference ROI-{roi_index} (Scaled)");
        axs[1].axis('off')

        video_name_no_ext = os.path.splitext(os.path.basename(current_video_file_for_plot))[0]
        specific_save_dir = os.path.join(save_dir_base, video_name_no_ext)
        os.makedirs(specific_save_dir, exist_ok=True)

        # Construct suffix including kf_interval for uniqueness if it's part of the test parameters
        final_suffix = f"{suffix_params}_kf{current_kf_interval_for_plot}"

        plot_filename = f"plot_diff_frame{frame_index}_roi{roi_index}{final_suffix}.png"
        save_path = os.path.join(specific_save_dir, plot_filename)
        plt.suptitle(
            f"Video: {video_name_no_ext}, Frame: {frame_index}, ROI: {roi_index}, Params: {final_suffix.strip('_')}",
            fontsize=10)
        plt.tight_layout(rect=[0, 0, 1, 0.96])
        plt.savefig(save_path);
        plt.close(fig)
    except Exception as e:
        print(f"Error plotting frame {frame_index} ROI {roi_index} for {current_video_file_for_plot}: {e}");
        import traceback;
        traceback.print_exc()
        if 'fig' in locals() and plt.fignum_exists(fig.number): plt.close(fig)


##############################################################################
if __name__ == "__main__":
    for video_file_path_loop in pliki_wideo:
        current_video_file_for_plot = video_file_path_loop  # Set global for plotDiffrence
        print(f"\n{'=' * 10} Processing Video: {current_video_file_for_plot} {'=' * 10}")

        for params_idx, params in enumerate(PARAM_SETS):
            current_subsampling = params['subsampling']
            current_dzielnik = params['dzielnik']
            current_key_frame_interval = params['key_frame_interval']
            current_use_lossless = params['use_lossless']
            current_lossless_method = params['lossless_method']
            current_plot_frames_list = params['plot_frames']
            current_kf_interval_for_plot = str(current_key_frame_interval)  # Set global for plotDiffrence filename

            print(
                f"\n--- Param Set {params_idx + 1}/{len(PARAM_SETS)}: SS={current_subsampling}, Div={current_dzielnik}, KF_Int={current_key_frame_interval}, Lossless={current_use_lossless} ---")

            cap = cv2.VideoCapture(os.path.join(kat, current_video_file_for_plot))
            if not cap.isOpened(): print(f"BŁĄD: Nie można otworzyć {current_video_file_for_plot}"); continue

            width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH));
            height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
            frame_count_prop = cap.get(cv2.CAP_PROP_FRAME_COUNT)
            effective_ile = ile
            if effective_ile < 0:
                effective_ile = int(
                    frame_count_prop) if frame_count_prop > 0 else 200  # Max frames to process if not specified
            elif effective_ile == 0:
                cap.release(); continue
            else:
                effective_ile = min(effective_ile, int(frame_count_prop)) if frame_count_prop > 0 else effective_ile

            max_plot_frame = np.max(current_plot_frames_list) if current_plot_frames_list.size > 0 else -1
            frames_to_process_for_plots = max(effective_ile,
                                              max_plot_frame + 1) if max_plot_frame != -1 else effective_ile
            # For RLE tests (TRYB=2), PDF suggests 15-20 klatches, but the question implies testing KF intervals.
            # We'll process 'effective_ile' or up to the max frame needed for plotting.
            # For RLE, the PDF states "maksymalnie 15-20 klatach", this needs to be reconciled with "minimum 6 odległościach z zakresu < 2, 20 > klatek".
            # If testing KF interval of 20, we need at least 20 frames.
            # Let's use a sensible number for RLE tests if 'ile' is -1.
            if TRYB == 2 and ile == -1:
                # Ensure enough frames for the largest KF interval + a few more
                frames_to_process_for_rle_test = max(
                    KEY_FRAME_INTERVAL_LIST_RLE) + current_key_frame_interval  # e.g. 20 + 20 = 40
                frames_to_process_for_plots = min(frames_to_process_for_rle_test,
                                                  int(frame_count_prop) if frame_count_prop > 0 else frames_to_process_for_rle_test)

            Last_KeyFrame_Compressed_Data = None
            Last_KeyFrame_Decompressed_YCrCb = None
            if current_use_lossless: compression_stats = {'Y_gain': [], 'Cb_gain': [], 'Cr_gain': [], 'is_keyframe': []}

            for i in range(frames_to_process_for_plots):
                ret, frame_bgr = cap.read()
                if not ret: print(
                    f"End of {current_video_file_for_plot} or error at frame {i}. Processed {i} frames."); break
                frame_ycrcb_original = cv2.cvtColor(frame_bgr, cv2.COLOR_BGR2YCrCb)
                Current_Frame_Layers = frame_image_to_class(frame_ycrcb_original, current_subsampling)
                Decompressed_Frame_YCrCb_current = None
                is_current_frame_key = (i % current_key_frame_interval) == 0

                try:
                    if is_current_frame_key:
                        Compressed_KF = compress_KeyFrame(Current_Frame_Layers, current_use_lossless,
                                                          current_lossless_method)
                        Decompressed_Frame_YCrCb_current = decompress_KeyFrame(Compressed_KF, current_subsampling,
                                                                               current_use_lossless,
                                                                               current_lossless_method)
                        if Decompressed_Frame_YCrCb_current is not None:
                            Last_KeyFrame_Decompressed_YCrCb = Decompressed_Frame_YCrCb_current.copy()
                        else:
                            print(f"ERROR: KF decompress {i}."); break

                        if current_use_lossless:
                            orig_y_b = Current_Frame_Layers.Y.nbytes;
                            orig_cb_b = Current_Frame_Layers.Cb.nbytes if Current_Frame_Layers.Cb is not None else 0;
                            orig_cr_b = Current_Frame_Layers.Cr.nbytes if Current_Frame_Layers.Cr is not None else 0
                            comp_y_b = Compressed_KF.Y_compressed_size;
                            comp_cb_b = Compressed_KF.Cb_compressed_size;
                            comp_cr_b = Compressed_KF.Cr_compressed_size
                            compression_stats['Y_gain'].append(
                                (1 - comp_y_b / (orig_y_b + EPS)) * 100 if orig_y_b > 0 else 0)
                            compression_stats['Cb_gain'].append(
                                (1 - comp_cb_b / (orig_cb_b + EPS)) * 100 if orig_cb_b > 0 else 0)
                            compression_stats['Cr_gain'].append(
                                (1 - comp_cr_b / (orig_cr_b + EPS)) * 100 if orig_cr_b > 0 else 0)
                            compression_stats['is_keyframe'].append(True)
                    else:
                        if Last_KeyFrame_Decompressed_YCrCb is None: print(
                            f"Warning: No prev DECOMPRESSED KF for P-Frame {i}."); break
                        Compressed_PF = compress_not_KeyFrame(Current_Frame_Layers, Last_KeyFrame_Decompressed_YCrCb,
                                                              current_subsampling, current_dzielnik,
                                                              current_use_lossless, current_lossless_method)
                        Decompressed_Frame_YCrCb_current = decompress_not_KeyFrame(Compressed_PF,
                                                                                   Last_KeyFrame_Decompressed_YCrCb,
                                                                                   current_subsampling,
                                                                                   current_dzielnik,
                                                                                   current_use_lossless,
                                                                                   current_lossless_method)
                        if Decompressed_Frame_YCrCb_current is None: print(f"ERROR: PF decompress {i}."); break

                        if current_use_lossless:
                            # For P-frames, original size for gain is based on the diff signal before RLE
                            # But PDF asks for gain based on original frame layer sizes for comparison.
                            # Let's use original frame layers' sizes for consistency with KF, acknowledging this isn't pure RLE gain on diff data.
                            # Alternative: calculate size of Diff_Y.astype(np.int16) etc. before RLE.
                            # For now, sticking to Current_Frame_Layers for consistency with how KF gain might be interpreted from instructions.
                            # A more accurate "RLE gain on diff signal" would compare Compressed_PF.Y_compressed_size to Y_diff_to_store.nbytes.
                            orig_y_b = Current_Frame_Layers.Y.nbytes;
                            orig_cb_b = Current_Frame_Layers.Cb.nbytes if Current_Frame_Layers.Cb is not None else 0;
                            orig_cr_b = Current_Frame_Layers.Cr.nbytes if Current_Frame_Layers.Cr is not None else 0
                            comp_y_b = Compressed_PF.Y_compressed_size;
                            comp_cb_b = Compressed_PF.Cb_compressed_size;
                            comp_cr_b = Compressed_PF.Cr_compressed_size
                            compression_stats['Y_gain'].append(
                                (1 - comp_y_b / (orig_y_b + EPS)) * 100 if orig_y_b > 0 else 0)
                            compression_stats['Cb_gain'].append(
                                (1 - comp_cb_b / (orig_cb_b + EPS)) * 100 if orig_cb_b > 0 else 0)
                            compression_stats['Cr_gain'].append(
                                (1 - comp_cr_b / (orig_cr_b + EPS)) * 100 if orig_cr_b > 0 else 0)
                            compression_stats['is_keyframe'].append(False)

                    if wyswietlaj_klatki_live and Decompressed_Frame_YCrCb_current is not None:
                        cv2.imshow('Decompressed', cv2.cvtColor(Decompressed_Frame_YCrCb_current, cv2.COLOR_YCrCb2BGR))
                        cv2.imshow('Original', frame_bgr)
                        if cv2.waitKey(10) & 0xFF == ord('q'): print(
                            "Interrupted."); cap.release(); cv2.destroyAllWindows(); exit()

                    if TRYB == 1 and Decompressed_Frame_YCrCb_current is not None and np.any(
                            current_plot_frames_list == i):
                        for roi_idx, roi_coords_val in enumerate(ROI_LIST):
                            plot_suffix_params = f"_ss{current_subsampling.replace(':', '')}_div{current_dzielnik}"
                            plotDiffrence(frame_ycrcb_original, Decompressed_Frame_YCrCb_current, roi_coords_val, i,
                                          roi_idx + 1,
                                          save_dir_base=OUTPUT_DIR, suffix_params=plot_suffix_params)
                except Exception as e_frame:
                    print(f"ERROR processing frame {i} in {current_video_file_for_plot}: {e_frame}");
                    traceback.print_exc();
                    break
            cap.release()

            if TRYB == 2 and current_use_lossless and compression_stats['Y_gain']:
                frames_axis = np.arange(len(compression_stats['Y_gain']))
                keyframe_indices_bool = np.array(compression_stats['is_keyframe'])
                plt.figure(figsize=(12, 7));
                plt.plot(frames_axis, compression_stats['Y_gain'], label='Y Gain (%)', marker='.')
                plt.plot(frames_axis, compression_stats['Cb_gain'], label='Cb Gain (%)', marker='.')
                plt.plot(frames_axis, compression_stats['Cr_gain'], label='Cr Gain (%)', marker='.')
                first_kf_marked = False
                for kf_idx_val in frames_axis[keyframe_indices_bool]:
                    plt.axvline(x=kf_idx_val, color='r', linestyle='--', alpha=0.6,
                                label='KeyFrame' if not first_kf_marked else "")
                    first_kf_marked = True
                plt.xlabel("Numer Klatki");
                plt.ylabel("% Zysk Pamięci (po RLE względem warstwy przed RLE)")
                title_info = f"Zysk Kompresji RLE dla: {os.path.basename(current_video_file_for_plot)}\n(SS={current_subsampling}, Dzielnik Różnicy={current_dzielnik}, Interwał KF={current_key_frame_interval})"
                # Dodanie informacji o metodzie RLE w tytule wykresu zgodnie z PDF
                title_info += f"\nMetoda kompresji bezstratnej: {current_lossless_method}"
                plt.title(title_info, fontsize=11)
                plt.legend(loc='best');
                plt.grid(True, linestyle=':', alpha=0.7)
                all_gains = compression_stats['Y_gain'] + compression_stats['Cb_gain'] + compression_stats['Cr_gain']
                min_gain = min(all_gains) if all_gains else -25;
                max_gain = max(all_gains) if all_gains else 100
                plt.ylim(min(min_gain - 10, -25), max(max_gain + 10, 100));
                plt.tight_layout()
                comp_plot_filename = f"compression_stats_{os.path.splitext(os.path.basename(current_video_file_for_plot))[0]}_ss{current_subsampling.replace(':', '')}_div{current_dzielnik}_kf{current_key_frame_interval}.png"
                comp_save_path = os.path.join(OUTPUT_DIR, comp_plot_filename)
                plt.savefig(comp_save_path);
                print(f"  Zapisano wykres statystyk RLE: {comp_save_path}");
                plt.close()
    if wyswietlaj_klatki_live: cv2.destroyAllWindows()
    print("\n--- Skrypt zakończył działanie ---")