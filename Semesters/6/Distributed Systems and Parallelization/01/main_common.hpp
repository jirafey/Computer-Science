#ifndef MAIN_COMMON_HPP
#define MAIN_COMMON_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <omp.h>
#include <cmath>
#include <limits>

using namespace std;


int** createMatrix(const int rows, const int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void deleteMatrix(int** matrix, const int rows) {
     if (!matrix) return;
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void initializeMatrix(int** matrix, const int rows, const int cols) {
    if (!matrix) return;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = 0;
        }
    }
}

int** readMatrix(const string& filename, int& rows, int& cols) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        rows = cols = -1;
        return nullptr;
    }
    if (!(file >> rows >> cols)) {
         cerr << "Error: Could not read dimensions from " << filename << endl;
         rows = cols = -1;
         file.close();
         return nullptr;
    }
     if (rows <= 0 || cols <= 0) {
        cerr << "Error: Invalid dimensions read from " << filename << " (" << rows << "x" << cols << ")" << endl;
        rows = cols = -1;
        file.close();
        return nullptr;
    }

    int** matrix = createMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
             if (!(file >> matrix[i][j])) {
                cerr << "Error: Failed to read element (" << i << "," << j << ") from " << filename << endl;
                file.close();
                deleteMatrix(matrix, rows);
                rows = cols = -1;
                return nullptr;
            }
        }
    }
    file.close();
    return matrix;
}

void writeMatrixToFile(const string& filename, const int& rows, const int& cols, int** resultMatrix) {
   ofstream file(filename);
   if (!file) {
        cerr << "Error: Cannot open file " << filename << " for writing." << endl;
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file << resultMatrix[i][j] << (j == cols - 1 ? "" : " ");
        }
        file << endl;
    }
    file.close();
}

bool compareMatrices(int** mat1, int** mat2, const int rows, const int cols) {
    if (!mat1 || !mat2) return false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (mat1[i][j] != mat2[i][j]) {
                cerr << "Verification Failed: Mismatch at [" << i << "][" << j << "] -> "
                     << "Seq=" << mat1[i][j] << ", Par=" << mat2[i][j] << endl;
                return false;
            }
        }
    }
    return true;
}


void multiplyMatrices_sequential(int** mat1, int** mat2, int** result, const int& rows, const int& cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < cols; k++) {
                 result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}


#endif // MAIN_COMMON_HPP