#include <stdio.h>

//1. Napisz funkcję otrzymującą jako argumenty wskaźniki do dwóch zmiennych typu int, która
//        zamienia ze sobą wartości wskazywanych zmiennych.

void ex_1(int *ex_1_num1, int *ex_1_num2){
    printf("BEFORE: number1 = %d, number2 = %d\n", *ex_1_num1, *ex_1_num2);
    int temp = *ex_1_num1;
    *ex_1_num1 = *ex_1_num2;
    *ex_1_num2 = temp;
    printf("AFTER: number1 = %d, number2 = %d\n", *ex_1_num1, *ex_1_num2);
}

//2. Napisz funkcję, która dostaje jako argument ścieżkę dostępu do pliku tekstowego zawierającego
//        liczby całkowite oddzielone białymi znakami i zwraca jako wartość sumę znajdujących się w pliku liczb.

unsigned int ex_2(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening the file");
        return 1;
    }
        int sum_of_nums = 0;
        int num;

    while (fscanf_s(fp, "%d\n", &num) == 1) {
        sum_of_nums+=num;

    }
    fclose(fp);
    return sum_of_nums;
}
//3. Zdefiniuj strukturę 'Trojkat' przechowującą długości boków trójkąta. Napisz funkcję, która
//otrzymuje jako argument zmienną typu struct 'Trojkat', i zwraca jako wartość obwód trójkąta
//przekazanego w argumencie.

struct Trojkat{
    unsigned int length_a;
    unsigned int length_b;
    unsigned int length_c;
};
unsigned int calculate_triangle_perimeter(struct Trojkat instance) {
    return instance.length_a + instance.length_b + instance.length_c;
}

int main() {
    int num1=0;
    int num2=1;
    int *num1_p = &num1;
    int *num2_p = &num2;
    ex_1(num1_p, num2_p);

    // Tests for Exercise_2:
//    printf("%d", ex_2(filename.txt));

    // Tests for Exercise_3:
    struct Trojkat i1 = {1,2,3};
    printf("%d\n", calculate_triangle_perimeter(i1));


    printf("Hi mom!");
    return 0;
}
