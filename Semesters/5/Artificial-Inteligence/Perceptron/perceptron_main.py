import numpy as np
from matplotlib import pyplot as plt
import time

from perceptron_1 import SimplePerceptron


def generate_dataset(m: int = 1000):
    """Generate dataset as described in the PDF"""
    X = np.zeros((m, 2))
    X[:, 0] = np.random.uniform(0, 2 * np.pi, m)
    X[:, 1] = np.random.uniform(-1, 1, m)

    # Class assignment based on the rule in the document
    y = np.where(np.abs(np.sin(X[:, 0])) > np.abs(X[:, 1]), -1, 1)

    return X, y


def gaussian_kernel(x, center, sigma=0.5):
    """Gaussian kernel function as described in the document"""
    distance = np.sum((x - center) ** 2)
    return np.exp(-distance / (2 * sigma ** 2))


def transform_data(X, centers, sigma=0.5):
    """Transform input data to higher dimensional feature space"""
    m, n = X.shape
    feature_matrix = np.ones((m, len(centers) + 1))

    for i, x in enumerate(X):
        feature_matrix[i, 1:] = [gaussian_kernel(x, center, sigma) for center in centers]

    return feature_matrix


class NonLinearPerceptron(SimplePerceptron):
    def __init__(self, learning_rate=0.1, centers_count=50, sigma=0.5, max_iterations=1000):
        super().__init__(learning_rate)
        self.centers_count = centers_count
        self.sigma = sigma
        self.max_iterations = max_iterations
        self.fit_time = 0
        self.predict_time = 0

    def fit(self, X, y):
        start_time = time.time()

        # Normalize input features to [-1, 1]
        X = (X - X.min(axis=0)) / (X.max(axis=0) - X.min(axis=0)) * 2 - 1

        # Randomly place centers in the input space
        centers = np.random.uniform(low=-1, high=1, size=(self.centers_count, X.shape[1]))

        # Transform data to feature space
        X_transformed = transform_data(X, centers, self.sigma)

        self.classes_ = np.unique(y)
        m, n = X_transformed.shape
        yy = np.ones(m, dtype=np.int8)
        yy[y == self.classes_[0]] = -1

        self.w_ = np.zeros(n)
        self.k_ = 0

        iteration = 0
        while iteration < self.max_iterations:
            E = np.where(self.w_.dot(X_transformed.T) * yy <= 0.0)[0]
            if len(E) == 0:
                break

            i = np.random.choice(E)
            x_i = X_transformed[i]
            y_i = yy[i]

            self.w_ = self.w_ + self.learning_rate * y_i * x_i
            self.k_ += 1
            iteration += 1

        self.centers_ = centers

        self.fit_time = time.time() - start_time
        return self

    def predict(self, X):
        start_time = time.time()

        # Normalize input features
        X = (X - X.min(axis=0)) / (X.max(axis=0) - X.min(axis=0)) * 2 - 1

        # Transform data using the same centers from training
        X_transformed = transform_data(X, self.centers_, self.sigma)

        predictions = self.classes_[(self.w_.dot(X_transformed.T) > 0.0) * 1]

        self.predict_time = time.time() - start_time
        return predictions


def plot_results(X, y, clf):
    """Create multiple visualizations like in the document"""
    plt.figure(figsize=(15, 5))

    # Original data scatter plot
    plt.subplot(131)
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap='coolwarm')
    plt.title('Original Data')
    plt.xlabel('x1')
    plt.ylabel('x2')

    # Contour plot of decision boundary
    plt.subplot(132)
    x1_grid, x2_grid = np.meshgrid(np.linspace(-1, 1, 100), np.linspace(-1, 1, 100))
    grid_points = np.column_stack([x1_grid.ravel(), x2_grid.ravel()])
    Z = clf.predict(grid_points).reshape(x1_grid.shape)

    plt.contourf(x1_grid, x2_grid, Z, alpha=0.8, cmap='coolwarm')
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap='coolwarm', edgecolors='black')
    plt.title('Decision Boundary')
    plt.xlabel('x1')
    plt.ylabel('x2')

    # Surface plot of weighted sum (without thresholding)
    plt.subplot(133)
    decision_values = np.zeros_like(x1_grid)
    for i in range(x1_grid.shape[0]):
        for j in range(x1_grid.shape[1]):
            point = np.array([x1_grid[i, j], x2_grid[i, j]])
            X_transformed = transform_data(point.reshape(1, -1), clf.centers_, clf.sigma)
            # Extract the scalar value from the dot product result
            decision_values[i, j] = clf.w_.dot(X_transformed.T)[0]

    plt.contourf(x1_grid, x2_grid, decision_values, levels=20, cmap='viridis')
    plt.colorbar()
    plt.title('Weighted Sum Surface')
    plt.xlabel('x1')
    plt.ylabel('x2')

    plt.tight_layout()
    plt.show()


if __name__ == '__main__':
    np.random.seed(0)

    # Generate dataset according to the document
    X, y = generate_dataset(m=1000)

    # Try different configurations as suggested in the document
    configurations = [
        {'centers_count': 20, 'sigma': 1.0, 'max_iterations': 500},
        {'centers_count': 50, 'sigma': 0.5, 'max_iterations': 1000},
        {'centers_count': 100, 'sigma': 0.1, 'max_iterations': 5000}
    ]

    for config in configurations:
        print(f"Configuration: {config}")
        clf = NonLinearPerceptron(**config)

        # Measure fitting time
        clf.fit(X, y)

        print(f"Fitting time: {clf.fit_time:.4f} seconds")
        print(f"Number of updates: {clf.k_}")

        # Measure prediction time
        clf.predict(X)
        print(f"Prediction time: {clf.predict_time:.4f} seconds")

        print(f"Accuracy: {clf.score(X, y):.2%}\n")

        # Visualize results
        plot_results(X, y, clf)
