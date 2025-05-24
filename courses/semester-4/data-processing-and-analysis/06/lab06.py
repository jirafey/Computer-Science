import numpy as np  # Import NumPy library for numerical computations
import matplotlib.pyplot as plt  # Import matplotlib library for plotting
from sklearn import datasets  # Import datasets module from scikit-learn for dataset loading
from sklearn.decomposition import PCA  # Import PCA module from scikit-learn for Principal Component Analysis

def draw_vector(v0, v1, ax=None):
    """
    Draw a vector from point v0 to point v1.

    Parameters:
        v0 (numpy array): Starting point of the vector.
        v1 (numpy array): Ending point of the vector.
        ax (matplotlib axes, optional): Axes to draw the vector on. If None, current axes are used.
    """
    ax = ax or plt.gca()  # If ax is None, set ax to current axes
    arrowprops = dict(arrowstyle='->', linewidth=2, shrinkA=0, shrinkB=0, color='red')  # Arrow properties
    ax.annotate('', v1, v0, arrowprops=arrowprops)  # Annotate the arrow from v0 to v1 on axes ax

def wiPCA(data, n_components=2):
    """
        Perform Principal Component Analysis (PCA) on the given data.

        Args:
            data (ndarray): The input data matrix.
            num_components (int): Number of principal components to retain. Default is 1.

        Returns:
            tuple: A tuple containing:
                - mean_vector (ndarray): Mean vector of the data.
                - selected_components (ndarray): Selected principal components.
                - eigenvalues (ndarray): Eigenvalues corresponding to the selected components.
                - transformed_data (ndarray): Transformed data after dimensionality reduction.
                - reconstructed_data (ndarray): Reconstructed data from the transformed data.

        Covariance Matrix: This is a square matrix that tells us how different variables in our data set vary together.
        Each entry in the covariance matrix represents the covariance between two variables. A positive covariance indicates
        that the variables tend to increase or decrease together, while a negative covariance indicates that they vary in
        opposite directions.

        Eigenvalues and Eigenvectors: When we compute the covariance matrix, we also find its eigenvectors and eigenvalues.
        Eigenvectors are special vectors that, when multiplied by the covariance matrix, give a scalar multiple of themselves.
        These eigenvectors represent the principal axes or directions of maximum variance in the data. Eigenvalues are the
        corresponding scalars that tell us how much variance there is in each eigenvector's direction.

        Selected Components: In PCA (Principal Component Analysis), we aim to reduce the dimensionality of our data by
        selecting a subset of the eigenvectors (principal components) that capture the most variance in the data. These
        components are chosen based on the corresponding eigenvalues. Typically, we select the top num_components eigenvectors
        that correspond to the largest eigenvalues. This ensures that we retain as much variance in the data as possible while
        reducing its dimensionality.
        """
    mean = np.mean(data, axis=0)  # Calculate mean along the specified axis (0 for columns)
    centered_data = data - mean  # Center the data by subtracting the mean
    covariance_matrix = np.cov(centered_data, rowvar=False)  # Compute the covariance matrix
    eigenvalues, eigenvectors = np.linalg.eigh(covariance_matrix)  # Compute eigenvalues and eigenvectors
    sorted_indices = np.argsort(eigenvalues)[::-1]  # Sort eigenvalues in descending order
    eigenvectors = eigenvectors[:, sorted_indices][:, :n_components]  # Select top n_components eigenvectors
    eigenvalues = eigenvalues[sorted_indices][:n_components]  # Select top n_components eigenvalues
    transformed_data = np.dot(centered_data, eigenvectors)  # Project data onto the selected eigenvectors
    reconstructed_data = np.dot(transformed_data, eigenvectors.T) + mean  # Reconstruct data from transformed data
    return mean, eigenvectors, eigenvalues, transformed_data, reconstructed_data  # Return results of PCA

# Generate random data for demonstration
np.random.seed(1)  # Set seed for reproducibility
data = np.dot(np.random.rand(2, 2), np.random.randn(2, 200)).T  # Generate random 2D data

# Perform PCA on the random data
mean, eigenvectors, eigenvalues, projected_data, reconstructed_data = wiPCA(data, n_components=2)

