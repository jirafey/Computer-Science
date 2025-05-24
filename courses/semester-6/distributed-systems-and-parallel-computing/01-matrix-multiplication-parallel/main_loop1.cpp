#include "main_common.hpp"

void multiplyMatrices_parallel(int** mat1, int** mat2, int** result, const int& rows, const int& cols) {
    #pragma omp parallel for shared(mat1, mat2, result, rows, cols) default(none)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < cols; k++) {
                 result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <num_threads> <matrix_size>" << endl;
        return 1;
    }

    int thread_num = atoi(argv[1]);
    int size = atoi(argv[2]);

    if (thread_num <= 0 || size <= 0) {
        cerr << "Error: Number of threads and matrix size must be positive." << endl;
        return 1;
    }

    omp_set_num_threads(thread_num);

    string filenameA = "matrices/" + to_string(size) + "_" + to_string(size) + ".txt";
    string filenameB = filenameA;
    string filenameC = "matrices/OUTPUT_" + to_string(size) + "_" + to_string(size) + "_L1.txt";

    int rowsA, colsA, rowsB, colsB;

    int** matrixA = readMatrix(filenameA, rowsA, colsA);
    int** matrixB = readMatrix(filenameB, rowsB, colsB);

    if (!matrixA || !matrixB || rowsA != size || colsA != size || rowsB != size || colsB != size) {
         cerr << "Error reading matrices or dimensions mismatch for size " << size << endl;
         deleteMatrix(matrixA, rowsA);
         deleteMatrix(matrixB, rowsB);
         return 1;
    }
     if (colsA != rowsB) {
        cerr << "Error: Matrix dimensions incompatible for multiplication ("
             << rowsA << "x" << colsA << " and " << rowsB << "x" << colsB << ")" << endl;
        deleteMatrix(matrixA, rowsA);
        deleteMatrix(matrixB, rowsB);
        return 1;
    }

    int** result_seq = createMatrix(rowsA, colsB);
    int** result_par = createMatrix(rowsA, colsB);

    initializeMatrix(result_seq, rowsA, colsB);
    double start_sequential = omp_get_wtime();
    multiplyMatrices_sequential(matrixA, matrixB, result_seq, rowsA, colsB);
    double end_sequential = omp_get_wtime();
    double time_sequential = (end_sequential - start_sequential) * 1000.0;

    initializeMatrix(result_par, rowsA, colsB);
    double start_parallel = omp_get_wtime();
    multiplyMatrices_parallel(matrixA, matrixB, result_par, rowsA, colsB);
    double end_parallel = omp_get_wtime();
    double time_parallel = (end_parallel - start_parallel) * 1000.0;

    const char* schedule_env = getenv("OMP_SCHEDULE");
    string schedule_str = schedule_env ? schedule_env : "Default (Static)";

    bool results_match = compareMatrices(result_seq, result_par, rowsA, colsB);
    string verification_status = results_match ? "Match" : "MISMATCH";

    cout << "Size: " << size << "x" << size
         << ", Threads: " << thread_num
         << ", Loop: 1"
         << ", Schedule: " << schedule_str
         << ", Time(Seq): " << time_sequential << " ms"
         << ", Time(Par): " << time_parallel << " ms"
         << ", Verify: " << verification_status
         << endl;

    writeMatrixToFile(filenameC, rowsA, colsB, result_par);

    deleteMatrix(matrixA, rowsA);
    deleteMatrix(matrixB, rowsB);
    deleteMatrix(result_seq, rowsA);
    deleteMatrix(result_par, rowsA);

    return results_match ? 0 : 1;
}