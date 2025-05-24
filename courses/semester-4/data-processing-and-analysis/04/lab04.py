from typing import Tuple, Any

import numpy as np
import matplotlib.pyplot as plt

import matplotlib.image as mpimg
from numpy import ndarray, dtype
from skimage import io, color
from scipy.signal import find_peaks

def generate_discretized_sine_wave(f: int, Fs: int) -> tuple[ndarray[Any, dtype[Any]], Any]:
    dt = 1 / Fs
    t = np.arange(0, 1, dt)
    s = np.sin(2 * np.pi * f * t)
    return t, s

# Częstotliwość sygnału sinusoidalnego
frequency = 10

# Częstotliwości próbkowania
sampling_frequencies = [20, 21, 30, 45, 50, 100, 150, 200, 250, 1000]

for Fs in sampling_frequencies:
    t, s = generate_discretized_sine_wave(frequency, Fs)
    plt.figure()
    plt.plot(t, s)
    plt.xlabel('Czas [s]')
    plt.ylabel('Amplituda')
    plt.title(f'Zdyskretyzowany sygnał sinusoidalny (f = {frequency} Hz, Fs = {Fs} Hz)')
    plt.show()
#  twierdzenie Nyquista-Shannona.

# aliasing.


# Open and display the image
img:ndarray = mpimg.imread('robal.png')
img2: ndarray = mpimg.imread('robal.png')
img3: ndarray = mpimg.imread('robal.png')
img4: ndarray = mpimg.imread('robal.png')
# plt.imshow(img)
# plt.axis('off')  # Turn off axis numbers and ticks
# plt.show()


# KWANTYZACJA

print(img.ndim)

shape = img.shape

print(shape[2])

def grayscale():
    i: int
    j: int
    for i in range(0, img.shape[0]):
        for j in range(0, img.shape[1]):
            a = img2[i][j]
            b = img3[i][j]
            c = img3[i][j]
            img2[i][j] = (max(a[0], a[1], a[2]) + min(a[0], a[1], a[2])) / 2
            img3[i][j] = (b[0] + b[1] + b[2]) / 3
            img4[i][j] = (c[0] * 0.21) + (c[1] * 0.72) + (c[2] * 0.07)

    for i in [img2, img3, img4]:
        plt.imshow(i)
        plt.axis('off')  # Turn off axis numbers and ticks
        plt.show()

gray_images = [img2, img3, img4]
# grayscale()
# Wygeneruj histogram dla każdego z otrzymanych „szarych” obrazów (funkcja histogram z pakietu numpy)
for i, gray_image in enumerate(gray_images):
    plt.figure()
    plt.imshow(gray_image, cmap='gray')
    plt.axis('off')
    plt.title(f'Obraz {i + 1}')
    plt.show()

    histogram, bins = np.histogram(gray_image.flatten(), bins=256, range=(0, 1))
    plt.bar(bins[:-1], histogram, width=1)
    plt.title(f'Histogram obrazu {i + 1}')
    plt.xlabel('Wartość piksela')
    plt.ylabel('Liczba pikseli')
    plt.show()


# Funkcja generująca różne poziomy szarości obrazów
def generuj_obrazy_szarosci(obraz):
    obrazy_szarosci = []
    for czynnik in [0.5, 0.75, 1.0]:
        obraz_szarosci = np.dot(obraz[..., :3], [0.299, 0.587, 0.114]) * czynnik
        obrazy_szarosci.append(obraz_szarosci)
    return obrazy_szarosci


# Funkcja redukująca liczbę kolorów na histogramie i generująca nowy obrazek
def redukuj_kolory_na_histogramie(obraz, liczba_kolorow):
    histogram, przedzialy = np.histogram(obraz.flatten(), bins=liczba_kolorow, range=(0, 1))
    srodki_przedzialow = (przedzialy[:-1] + przedzialy[1:]) / 2
    nowy_obraz = np.zeros_like(obraz)
    for i in range(liczba_kolorow):
        nowy_obraz[(obraz >= przedzialy[i]) & (obraz <= przedzialy[i + 1])] = srodki_przedzialow[i]
    return nowy_obraz


# Wczytanie obrazu
obraz = plt.imread('robal.png')

# Generowanie obrazów o różnych poziomach szarości
obrazy_szarosci = generuj_obrazy_szarosci(obraz)

# Wyświetlenie i obliczenie histogramów dla każdego obrazu
for i, obraz_szarosci in enumerate(obrazy_szarosci):
    plt.figure()
    plt.imshow(obraz_szarosci, cmap='gray')
    plt.axis('off')
    plt.title(f'Obraz {i + 1}')
    plt.show()

    # Obliczenie i wyświetlenie histogramu zredukowanego do 16 kolorów
    histogram, przedzialy = np.histogram(obraz_szarosci.flatten(), bins=16, range=(0, 1))
    plt.bar(przedzialy[:-1], histogram, width=1 / 16, align='edge')
    plt.title(f'Histogram obrazu {i + 1} (16 kolorów)')
    plt.xlabel('Wartość piksela')
    plt.ylabel('Liczba pikseli')
    plt.xticks(np.linspace(0, 1, num=17))  # Ustawienie etykiet na osi X
    plt.show()

    # Generowanie nowego obrazu zredukowanego do 16 kolorów
    obraz_zredukowany = redukuj_kolory_na_histogramie(obraz_szarosci, 16)
    plt.imshow(obraz_zredukowany, cmap='gray')
    plt.axis('off')
    plt.title(f'Obraz {i + 1} zredukowany do 16 kolorów')
    plt.show()

# Binaryzacjaę

obraz = io.imread('tiger.png')

# Wygenerowanie obrazów o różnych poziomach szarości
obrazy_szarosci = generuj_obrazy_szarosci(obraz)

# Wyświetlenie i obliczenie histogramów dla każdego obrazu
for i, obraz_szarosci in enumerate(obrazy_szarosci):
    plt.figure()
    plt.imshow(obraz_szarosci, cmap='gray')
    plt.axis('off')
    plt.title(f'Obraz {i + 1}')
    plt.show()

    # Obliczenie i wyświetlenie histogramu dla obrazu w skali szarości
    histogram, bins = np.histogram(obraz_szarosci.flatten(), bins=256, range=(0, 1))
    plt.bar(bins[:-1], histogram, width=1)
    plt.title(f'Histogram obrazu {i + 1}')
    plt.xlabel('Wartość piksela')
    plt.ylabel('Liczba pikseli')
    plt.show()