# Plot the original data and principal components
plt.scatter(data[:, 0], data[:, 1], alpha=0.2)  # Plot original data points with transparency
for i in range(len(eigenvalues)):  # Iterate over each principal component
    end_vector = mean + np.sqrt(eigenvalues[i]) * eigenvectors[:, i] * 3  # Compute endpoint of the vector
    draw_vector(mean, end_vector)  # Draw the principal component vector

# Project data onto one principal component for visualization
mean, eigenvectors, _, projected_data, reconstructed_data = wiPCA(data, n_components=1)  # Perform PCA for 1 component
projected_data = np.dot(data - mean, eigenvectors) * eigenvectors.T + mean  # Project data onto 1 principal component
plt.scatter(projected_data[:, 0], projected_data[:, 1], alpha=0.8, color='orange')  # Plot projected data in orange

plt.axis('equal')  # Set equal scaling for x and y axes
plt.title('PCA Visualization')  # Set title of the plot
plt.grid(True)  # Show grid on the plot
plt.legend()  # Show legend
plt.show()  # Display the plot

# Task 2: Perform PCA on the Iris dataset
iris = datasets.load_iris()  # Load Iris dataset
X = iris.data  # Features of the Iris dataset
y = iris.target  # Target labels of the Iris dataset

mean, eigenvectors, eigenvalues, projected_data, reconstructed_data = wiPCA(X, n_components=2)  # Perform PCA

plt.figure(figsize=(8, 6))  # Set figure size for the plot
scatter = plt.scatter(projected_data[:, 0], projected_data[:, 1], c=y, cmap='viridis', edgecolor='none', alpha=0.7)
# Plot projected data with color coding based on target labels
plt.title('PCA on Iris Dataset')  # Set title of the plot
plt.show()  # Display the plot

# Task 3: Perform PCA on the Digits dataset
digits = datasets.load_digits()  # Load Digits dataset
X = digits.data  # Features of the Digits dataset
y = digits.target  # Target labels of the Digits dataset

mean, eigenvectors, eigenvalues, projected_data, reconstructed_data = wiPCA(X, n_components=2)  # Perform PCA

plt.figure(figsize=(10, 8))  # Set figure size for the plot
scatter = plt.scatter(projected_data[:, 0], projected_data[:, 1], c=y, cmap='viridis', edgecolor='none', alpha=0.7)
# Plot projected data with color coding based on target labels
plt.title('PCA on Digits Dataset')  # Set title of the plot
plt.show()  # Display the plot

# Plot variance curve
pca = PCA().fit(X)  # Fit PCA model to the Digits dataset
plt.plot(np.cumsum(pca.explained_variance_ratio_), marker='o', linestyle='-')  # Plot cumulative explained variance
plt.title('Variance Curve')  # Set title of the plot
plt.grid(True)  # Show grid on the plot
plt.show()  # Display the plot

def calculate_reconstruction_errors(data, max_n_components):
    """
    Calculate reconstruction errors for different numbers of principal components.

    Parameters:
        data (numpy array): Input data matrix.
        max_n_components (int): Maximum number of principal components to consider.

    Returns:
        list: List containing reconstruction errors for each number of components.
    """
    errors = []  # Initialize list to store reconstruction errors
    for n in range(1, max_n_components + 1):  # Iterate over different numbers of components
        _, _, _, _, reconstructed_data = wiPCA(data, n_components=n)  # Perform PCA
        error = np.mean(np.sqrt(np.sum((data - reconstructed_data) ** 2, axis=1)))  # Calculate reconstruction error
        errors.append(error)  # Append reconstruction error to the list
    return errors  # Return list of reconstruction errors

# Calculate and plot reconstruction errors
reconstruction_errors = calculate_reconstruction_errors(X, 64)  # Calculate reconstruction errors for up to 64 components

plt.figure(figsize=(10, 6))  # Set figure size for the plot
plt.plot(range(1, 65), reconstruction_errors)  # Plot reconstruction errors
plt.title('Reconstruction Error')  # Set title of the plot
plt.grid(True)  # Show grid on the plot
plt.show()  # Display the plot
