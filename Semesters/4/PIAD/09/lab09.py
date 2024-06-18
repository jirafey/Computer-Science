# https://www.youtube.com/watch?v=rTEtEy5o3X0
# inspiracja ☝️
import numpy as np;
from collections import Counter;
from sklearn.metrics import accuracy_score
def euclidean_distance(a, b):
    return np.sqrt(sum((a - b) ** 2));

class KNN:
    def __init__(self, k=3):
        self.k = k;

    def fit(self, X, y):
        self.X_train = X;
        self.y_train = y;

    def predict(self, X):
        # predictions = [];
        # for x in X:
        #     predictions.append(self._predict(x));
        # Simplified ☝️
        predictions = [self._predict(x) for x in X];
        return predictions;

    def _predict(self, x):
        # calculate the distance
        # distances = [];
        # for x_train in self.X_train:
        #     distances.append(euclidean_distance(x, x_train));
        # Simplified ☝️
        distances = [euclidean_distance(x, x_train) for x_train in self.X_train];

        # get the closest k
        k_indices = np.argsort(distances)[:self.k];

        # k_nearest_labels = [];
        # for i in k_indices:
        #     k_nearest_labels.append(self.y_train[i]);
        # Simplified ☝️
        k_nearest_labels = [self.y_train[i] for i in k_indices];

        # majority vote
        most_common = Counter(k_nearest_labels).most_common();
        return most_common[0][0];

    def score(self, X, y):
        return accuracy_score(y, self.predict(X));

# Zadanie 3.1
from sklearn import datasets
import matplotlib.pyplot as plt
import numpy as np
from statistics import mode
from sklearn import datasets
from sklearn.decomposition import PCA
from sklearn.neighbors import KDTree
import time
import pandas as pd

# copied
X, y = datasets.make_classification(
    n_samples=100,  # liczba próbek
    n_features=2,  # liczba wymiarów (cech)
    n_informative=2,  # cechy ważne w tym przypadku oba wymiary są ważne
    n_redundant=0,  # nadmiarowe funkcje ustawione jako 0. Wszystkie cechy w tym przypadku są unikalne
    n_repeated=0,  # 0 gwarantuje niepowatarzalność cech
    random_state=3  # ustawienie generatora liczb losowych - 3 oznacza generowanie tych samych danych za każdym razem
)
# copied
X_value_samples = 100
# ustalenie zakresu danych
X_min, X_max = np.min(X, axis=0), np.max(X, axis=0)
y_min, y_max = np.min(X, axis=0), np.max(X, axis=0)

# tworzenie zbioru X_valueowego w zakresie wylosowanych danych
X_value1 = np.random.uniform(X_min[0], X_max[0], (X_value_samples, 1))
y_value_2 = np.random.uniform(y_min[1], y_max[1], (X_value_samples, 1))

# zlaczenie zbioru
X_value = np.hstack((X_value1, y_value_2))

#copied
# wizualizacja zbiorow danych
plt.plot(X[y == 0, 0], X[y == 0, 1], 'go', label='Klasa 0')
plt.plot(X[y == 1, 0], X[y == 1, 1], 'ro', label='Klasa 1')

#copied
# wizualizacja punktow X_valueowych
plt.plot(X_value[:, 0], X_value[:, 1], 'yo', label='Testowe')

#copied
plt.legend()
plt.xlabel('Cecha 1')
plt.ylabel('Cecha 2')
plt.title('Zbior danych')
plt.show()

# copied
# Zadanie 3.2
model = KNN(5)
model.fit(X, y)
wynik = model.predict(X_value)
print(wynik)
dokladnosc = model.score(X_value, wynik)
print(dokladnosc)

# copied
# Zadanie 3.3
x0 = np.linspace(X_value[:, 0].min(), X_value[:, 0].max(), 20)
x1 = np.linspace(X_value[:, 1].min(), X_value[:, 1].max(), 20)
XX, YY = np.meshgrid(x0, x1)

siatka = np.vstack((XX.ravel(), YY.ravel())).T
wynik = model.predict(siatka)
plt.plot(X[:, 0][y == 0], X[:, 1][y == 0], 'o')
plt.plot(X[:, 0][y == 1], X[:, 1][y == 1], 'ro')
plt.plot(siatka[:, 0], siatka[:, 1], 'yo')
wynik = np.array(wynik)  # trzeba konwertować, bo reshape nie działa na liście
wynik = wynik.reshape(XX.shape)

plt.contour(XX, YY, wynik)
plt.show()

# copied
# Zadanie 3.4
iris = datasets.load_iris()
X_ir = iris.data
Y_ir = iris.target

# klasyfikacja
iris_model = KNN(7)
iris_model.fit(X_ir, Y_ir)
iris_wynik = iris_model.predict(X_ir)
print(iris_wynik)
print(iris_model.score(X_ir, Y_ir))
transform_result = PCA(2);  # Applying PCA for 2 components 🌀
transformed_data = transform_result.fit_transform(X_ir);

[plt.scatter(transformed_data[Y_ir == i, 0], transformed_data[Y_ir == i, 1]) for i in range(len(iris.target_names))];  # Visualizing transformed data 💫

plt.xlabel('1');
plt.ylabel('1');
plt.title('3.5');

x_min, x_max = transformed_data[:, 0].min(), transformed_data[:, 0].max();
y_min, y_max = transformed_data[:, 1].min(), transformed_data[:, 1].max();

xx, yy = np.meshgrid(np.linspace(x_min, x_max, 100), np.linspace(y_min, y_max, 100));  # Creating a 2D grid 📐

grid_points = np.c_[xx.ravel(), yy.ravel()];
original_points = transform_result.inverse_transform(grid_points);  # Converting grid points back 🔄

Z = iris_model.predict(original_points);
Z = np.array(Z);
Z = Z.reshape(xx.shape);

[plt.scatter(transformed_data[Y_ir == i, 0], transformed_data[Y_ir == i, 1]) for i in range(len(iris.target_names))];  # Scatter plot with contours 🌟

plt.contour(xx, yy, Z);
plt.title('3.5 koncowy');
plt.xlabel('Skladowa glowna 1');
plt.ylabel('Skladowa glowna 2');
plt.show();


# zadanie 4
from sklearn.datasets import fetch_california_housing
import pandas

X, y = fetch_california_housing(return_X_y=True)
ilosc_danych = 1000
X = X[:ilosc_danych]
y = y[:ilosc_danych]