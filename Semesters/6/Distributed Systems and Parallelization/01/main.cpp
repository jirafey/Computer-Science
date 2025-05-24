#include <fstream>
#include <iostream>
#include <omp.h>
using namespace std;

void multiplyMatrices(int** mat1, int** mat2, int** result, const int &rows, const int &cols) {
    // Inicjalizacja elementów macierzy wynikowej na 0
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = 0;
        }
    }
    // 0
# pragma omp parallel shared(result)
    {
        // 1
        # pragma omp for
        for (int i = 0; i < rows; i++) {
            // 2
            # pragma omp for
            for (int j = 0; j < cols; j++) {
                // 3
                # pragma omp for
                for (int k = 0; k < cols; k++) {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
    }
}

void multiplyMatrices_sequential(int** mat1, int** mat2, int** result, const int &rows, const int &cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = 0;
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < cols; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}


int** createMatrix(const int rows, const int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void deleteMatrix(int** matrix, const int rows) {

    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(int** matrix, const int rows, const int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
int** readMatrix(const string &filename, int rows, int cols) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return nullptr;
    }
    file >> rows >> cols;
    int** matrix = createMatrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file >> matrix[i][j];
        }
    }
    file.close();
    return matrix;
}
void readMatrixDimensions(const string &filename, int& rows, int& cols) {

    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        rows = cols = -1;  // Error indicator
        return;
    }
    file >> rows >> cols;
    file.close();
}

void writeMatrixToFile(const string &filename, const int& rows, const int& cols, int** resultMatrix) {
    ofstream file;
    file.open(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << " for writing." << endl;
        return;
    }
    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
            file << resultMatrix[i][j]<< " ";
        }
        file<<endl;
    }
    file.close();
}

int main(int argc, char** argv) {
    int threadnum = atoi(argv[1]);
    string textbuffer;
    string filenameA = "Macierze/100_100.txt";
    string filenameB = "Macierze/100_100.txt";
    string filenameC = "Macierze/OUTPUT_100_100.txt";
    int rows, cols;
    readMatrixDimensions(filenameA, rows, cols);

    if (rows <= 0 || cols <= 0) {
        cerr << "Error: Failed to read valid matrix dimensions from " << filenameA << endl;
        return 1;
    }

    int** matrixA = nullptr;
    int** matrixB = nullptr;

    #pragma omp parallel sections shared(matrixA, matrixB, filenameA, filenameB, rows, cols) default(none)
    {
        #pragma omp section
        {
            matrixA = readMatrix(filenameA, rows, cols);
        }

        #pragma omp section
        {
            matrixB = readMatrix(filenameB, rows, cols);

        }
    }

        int** result = createMatrix(rows, cols);

        double start_sequential = omp_get_wtime();
        multiplyMatrices_sequential(matrixA, matrixB, result, rows, cols);
        double end_sequential = omp_get_wtime();
        cout<<"Time"<<(end_sequential-start_sequential)*1000 << "threads: "<< threadnum <<"size of matrix: "<<rows<<"x"<<cols<<endl;

        double start = omp_get_wtime();
        multiplyMatrices(matrixA, matrixB, result, rows, cols);
        double end = omp_get_wtime();
        cout<<"Time"<<(end-start)*1000 << "threads: "<< threadnum <<"size of matrix: "<<rows<<"x"<<cols<<endl;

        // printMatrix(result, rows, cols);
        writeMatrixToFile(filenameC, rows, cols, result);
        deleteMatrix(matrixA, rows);
        deleteMatrix(matrixB, rows);
        deleteMatrix(result, rows);
        return 0;
    }



// wczytac z pliku macierze i zapisac do pliku macierz wynikowa 1-10 wartosci wystarczy
// przeczytac macierze i zarezerwowac pamiec dynamicznie
// malloc alloc
// bez wyswietlania na ekran
// nie printowac nie trzeba ostatecznie
// nazwa na sztywno moze byc albo argument do programu
// mamy programowanie rowsnolegle i wspolbiezne

// dwie pierwsze wartosci calkowite to wymair macierzy
// po spacjach wartosci i po enterach

// jedno z nich niepoprawnie sie zrownolegla
// porownac z sekwencyjnym
// porownanie tablic?
// po rozpisaniu ilus tam operacji
// albo matematycznie
// 0.5 oceny wyzej jak matme uzyje

// 8 16 1000x 2000x static i tak dla 8 16 robic mimo ze 12
// schedule static 10 50 100 dynamic 10 50 100 guided 10 50 100
// runtime system by robilo to
// zrownoleglic odczyt z pliku jeden plik przez jeden watek a drugi przez drugi
// a same pliki sekwencyjne
// plik a i b
// plik a przez 1 watek a b przez drugi watek rownolegle wzgledem siebie
// fragmenty kodu z prgamami (ze zrownolegleniem)
// private shared firs private zadeklarowac jaki maja zakres moze byc default
// zadeklarowac (i, j) jaki ma zakres jawny

// fragemtn 1 wersji calych petli
// fragment 2 wersji calych petli
// fragment 3 wersji calych petli

// analiza zaleznosci

// wnioski
// dane o komputerze pamiec operacyjna
// 3 kwietnia podesla krzysztof.siedlecki
// 27 marca fajrant
