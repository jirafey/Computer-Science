import numpy as np
from sklearn.base import BaseEstimator, ClassifierMixin


class SimplePerceptron(BaseEstimator, ClassifierMixin):

    def __init__(self, learning_rate=0.1):
        self.learning_rate = learning_rate

    def fit(self, X, y):
        self.classes_ = np.unique(y)
        m, n = X.shape
        yy = np.ones(m, dtype=np.int8)
        yy[y == self.classes_[0]] = -1  # zakladamy, ze klasa nr 0 jest klasa negatywna
        self.w_ = np.zeros(n + 1)
        self.k_ = 0
        X_ext = np.c_[np.ones((m, 1)), X]
        while True:
            E = np.where(self.w_.dot(X_ext.T) * yy <= 0.0)[0] # misclassified points
            if len(E) == 0:
                break
            i = np.random.choice(E) # pick a random misclassified point
            x_i = X_ext[i]
            y_i = yy[i]
            self.w_ = self.w_ + self.learning_rate * y_i * x_i # update the weight
            # w = w + N + yi * xi
            self.k_ += 1 # increment update counter

    def predict(self, X):
        return self.classes_[(self.decision_function(X) > 0.0) * 1]

    def decision_function(self, X):
        m = X.shape[0]
        X_ext = np.c_[np.ones((m, 1)), X] # add bias term
        return self.w_.dot(X_ext.T) # f(x) = w*x
