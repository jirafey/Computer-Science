#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


// START: Program that generates matrix_A & matrix_B with random numbers (0-100) & prints them to seperate .txt files
// RESULT: Then it takes those matrixes from these files, multiplies them and prints the result to a .txt file


// Get the number of rows from user input
int get_rows() {
    int rows;
    printf("Insert the number of rows: ");
    scanf_s(" %d", &rows);
    if (rows > 0) {
        return rows;
    }
    else {
        printf("The number of rows must not be less than 1!\n");
        get_rows();
    }
}

// Get the number of columns from user input
int get_columns() {
    int columns;
    printf("Insert the number of columns ");
    scanf_s(" %d", &columns);
    if (columns > 0) {
        return columns;
    }
    else {
        printf("The number of columns must not be less than 1!\n");
        get_columns();
    }
}

// Dynamically allocate memoory for a matrix, fill it in with random numbers (0-100).
int **fill_in_matrix(int rows, int columns) {

    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(columns * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = rand() % 101;
        }
    }

    return matrix;
}

// Print matrixes to the console
void print_matrix(int **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] <10){
                printf("   %d", matrix[i][j]);
            }
            else if (matrix[i][j] <100){
                printf("  %d", matrix[i][j]);
            }
            else if (matrix[i][j] == 100){
                printf("% d", matrix[i][j]);
            }
            else if (matrix[i][j] <1000){
                printf("%   d", matrix[i][j]);
            }
            else if (matrix[i][j] <10000){
                printf("%  d", matrix[i][j]);
            }
            else if (matrix[i][j] <100000){
                printf("% d", matrix[i][j]);
            }
            else {
                printf("%d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

// Multiply matrix_A by matrix_B
void multiplication(int **matrix_A, int **matrix_B, int **matrix_C, int rows_A, int columns, int rows_B)
{
    int result = 0;
    for (int i_rows_A = 0; i_rows_A < rows_A; i_rows_A++)
    {
        for (int j_columns = 0; j_columns <columns; j_columns++)
        {
            for (int k_rows_B = 0; k_rows_B < rows_B; k_rows_B++)
            {
                // matrix_A[0][1] * matrix_B[1][0]
                //  1 2 3      7  8  -> (1*7 + 2*9 + 3*11) (1*8 + 2*10 + 3*12)
                //  4 5 6  *   9 10  -> (4*7 + 5*9 + *11) (4*8 + 5*10 + 6*12)
                //              11 12
                result += matrix_A[i_rows_A][k_rows_B] * matrix_B[k_rows_B][j_columns];
            }
            matrix_C[i_rows_A][j_columns] = result;
            result = 0;
        }
    }
}

// Read generated matrixes from a file with specified filename
int **read_from_file(char *filename, int rows_read, int columns_read)
{
    int **matrix_read = (int **)malloc(rows_read * sizeof(int *));
    for (int i = 0; i < rows_read; i++) {
        matrix_read[i] = (int *)malloc(columns_read * sizeof(int));
    }

    FILE *file;
    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    int row = 0;

// Execute while we have not reached the end of file
    while (!feof(file))
    {
// If file error occurs, exit
        if (ferror(file))
        {
            printf("Error reading file.\n");
            exit(1);
        }

// Store the numbers inside a 2D "matrix_read" array memory address
        for (int i = 0; i < columns_read; i++)
        {
            // If "fscanf" function returns EOF break out of the loop
            if (fscanf(file, "%d", &matrix_read[row][i]) == EOF)
                break;
        }

        row++;
        if (row == rows_read) break;
    }
    fclose(file);

    for (int i = 0; i < rows_read; i++)
    {
        for (int j = 0; j < columns_read; j++)
            printf("%d ", matrix_read[i][j]);
        printf("\n");
    }

    return matrix_read;
}

int print_matrix_to_file(int rows, int columns, int **matrix, char *filename){

    int i, j;
    FILE *file_pointer;


        file_pointer = fopen(filename, "w");
        if (file_pointer == NULL)
            return 0;

            for (i = 0; i < rows; i++) {

                for (j = 0; j < columns; j++) {
// Formatting to make matrixes look more readable
                    if (matrix[i][j] < 10)
                        fprintf(file_pointer, "   %d", matrix[i][j]);

                    else if (matrix[i][j] < 100)
                        fprintf(file_pointer, "  %d", matrix[i][j]);

                    else if (matrix[i][j] == 100)
                        fprintf(file_pointer, "% d", matrix[i][j]);

                    else if (matrix[i][j] > 100)
                        fprintf(file_pointer, "% d", matrix[i][j]);

                    // New rows
                    if (j == columns - 1)
                        fprintf(file_pointer, "\n");


                }
            }
            fclose(file_pointer);
    return 0;
}
int main() {

    srand(time(NULL));


    // matrix_A
    printf("Insert the size of matrix A: \n");
    int rows_A  = get_rows();
    int columns_A = get_columns();
    printf("Matrix A (rows x columns): %dx%d\n", rows_A, columns_A);

    // Initialize matrix_A
    int **matrix_A;
    matrix_A = fill_in_matrix(rows_A, columns_A);

    // Print matrix_A to file
    print_matrix_to_file(rows_A, columns_A, matrix_A, "matrix_A.txt");

    // Clean up the memory after matrix_A
    for (int i = 0; i < rows_A; i++)
        free(matrix_A[i]);
    free(matrix_A);

    // We replaced matrix_A which was randomly generated inside the file, with matrix_A_read which was derived from a file
    int **matrix_A_read;
    matrix_A_read = read_from_file("matrix_A.txt", rows_A, columns_A);


    // matrix_B
    printf("Insert the size of matrix B: \n");
    int rows_B = get_rows();
    int columns_B = get_columns();
    printf("Matrix B(rows x columns): %dx%d\n", rows_B, columns_B);

    // Initialize matrix_B
    int **matrix_B;
    matrix_B = fill_in_matrix(rows_B, columns_B);

    // Print matrix_B to file
    print_matrix_to_file(rows_B, columns_B, matrix_B, "matrix_B.txt");

    // Clean up the memory after matrix_B
    for (int i = 0; i < rows_B; i++)
        free(matrix_B[i]);
    free(matrix_B);

    // We replaced matrix_B which was randomly generated inside the file, with matrix_B_read which was derived from a file
    int **matrix_B_read;
    matrix_B_read = read_from_file("matrix_B.txt", rows_B, columns_B);

    // Print the matrixes
    printf("Matrix A:\n");
    print_matrix(matrix_A_read, rows_A, columns_A);
    printf("Matrix B:\n");
    print_matrix(matrix_B_read, rows_B, columns_B);


    // Initialize matrix_C
    int **matrix_C;
    matrix_C = fill_in_matrix(rows_A, columns_B);

    if (columns_A == rows_B)
    {
        //matrix_A * matrix_B
        multiplication(matrix_A_read, matrix_B_read, matrix_C, rows_A, columns_B, rows_B);
        printf("C = A*B \nMatrix C:\n");
        print_matrix(matrix_C, rows_A, columns_B);

    }
    else
    {
        printf("Multiplication is not possible");
    }
    print_matrix_to_file(rows_A, columns_B, matrix_C, "matrix_C.txt");

    // Clean up the memory by [i] because this is a 2D array, so we need to free it using for loop
    for (int i = 0; i < rows_A; i++)
        free(matrix_A_read[i]);
    for (int i = 0; i < rows_B; i++)
        free(matrix_B_read[i]);
    for (int i = 0; i < rows_A; i++)
        free(matrix_C[i]);

    free(matrix_A_read);
    free(matrix_B_read);
    free(matrix_C);
    return 0;
}
