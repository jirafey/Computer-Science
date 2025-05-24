#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Użytkownik wprowadza wymiary macierzy
//Inicjalizacja macierzy losowymi wartościami
//Mnożymy macierze
//Wyświetlamy na ekran
//Sprzątamy po sobie


// Random number generator function with inclusive limits.

// Insert random numbers into a specified size of a matrix.

int get_rows(){
    int rows;
    printf("Insert a specified amount of rows: \n");
    scanf_s("%d", &rows);
    if (rows< 0){
        get_rows();
    }
    return rows;
}
int get_columns() {
    int columns;
    printf("Insert a specified amount of columns: \n");
    scanf_s("%d", &columns);
    return columns;
}
int **random_matrix(int rows, int columns) {


//    int **matrix[rows+1][columns+1];
//    int (**matrix) =  malloc((rows * columns) * sizeof(int));

    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 1; i < rows; i++) {
        matrix[i] = (int*)malloc(columns * sizeof(int));
    }
    int i, j;


    for (i = 1; i <= rows; i++) {
        for (j = 1; j <= columns; j++) {
            matrix[i][j] = rand() % 101;
        }
    }
    return matrix;
}
void print_matrix(int **matrix, int rows, int columns) {

    int i, j;

    for (i = 1; i <= rows; i++) {
        printf("\n");
        for (j = 1; j <= columns; j++) {
            if (matrix[i][j] < 10) {
                printf("  %d ", matrix[i][j]);
            } else if (matrix[i][j] < 100) {
                printf(" %d ", matrix[i][j]);
            } else {
                printf("%d ", matrix[i][j]);

            }
        }
    }
}
// Main function.
    int main() {


    // Use current time as seed for random generator.
    srand(time(NULL));
    // Call the function to insert random values (0-100) into a matrix.
    int matrix_A_rows = get_rows();
    int matrix_A_columns = get_columns();


    printf("Wymiary macierzy A to: %dx%d\n", matrix_A_rows, matrix_A_columns);
    int matrix_B_rows = get_rows();
    int matrix_B_columns = get_columns();

    printf("Wymiary macierzy B to: %dx%d\n", matrix_B_rows, matrix_B_columns);


    int **matrix_A = random_matrix( matrix_A_rows, matrix_A_columns);

    printf("Matrix_A:\n");
    print_matrix(matrix_A, matrix_A_rows, matrix_A_columns);
    printf("Matrix_B:\n");
    int **matrix_B = random_matrix(matrix_B_columns, matrix_B_rows);
    print_matrix(matrix_B, matrix_B_columns, matrix_B_rows);
    free(matrix_A);
    free(matrix_B);
//    free();
    return 0;
    }
