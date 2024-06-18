#include <stdio.h>
#include <stdlib.h>

// WSKAŹNIKI

// 6. Napisz funkcję, która dostaje jako argument dodatnią liczbę całkowitą n, rezerwuje w pamięci blok n
// zmiennych typu int i zwraca jako wartość wskaźnik do początku zarezerwowanego bloku pamięci.
// 7. Napisz funkcję, która dostaje jako argument dodatnią liczbę całkowitą n, rezerwuje w pamięci blok n
// zmiennych typu double i zwraca jako wartość wskaźnik do początku zarezerwowanego bloku pamięci.
// 8. Napisz funkcję, która dostaje jako argument dodatnią liczbę całkowitą n, rezerwuje w pamięci blok n
// zmiennych typu ‘int *’ i zwraca jako wartość wskaźnik do początku zarezerwowanego bloku pamięci.
// 9. Napisz funkcję która dostaje jako argumenty dwa wskaźniki na tablice jednowymiarowe tegosamego
// rozmiaru oraz dodatnią liczbę zawierającą ilość elementów w tablicy. Zadaniem funkcji jest zamiana
// wartości zapisanych w tablicach. Wyświetl zawartości tablic prze i po zmianie.
// 10. Napisz funkcję która dostaje jako argumenty dwa wskaźniki na tablice jednowymiarowe różnego rozmiaru
// oraz dwie dodatnie liczby zawierającą ilości elementów w tablicach. Zadaniem funkcji jest zamiana
// wartości zapisanych w tablicach – należy zwrócić uwagę że jedna tablica może zawierać mniej elementów
// od drugiej. Wyświetl zawartości tablic przed i po zmianie.
// 11. Napisz funkcję, która dostaje jako argument dodatnie liczby całkowite n i m, tworzy dynamiczną
// dwuwymiarową tablicę tablic elementów typu int o wymiarach n na m, i zwraca jako wartość wskaźnik do
// niej.
// 12. Napisz funkcję, która dostaje jako argumenty wskaźnik do tablicy dwuwymiarowej elementów typu int
// oraz jej wymiary n i m, i usuwa z pamięci otrzymaną tablicę.
// 13. Rozwiąż powyższe dwa zadania w wersji z trójwymiarowymi tablicami.
// 14. Napisz funkcję, która dostaje w argumentach tablicę dwuwymiarową elementów typu int oraz jej wymiary
// n i m, i wypełnia ją zerami.
// 15. Napisz funkcję, która dostaje w argumentach tablicę dwuwymiarową o elementach typu int oraz jej
// wymiary n i m, i zwraca jako wartość sumę wartości elementów tablicy.
// 16. Napisz funkcję, która dostaje jako argumenty dwuwymiarową tablicę tablic o elementach typu int oraz jej
// wymiary, i zwraca jako wartość indeks wiersza o największej średniej wartości elementów. Przyjmujemy,
// że dwa elementy leżą w tym samym wierszu, jeżeli mają taki sam pierwszy indeks.

// 1. Napisz funkcję otrzymującą jako argumenty wskaźniki do dwóch zmiennych typu int, która zwraca jako
// wartość mniejszą z liczb wskazywanych przez argumenty.

// zad1(int* a, int* b){

//     int *p_a = &a;
//     int *p_b = &b;

// }

int zad1(int *num1, int *num2)
{
    if (*num1 < *num2)
    {
        // printf("asmol %d", a);
        return *num1;
    }
    else
    {
        // printf("bsmol, %d\n", b);
        // printf("bsmol, %p\n", *b);
        return *num2;
    }
}

// 2. Napisz funkcję otrzymującą jako argumenty wskaźniki do dwóch zmiennych typu int, która zwraca jako
// wartość wskaźnik na zmienną przechowującą mniejszą z liczb wskazywanych przez argumenty.

int zad2(int *num1, int *num2)
{

    if (*num1 < *num2)
    {
        printf("\npointer=");
        return num1;
    }
    else
    {
        printf("\npointer=");
        return num2;
    }
}
// 3. Napisz funkcję otrzymującą jako argumenty wskaźniki do dwóch zmiennych typu int, która zamienia ze sobą
// wartości wskazywanych zmiennych.

void zad3(int *num1, int *num2)
{
    int temp = 0;
    temp = *num1;
    printf("\n%d, %d\n", *num1, *num2);
    *num1 = *num2;
    *num2 = temp;
    printf("%d, %d\n", *num1, *num2);
}
// 4. Napisz bezargumentową funkcję, która rezerwuje pamięć dla pojedynczej zmiennej typu int i zwraca jako
// wartość wskaźnik do niej.

int *zad4_helper()
{

    int *ptr = (int *)malloc(sizeof(int));
    return ptr;
}
void zad4()
{
    int *ptr = zad4_helper();
    printf("4: Pointer:%p", ptr);
    free(ptr);
}
// 5. Napisz bezargumentową funkcję, która rezerwuje pamięć dla pojedynczej zmiennej typu double i zwraca
// jako wartość wskaźnik do niej.
// double**

double *zad5_helper()
{

    double *ptr = (double *)malloc(sizeof(double));
    return ptr;
}

void zad5()
{

    double *ptr = zad5_helper();
    printf("\n5: Pointer:%p", ptr);
    free(ptr);
}

void zad6()
{
}
void zad7()
{
}
void zad8()
{
}
void zad9()
{
}
void zad10()
{
}
void zad11()
{
}
void zad12()
{
}
void zad13()
{
}
void zad14()
{
}
void zad15()
{
}

void zad16()
{
}

int main()
{
    int a = 222222, b = 12;
    int *pa = &a;
    int *pb = &b;

    printf("the numba is %d", zad1(pa, pb));
    int c = 7222, d = 102;
    int *pc = &c;
    int *pd = &d;
    printf("%d", zad2(pc, pd));

    int e = 7222, f = 102;
    int *pe = &e;
    int *pf = &f;
    zad3(pe, pf);

    zad4();

    zad5();

    zad6();

    zad7();

    zad8();

    zad9();

    zad10();

    zad11();

    zad12();

    zad13();

    zad14();

    zad15();

    zad16();
}
dvcdv