import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.metrics import silhouette_score

def load_dataset():
    data = pd.read_csv('autos.csv')
    width = data['width'].values
    length = data['length'].values
    dataset = np.array(list(zip(width, length)))
    return dataset


def distp(a, b):
    return np.sqrt(sum((a - b) ** 2))


def k_means(k):
    dataset = load_dataset()
    centroids = dataset[np.random.choice(dataset.shape[0], size=k, replace=False)]
    while True:
        distances = np.array([distp(point, centroid) for point in dataset for centroid in centroids])
        assignments = np.argmin(distances.reshape(dataset.shape[0], k), axis=1)
        new_centroids = np.array([dataset[assignments == i].mean(axis=0) for i in range(k)])
        if np.allclose(centroids, new_centroids):
            break
        centroids = new_centroids
    return centroids, assignments


def visualize_clusters(centroids, assignments, dataset):
    plt.scatter(dataset[:, 0], dataset[:, 1], c=assignments, cmap='viridis')
    plt.scatter(centroids[:, 0], centroids[:, 1], c='red', marker='x')
    plt.title('K-Means Clustering')
    plt.xlabel('Width')
    plt.ylabel('Length')
    plt.show()


def calculate_F_C(centroids, assignments, dataset):
    sum_distances_between_centroids = np.sum(
        [distp(centroids[i], centroids[j]) for i in range(len(centroids)) for j in
         range(i + 1, len(centroids))])

    # Calculate the sum of squared distances from each point to its centroid
    ssd = np.sum([np.sum((dataset[assignments == i] - centroids[i]) ** 2) for i in range(len(centroids))])

    # Calculate F(C)
    F_C = sum_distances_between_centroids / ssd
    return F_C


if __name__ == '__main__':
    k = 4
    centroids, assignments = k_means(k)
    dataset = load_dataset()
    visualize_clusters(centroids, assignments, dataset)

    # Calculate and print the Silhouette Score
    F_C_value = calculate_F_C(centroids, assignments, dataset)
    print("F(C) value:\n", F_C_value)
    # Optionally, print the centroids and assignments
    print("Centroids:\n", centroids, "\n")
    print("Assignments:\n", assignments, "\n")
