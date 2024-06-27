#include <stdio.h>
#include <stdlib.h>



//1. Napisz funkcję, która dostaje jako argument dodatnią liczbę całkowitą n, rezerwuje w pamięci blok
//n zmiennych typu ‘int *’ i zwraca jako wartość wskaźnik do początku zarezerwowanego bloku
//pamięci.

//1. Write a function that gets a positive integer n as an argument, reserves a block of
//n variables of type 'int *' and returns as a value the pointer to the beginning of the reserved block of
//memory.
int *ex_1(int n){
    int *block = (int*)malloc(n* sizeof(int));
    return block;
}


//2. Napisz funkcję która dostaje jako argument ścieżkę do pliku tekstowego zawierającego wartości
//całkowite oddzielone spacjami. Funkcja ma zliczyć i zwrócić ilość wystąpień wartości 100 w
//przekazanym pliku.

//2. Write a function that gets as an argument the path to a text file containing the values of the
// totals separated by spaces. The function is to count and return the number of occurrences of the value 100 in the
// the passed file.
int ex_2(const char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening the file");
        return 1;
    }
    int num_counter = 0;
    int num;

    while (fscanf_s(fp, "%d\n", 100) == 1) {
        num_counter+=1;

    }
    fclose(fp);
    return num_counter;
}


//3. Zdefiniuj strukturę 'Test' zawierającą dwie składowe, pierwsza typu int, a druga to wskaźnik na int.
//Napisz funkcję która otrzymuje jako argumenty wskaźnik na tablicę tych struktur oraz rozmiar tablicy.
//Funkcja dla każdego elementu w tablicy: dynamicznie rezerwuje pamięć na pojedynczą zmienną int,
//przypisuje adres do wskaźnika i utworzoną zmienną inicjalizuje wartością 100.

//3. Define a structure 'Test' containing two components, the first of type int and the second a pointer to int.
//Write a function that receives as arguments a pointer to an array of these structures and the size of the array.
//Function for each element in the array: dynamically reserves memory for a single int variable,
//assigns the address to the pointer and initialises the created variable with the value 100.
struct Test{
    int num1;
    int * num2;
};

void ex_3(struct Test *arr, const int size){
    int num = 100;
    void initialize(Test* array, int size) {
        for (int i = 0; i < size; i++) {
            array[i].b   = new int;
            *(array[i].b) = 100;
        }
    }

    struct Test* arr_0 = (struct Test*)malloc(num*sizeof(int));
    int *arr_0_p = &arr_0;
}

int main() {
    printf("%d", ex_2("100.txt"));
    printf("%p", ex_1(10));
    printf("Hello world");
    return 0;
}
