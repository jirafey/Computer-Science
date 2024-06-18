import sklearn
from sklearn import preprocessing
import sounddevice as sd
import soundfile as sf
import scipy.fftpack
import librosa
import scipy.io.wavfile as wav
from scipy.fftpack import fft
import matplotlib.pyplot as plt
import numpy as np

dir = "audio/"
files = ["8000", "48000", "play_ht", "OSR_us_000_0010_8k"]
ending = ".wav"

audio_input = dir + files[0] + ending

s, fs = sf.read(audio_input, dtype='float32')

if len(s.shape) > 1:
    tab = s[:, 0]
else:
    tab = s
print("Shape of audio signal:", s.shape)
tab_czasu = np.zeros(len(tab))

# Wyświetlić sygnał tak, aby na osi poziomej znajdowała się jednostka czasu [ms]
convert_to_ms = 1000
for i in range(len(tab)):
    tab_czasu[i] = i / fs * convert_to_ms

plt.plot(tab_czasu, s, color='green')
plt.xlabel("time [ms]")
plt.ylabel("signal")
# plt.show()

# Normalize the audio signal to the range [-1, 1]
normalized_signal = s / np.max(np.abs(s) - 0.05)

plt.plot(tab_czasu, normalized_signal, color='green')
plt.xlabel("time [ms]")
plt.ylabel("signal")
plt.show()

# 2.1. Podzielić sygnał na ramki (okna) długości 10 ms i obliczyć dla każdej ramki dwie statystyki – funkcję energii E oraz funkcję przejść przez zero Z :
window_size = int(10 * fs / 1000)

def cut(normalized_signal, window_size):
    okna = []
    for i in range(0, len(normalized_signal), window_size):
        okno = normalized_signal[i:i + window_size]
        okna.append(okno)
    return okna

def energy(okna):
    result = []
    for i in okna:
        energy_val = np.sum(i ** 2)
        result.append(energy_val)
    return result

def zero(okna):
    result = []
    for okno in okna:
        lower_than_zero = 0
        for i in range(len(okno) - 1):
            if okno[i] * okno[i + 1] < 0:
                lower_than_zero += 1
        result.append(lower_than_zero)
    return result

okna = cut(normalized_signal, window_size)
zero_result = zero(okna)
energy_result = energy(okna)
normalized_e = energy_result / np.max(np.abs(energy_result) - 0.05)
normalized_z = zero_result / np.max(np.abs(zero_result) - 0.05)

czas_okien = np.arange(len(okna)) * (window_size / fs) * convert_to_ms

plt.plot(tab_czasu, normalized_signal, color='green', label='Normalized Signal')
plt.plot(czas_okien, normalized_e, color='red', label='Energy')
plt.plot(czas_okien, normalized_z, color='blue', label='Zero Crossings')
plt.xlabel("time [ms]")
plt.ylabel("value")
plt.legend()
plt.show()

# 2.4. Sprawdzić i pokazać wyniki dla okien równych: 5ms, 20ms i 50ms.
for window_size in [5, 20, 50]:
    window_size = int(window_size * fs / 1000)
    okna = cut(normalized_signal, window_size)
    zero_result = zero(okna)
    energy_result = energy(okna)
    normalized_e = energy_result / np.max(np.abs(energy_result) - 0.05)
    normalized_z = zero_result / np.max(np.abs(zero_result) - 0.05)
    czas_okien = np.arange(len(okna)) * (window_size / fs) * convert_to_ms
    plt.plot(tab_czasu, normalized_signal, color='green', label='Normalized Signal')
    plt.plot(czas_okien, normalized_e, color='red', label='Energy')
    plt.plot(czas_okien, normalized_z, color='blue', label='Zero Crossings')
    plt.xlabel("time [ms]")
    plt.ylabel("value")
    plt.legend()
    plt.show()

# 2.5. Podział sygnału na nakładające się ramki (50%)
def overlapping_frames(signal, frame_size, overlap):
    step = frame_size - overlap
    frames = []
    for i in range(0, len(signal) - frame_size + 1, step):
        frames.append(signal[i:i + frame_size])
    return np.array(frames)

