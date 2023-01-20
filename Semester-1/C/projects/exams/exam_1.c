#include <stdio.h>
#include <stdlib.h>

//1. Napisz funkcję otrzmującą jako argumenty wskaźniki do dwóch zmiennych typu int,
//która zwraca jako wartość wskaźnik na zmienną przechowująca mniejszą z liczb wskazywanych przez argumenty.

int *ex_1(int *ex_1_num_1, int *ex_1_num_2){
    int *lower;
    if(ex_1_num_1>ex_1_num_2){
        lower=ex_1_num_2;
    }
    else{
        lower=ex_1_num_1;
    }
    return lower;
}

//2. Napisz funkcję, która dostaje jako arguemnt dodatnią liczbę całkowitą n,
//rezerwuje w pamięci blok n zmiennych typu int i zwraca jako wartość wskaźnik do początku zarezerwowanego bloku pamięci.
unsigned int *ex_2(unsigned int number_ex_2){
    unsigned int *block = (unsigned int*) malloc(number_ex_2*sizeof(unsigned int));
    return block;
}

//3. Zdefiniuj strukturę o nazwie 'Test' przechowująca wartość typu int i float.
//Zarezerwuj dynamiecznie pamięc na tablicę do przechowywania 100 struktur 'Test', a następnie zwolnij zarezerwowany blok pamięci.
void ex_3() {
    struct Test {
        int i;
        float f;
    };
unsigned int number_of_Tests = 100;
struct Test *array = (struct Test *) malloc(number_of_Tests *sizeof(struct Test));
free(array);
// use array
}

int main(){
    // Exercise 1 test:
    int num1 = 2;
    int num2 = 4;
    int *num1_p = &num1;
    int *num2_p = &num2;
    
    printf("%p\n", ex_1(num1_p, num2_p));
    printf("%p\n",ex_2(52));
    ex_3();

    return 0;
}
