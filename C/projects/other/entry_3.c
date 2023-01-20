#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//1. Napisz funkcję która dostaje jako argumenty dwa wskaźniki na tablice jednowymiarowe tego
//samego rozmiaru oraz dodatnią liczbę zawierającą ilość elementów w tablicy. Zadaniem funkcji jest
//        zamiana wartości zapisanych w tablicach.

//1. Write a function that receives as arguments two pointers to one-dimensional arrays of the
// same size and a positive number containing the number of elements in the array. The function's task is to
// convert the values stored in the arrays.
void ex_1(int *array_1_p,int *array_2_p,int size){
    int temp[size+1];
    for(int i=0; i<size; i++){
        temp[i] = array_1_p[i];
        array_1_p[i] =array_2_p[i];
        array_2_p[i] =temp[i];
        printf("AFTER: Array 1: %d\n", array_1_p[i]);
        printf("AFTER: Array 2: %d\n", array_2_p[i]);
    }

}

//2. Napisz funkcję, która dostaje jako argument liczbę całkowitą n
// i zwraca jako wartość liczbę 2 do potęgi n (2^n).

//2. Write a function that gets as an argument an integer n
// and returns as a value the number 2 to the power of n (2^n).
double raise_to_a_power(int ex_1_num){
    return pow(2, ex_1_num);
}

//3. Zdefiniuj strukturę 'Punkt' pozwalającą na przechowywanie współrzędnych punktu w
//dwuwymiarowej przestrzeni kartezjańskiej. Zarezerwuj dynamicznie pamięć na tablicę 100 struktur
//'Punkt' i zainicjalizuj wszytskie punkty wartościami początkowymi (dowolnymi).

//3. Define a 'Point' structure to store the coordinates of a point in a
// two-dimensional Cartesian space. Reserve memory dynamically for an array of 100 structures
//'Point' and initialise all points with initial values (arbitrary).
struct Punkt{
    float x;
    float y;
};

int main(){
    srand(time(NULL));
    // Tests for Exercise_1:
    int arr_1_ex[3] = {1,2,3};
    int *arr_1_p_ex = &arr_1_ex[0];
    int arr_2_ex[3] = {9,8,7};
    int *arr_2_p_ex = &arr_2_ex[0];
    ex_1(arr_1_p_ex, arr_2_p_ex,3);
    printf("%.0lf\n", raise_to_a_power(0));

    // Tests for Exercise_3:
    int number_of_points = 100;
    struct Punkt *points_100 = (struct Punkt*)malloc(number_of_points*sizeof(struct Punkt)) ;
    for(int i=0;i<number_of_points;i++){
        points_100[i].x = rand();
        points_100[i].y = rand();
    }
    for (int i = 0; i < 100; i++) {
        printf("Punkt %d: x = %.0f, y = %.0f\n", i, points_100[i].x, points_100[i].y);
    }
    printf("Hi mom!");
    free(points_100);
    return 0;
}