overlap = 40  # 50% overlap for frame size 80
frames_50_overlap = overlapping_frames(normalized_signal, 80, overlap)
zero_result_50_overlap = zero(frames_50_overlap)
energy_result_50_overlap = energy(frames_50_overlap)
normalized_e_50_overlap = energy_result_50_overlap / np.max(np.abs(energy_result_50_overlap) - 0.05)
normalized_z_50_overlap = zero_result_50_overlap / np.max(np.abs(zero_result_50_overlap) - 0.05)
czas_okien_50_overlap = np.arange(len(frames_50_overlap)) * (overlap / fs) * convert_to_ms

plt.plot(tab_czasu, normalized_signal, color='green', label='Normalized Signal')
plt.plot(czas_okien_50_overlap, normalized_e_50_overlap, color='red', label='Energy')
plt.plot(czas_okien_50_overlap, normalized_z_50_overlap, color='blue', label='Zero Crossings')
plt.xlabel("time [ms]")
plt.ylabel("value")
plt.legend()
plt.show()

# 3.1. Zlokalizować (manualnie) fragment nagrania stanowiący samogłoskę ustną i skopiować jej fragment długości 2048 próbek do nowej zmiennej.
vowel_start = 10000  # przykładowy początek samogłoski
vowel_end = vowel_start + 2048
vowel_fragment = normalized_signal[vowel_start:vowel_end]

# 3.2. Dokonać maskowania sygnału oknem Hamminga
hamming_window = np.hamming(2048)
windowed_signal = vowel_fragment * hamming_window

# 3.3. Obliczyć logarytmiczne widmo amplitudowe dla badanego (zamaskowanego) okna.
yf = scipy.fftpack.fft(windowed_signal)
amplitude_spectrum = np.abs(yf)
log_amplitude_spectrum = np.log(amplitude_spectrum)


# 3.4. Wyświetlić widmo w taki sposób, aby na osi poziomej znajddowała się jednostka częstotliwości Hz w zakresie 0 - 10000 Hz. Oto kod:
freqs = np.fft.fftfreq(len(log_amplitude_spectrum), 1 / fs)
plt.plot(freqs[:len(freqs)//2], log_amplitude_spectrum[:len(log_amplitude_spectrum)//2])
plt.xlabel("Frequency (Hz)")
plt.ylabel("Log Amplitude")
plt.xlim([0, 10000])
plt.show()

# 3.5. Z wykresu odczytać F0
def find_f0(log_amplitude_spectrum, freqs):
    peaks = (log_amplitude_spectrum[1:-1] > log_amplitude_spectrum[:-2]) & \
            (log_amplitude_spectrum[:-2] > log_amplitude_spectrum[2:])
    peak_indices = np.where(peaks)[0] + 1
    if len(peak_indices) > 0:
        return freqs[peak_indices[0]]
    return None

f0 = find_f0(log_amplitude_spectrum, freqs)
print(f"F0: {f0} Hz")

# 4.1. Zlokalizować fragment nagrania stanowiący samogłoskę ustną i skopiować jej fragment długości 2048 próbek do zmiennej okno.
start_sample = 10000  # Example start sample, adjust based on the actual location of the vowel
okno = normalized_signal[start_sample:start_sample + 2048]

# 4.2. Wyznaczyć dla tego fragmentu p=20 współczynników liniowego filtra LPC.
p = 20
# Wyznaczyć dla tego fragmentu p=20 współczynników liniowego filtra LPC.
a = librosa.lpc(okno, order=p)
print("LPC Coefficients:")
print(a)
# 4.3. Wyznaczyć bieguny filtra LPC.
r = np.roots(a)
print("roots"
      "\n")
print(r)
# 4.4. Uzupełnić otrzymany wektor a długości p, zerami do długości okna sygnału (2048).
a_padded = np.pad(a, (0, 2048 - len(a)), 'constant')

# 4.5. Wyznaczyć wygładzone widmo amplitudowe na bazie wektora a
widmoLPC = np.log(np.abs(fft(a_padded)))
widmoLPC = -widmoLPC  # Odbicie w poziomie

# FFT okna
yf = fft(np.hamming(len(okno)) * okno)
widmo = np.log(np.abs(yf))

# Częstotliwości dla osi x
xf = np.linspace(0.0, fs / 2, len(widmo) // 2)

# Wyświetlenie obu widm na jednym wykresie
plt.plot(xf, widmo[:len(widmo) // 2], label='FFT')
plt.plot(xf, widmoLPC[:len(widmoLPC) // 2], label='LPC', linestyle='--')
plt.xlabel('Częstotliwość (Hz)')
plt.ylabel('Log Amplituda')
plt.legend()
plt.show()