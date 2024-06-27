from sklearn.datasets import make_classification;
import matplotlib.pyplot as plt;
import numpy as np;
from sklearn.model_selection import train_test_split, GridSearchCV;
from sklearn.metrics import accuracy_score, recall_score, precision_score, f1_score, roc_auc_score, roc_curve;
import pandas as pd;
import time;
from sklearn.naive_bayes import GaussianNB;
from sklearn.discriminant_analysis import QuadraticDiscriminantAnalysis;
from sklearn.neighbors import KNeighborsClassifier;
from sklearn.svm import SVC;
from sklearn.tree import DecisionTreeClassifier;


def exercise01():
    dataX, dataY = make_classification(n_samples=3000,
                                       n_features=2,
                                       n_informative=2,
                                       n_classes=2,
                                       n_clusters_per_class=2,
                                       n_redundant=0,
                                       n_repeated=0,
                                       random_state=15);

    plt.scatter(dataX[:, 0], dataX[:, 1], c=dataY, marker='o', edgecolor='k');
    plt.title("Generated Data");
    plt.xlabel("Feature 1");
    plt.ylabel("Feature 2");
    plt.show();

    return dataX, dataY;


def evaluate_classifiers_multiple_splits(X, y):
    classifiers = [
        ("GaussianNB", GaussianNB()),
        ("QuadraticDiscriminantAnalysis", QuadraticDiscriminantAnalysis()),
        ("KNeighborsClassifier", KNeighborsClassifier()),
        ("SVC", SVC(probability=True)),
        ("DecisionTreeClassifier", DecisionTreeClassifier())
    ];

    results = {};
    for name, _ in classifiers:
        results[name] = [];

    for iteration in range(100):
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=iteration);

        for name, clf in classifiers:
            start_train = time.time();
            clf.fit(X_train, y_train);
            train_duration = time.time() - start_train;

            start_test = time.time();
            y_pred = clf.predict(X_test);
            test_duration = time.time() - start_test;

            accuracy = accuracy_score(y_test, y_pred);
            recall = recall_score(y_test, y_pred, average='binary');
            precision = precision_score(y_test, y_pred, average='binary');
            f1 = f1_score(y_test, y_pred, average='binary');

            if hasattr(clf, "predict_proba"):
                y_pred_proba = clf.predict_proba(X_test)[:, 1];
                roc_auc = roc_auc_score(y_test, y_pred_proba);
            else:
                y_pred_decision = clf.decision_function(X_test);
                roc_auc = roc_auc_score(y_test, y_pred_decision);

            results[name].append([train_duration, test_duration, accuracy, recall, precision, f1, roc_auc]);

    summary_df = {};
    for name, scores in results.items():
        summary_df[name] = pd.DataFrame(scores, columns=['Train Time', 'Test Time', 'Accuracy', 'Recall', 'Precision',
                                                         'F1 Score', 'ROC AUC']);

    return summary_df;


def plot_classification_errors(X_test, y_test, y_pred):
    plt.scatter(X_test[:, 0], X_test[:, 1], c=y_test == y_pred, cmap='coolwarm', marker='o', edgecolor='k');
    plt.title("Classification Errors");
    plt.xlabel("Feature 1");
    plt.ylabel("Feature 2");
    plt.show();


def plot_roc_curve(y_test, y_pred_proba):
    fpr, tpr, _ = roc_curve(y_test, y_pred_proba);
    plt.plot(fpr, tpr, marker='.');
    plt.title("ROC Curve");
    plt.xlabel("False Positive Rate");
    plt.ylabel("True Positive Rate");
    plt.show();


def plot_decision_boundary(clf, X, y):
    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1;
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1;
    xx, yy = np.meshgrid(np.arange(x_min, x_max, 0.01),
                         np.arange(y_min, y_max, 0.01));
    Z = clf.predict(np.c_[xx.ravel(), yy.ravel()]);
    Z = Z.reshape(xx.shape);
    plt.contourf(xx, yy, Z, alpha=0.8);
    plt.scatter(X[:, 0], X[:, 1], c=y, edgecolor='k', marker='o');
    plt.title("Decision Boundary");
    plt.xlabel("Feature 1");
    plt.ylabel("Feature 2");
    plt.show();


def exercise02():
    dataX, dataY = make_classification(n_samples=200,
                                       n_features=2,
                                       n_informative=2,
                                       n_classes=2,
                                       n_clusters_per_class=1,
                                       n_redundant=0,
                                       n_repeated=0,
                                       random_state=42);

    classifier = SVC(probability=True);

    param_grid = {
        'C': [0.1, 1, 10, 100],
        'gamma': [1, 0.1, 0.01, 0.001],
        'kernel': ['rbf']
    };

    grid_search = GridSearchCV(classifier, param_grid, scoring='roc_auc', cv=5);
    grid_search.fit(dataX, dataY);

    best_params = grid_search.best_params_;
    print(f"Best parameters: {best_params}");

    classifier.set_params(**best_params);

    results = [];
    for iteration in range(100):
        X_train, X_test, y_train, y_test = train_test_split(dataX, dataY, test_size=0.3, random_state=iteration);

        start_train = time.time();
        classifier.fit(X_train, y_train);
        train_duration = time.time() - start_train;

        start_test = time.time();
        y_pred = classifier.predict(X_test);
        test_duration = time.time() - start_test;

        accuracy = accuracy_score(y_test, y_pred);
        recall = recall_score(y_test, y_pred, average='binary');
        precision = precision_score(y_test, y_pred, average='binary');
        f1 = f1_score(y_test, y_pred, average='binary');

        y_pred_proba = classifier.predict_proba(X_test)[:, 1];
        roc_auc = roc_auc_score(y_test, y_pred_proba);

        results.append([train_duration, test_duration, accuracy, recall, precision, f1, roc_auc]);

    results_df = pd.DataFrame(results, columns=['Train Time', 'Test Time', 'Accuracy', 'Recall', 'Precision',
                                                'F1 Score', 'ROC AUC']);

    avg_results = results_df.mean();
    print(f"Average results for SVC with optimal parameters:\n{avg_results}\n");

    X_train, X_test, y_train, y_test = train_test_split(dataX, dataY, test_size=0.3, random_state=99);
    classifier.fit(X_train, y_train);
    y_pred = classifier.predict(X_test);
    y_pred_proba = classifier.predict_proba(X_test)[:, 1];

    plot_classification_errors(X_test, y_test, y_pred);
    plot_roc_curve(y_test, y_pred_proba);
    plot_decision_boundary(classifier, dataX, dataY);


if __name__ == '__main__':
    X, y = exercise01();
    results_summary = evaluate_classifiers_multiple_splits(X, y);
    for name, df in results_summary.items():
        print(f"Average results for {name}:\n{df.mean()}\n");

    exercise02();
