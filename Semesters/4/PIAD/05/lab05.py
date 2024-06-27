import math
import numpy as np
import pandas as pd


# Funkcja obliczająca częstości wystąpień elementów w tablicy x.
def freq(x, prob=True):
    unique_values, counts = np.unique(x, return_counts=True)
    if prob:
        probabilities = counts / len(x)
        return unique_values, probabilities
    else:
        return unique_values, counts


# Funkcja obliczająca częstości wystąpień dla dwóch atrybutów x i y.
def freq2(x, y, prob=True):
    combined_data = np.column_stack((x, y))

    unique_combinations, counts = np.unique(combined_data, axis=0, return_counts=True)

    xi = unique_combinations[:, 0]
    yi = unique_combinations[:, 1]

    if prob:
        total_counts = np.sum(counts)
        probabilities = counts / total_counts
        return xi, yi, probabilities
    else:
        return xi, yi, counts


# Funkcja obliczająca entropię dla tablicy x.
def entropy(x):
    _, probabilities = freq(x)
    h = -sum(p * math.log2(p) for p in probabilities if p != 0)
    return h


# Funkcja obliczająca wzajemną informację między tablicami x i y.
def ixy(x, y):
    hx = entropy(x)
    hy = entropy(y)
    hxy = entropy(list(zip(x, y)))
    ixy = hx + hy - hxy
    return ixy


# Funkcja obliczająca wzajemną informację między tablicami x i y.
def iyx(x, y):
    hx = entropy(x)
    hxy = entropy(list(zip(x, y)))
    iyx = hx - hxy
    return iyx


# Funkcja obliczająca przyrost informacji dla danego atrybutu w danych.
def information_gain(data, attribute):
    total_entropy = entropy(data['type'])
    attribute_entropy = 0
    for value in data[attribute].unique():
        subset = data[data[attribute] == value]
        attribute_entropy += len(subset) / len(data) * entropy(subset['type'])
    return total_entropy - attribute_entropy


if __name__ == '__main__':
    print("a")
    # Wczytanie danych dotyczących zoo.
    zoo_data = pd.read_csv("zoo.csv")
    print(zoo_data["eggs"])
    print(zoo_data["type"])

    # Przykładowe dane
    x = np.array([1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4])
    x2 = np.array(['a', 'b', 'b', 'c', 'c', 'c', 'c', 'd', 'd', 'd', 'd'])
    y2 = np.array([1, 2, 1, 2, 3, 4, 3, 3, 4, 4, 4])

    # Obliczanie częstości
    xi, pi = freq(x)
    print("Unikalne wartości xi:", xi)
    print("Estymowane prawdopodobieństwa pi:", pi)

    xi, ni = freq(x, prob=False)
    print("Unikalne wartości xi:", xi)
    print("Częstości ni:", ni)

    xi, yi, ni = freq2(x2, y2)
    print(xi)
    print(yi)
    print(ni)

    xi, yi, ni = freq2(x2, y2, False)
    print(xi)
    print(yi)
    print(ni)

    # Przykładowe dane
    x = [1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4]
    y = [10, 20, 20, 30, 30, 30, 40, 40, 40, 40, 50]

    # Obliczanie entropii
    h = entropy(x)
    print("Entropia h:", h)

    # Obliczanie wzajemnej informacji
    i = ixy(x, y)
    print("Przyrost informacji i:", i)

    mutual_info = iyx(x, y)
    print("Wzajemna informacja i(Y, X):", mutual_info)


#4


# Funkcja obliczająca przyrost informacji dla dwóch atrybutów
def obliczenie_przyrostu_informacji(atrybut1, atrybut2, dane):
    wartosci_atrybutu1 = dane[atrybut1]
    wartosci_atrybutu2 = dane[atrybut2]
    return iyx(wartosci_atrybutu1, wartosci_atrybutu2)

# Pobranie listy nazw kolumn w zbiorze danych
kolumny = zoo_data.columns.tolist()

# Utworzenie kombinacji dwóch różnych kolumn
kombinacje_kolumn = [(kolumny[i], kolumny[j]) for i in range(len(kolumny)) for j in range(i+1, len(kolumny))]

# Obliczenie przyrostu informacji dla każdej pary kolumn
infogain_dict = {}
for kombinacja in kombinacje_kolumn:
    wartosc_przyrostu = obliczenie_przyrostu_informacji(kombinacja[0], kombinacja[1], zoo_data)
    infogain_dict[kombinacja] = wartosc_przyrostu

# Posortowanie słownika według wartości przyrostu informacji
posortowany_infogain = sorted(infogain_dict.items(), key=lambda x: x[1], reverse=True)

# Wyświetlenie posortowanych wyników przyrostu informacji dla par kolumn
# for kombinacja, wartosc_przyrostu in posortowany_infogain:
#     print("Para kolumn:", kombinacja, "--- Przyrost informacji:", wartosc_przyrostu)
