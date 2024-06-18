#include <iostream>
#include <string>
#include <cmath>
using namespace std;
// TABLICE JEDNOWYMIAROWE

// 1. Napisz funkcję, która otrzymuje dwa argumenty: nieujemną liczbę całkowitą n oraz n-elementową tablicę
// tab elementów typu int i:
// a. nadaje wartość zero wszystkim elementom tablicy tab,
// b. zapisuje do kolejnych elementów tablicy wartości równe ich indeksom (do komórki o indeksie i
// funkcja ma zapisywać wartość i),
// c. c) podwaja wartość wszystkich elementów w tablicy tab,
// d. d) do wszystkich komórek tablicy tab wstawia wartości bezwzględne ich pierwotnych wartości.
void zad1(int *array_given, int size)
{
    int array_given_copy[size];
    for (int i = 0; i < size; i++)
    {
        array_given_copy[i] = (array_given[i]);
        // printf("%d\n", array_given_copy[i]);
    }
    for (int i = 0; i < size; i++)
    {
        array_given[i] = 0;
        // printf("%d\n", array_given[i]);
    }
    for (int i = 0; i < size; i++)
    {
        array_given[i] = i;
        // printf("%d\n", array_given[i]);
    }
    for (int i = 0; i < size; i++)
    {
        array_given[i] *= 2;
        // printf("%d\n", array_given[i]);
    }

    for (int i = 0; i < size; i++)
    {
        // printf("copy:%d\n",array_given_copy[i]);
        array_given[i] = abs(array_given_copy[i]);
    }
}
// 2. Napisz funkcję, która otrzymuje dwa argumenty: dodatnią liczbę całkowitą n oraz n-elementową tablicę tab
// o elementach typu int i zwraca jako wartość:
// a. średnią arytmetyczną elementów tablicy tab.
// b. sumę elementów tablicy tab,
// c. sumę kwadratów elementów tablicy tab.
float *zad2(float num, int array[])
{
    float sum = 0;
    float sum_of_squares = 0;
    for (int i = 0; i < num; i++)
    {
        sum += array[i];
        sum_of_squares += pow(array[i], 2);
    }
    float arithmetic_sum = sum / (num - 1);
    float *result[4] = {&arithmetic_sum, &sum, &sum_of_squares};

    return *result;
}
// 3. Napisz funkcję, która otrzymuje dwa argumenty: dodatnią liczbę całkowitą n oraz n-elementową tablicę tab
// o elementach typu const int i zwraca jako wartość średnią arytmetyczną elementów tablicy tab.
void zad3()
{
}
// 4. Napisz funkcję, która otrzymuje trzy argumenty: dodatnią liczbę całkowitą n oraz dwie n-elementowe
// tablice tab1, tab2 o elementach typu int i:
// a. przepisuje zawartość tablicy tab1 do tablicy tab2,
// b. przepisuje zawartość tablicy tab1 do tablicy tab2 w odwrotnej kolejności (czyli element tab1[0] ma
// zostać zapisany do komórki tablicy tab2 o indeksie n − 1).
void zad4()
{
}
// 5. Napisz funkcję, która otrzymuje cztery argumenty: dodatnią liczbę całkowitą n oraz trzy n-elementowe
// tablice tab1, tab2 i tab3 o elementach typu int, i:
// a. przypisuje elementom tablicy tab3 sumę odpowiadających im elementów tablic tab1 i tab2 (do
// komórki tablicy tab3 o indeksie i powinna trafić suma elementów tab1[i] i tab2[i]),
// b. przypisuje elementom tablicy tab3 większy spośród odpowiadających im elementów tablic tab1 i
// tab2 (do komórki tablicy tab3 o indeksie i powinien trafić większy spośród elementów tab1[i] i
// tab2[i]),
// c. przypisuje zawartość tablicy tab1 do tablicy tab2, zawartość tablicy tab2 do tablicy tab3 oraz
// zawartość tablicy tab3 do tablicy tab1.
void zad5()
{
}
// 6. Napisz funkcję, która otrzymuje cztery argumenty: dodatnią liczbę całkowitą n, n-elementowe tablice tab1
// i tab2 oraz 2 · n-elementową tablicę tab3 o elementach typu double.
// a. Funkcja powinna przepisywać zawartość tablic tab1 i tab2 do tablicy tab3 w taki sposób, że na
// początku tablicy tab3 powinny się znaleźć elementy tablicy tab1, a po nich elementy tablicy tab2.
// b. Funkcja powinna przepisywać zawartość tablic tab1 i tab2 do tablicy tab3 w taki sposób, że w
// komórkach tablicy tab3 o nieparzystych indeksach powinny się znaleźć elementy tablicy tab1, a w
// komórkach tablicy tab3 o parzystych indeksach elementy tablicy tab2.
void zad6()
{
}
// 7. Napisz funkcję, która otrzymuje cztery argumenty: dodatnią liczbę całkowitą n oraz trzy n-elementowe
// tablice tab1, tab2 i tab3 o elementach typu int i zamienia zawartości komórek otrzymanych w argumentach
// tablic w następujący sposób:
// • dla dowolnego i komórka tab1[i] powinna zawierać największą spośród pierwotnych wartości
// komórek tab1[i], tab2[i] oraz tab3[i],
// • dla dowolnego i komórka tab2[i] powinna zawierać drugą co do wielkości spośród pierwotnych
// wartości komórek tab1[i], tab2[i] oraz tab3[i],
// • dla dowolnego i komórka tab3[i] powinna zawierać najmniejszą spośród pierwotnych wartości
// komórek tab1[i], tab2[i] oraz tab3[i].
void zad7()
{
}
// 8. Napisz funkcję, która otrzymuje dwa argumenty: dodatnią liczbę całkowitą n oraz n-elementową tablicę tab
// o elementach typu int i:
// a. zwraca największą wartość przechowywaną w tablicy tab,
// b. zwraca najmniejszą wartość przechowywaną w tablicy tab,
// c. zwraca indeks elementu tablicy tab o największej wartości,
// d. zwraca indeks elementu tablicy tab o najmniejszej wartości,
// e. zwraca największą spośród wartości bezwzględnych elementów przechowywanych w tablicy tab,
// f. zwraca indeks elementu tablicy tab o największej wartości bezwzględnej.
void zad8()
{
}
// 9. Napisz funkcję, która otrzymuje dwa argumenty: dodatnią liczbę całkowitą n oraz dwie n-elementowe
// tablice tab o elementach typu double przechowujące n-wymiarowe wektory i zwraca jako wartość iloczyn
// skalarny wektorów otrzymanych w argumentach.
void zad9()
{
}
int main()
{
    int array1[6] = {5, 4, 2, 3, 1};

    zad1(array1, sizeof(array1) / sizeof(*array1));
    // * array1 = array1[0]
    int array2[4] = {5, 4, 2};
    printf("%f\n", zad2(4, array2)[0]);
    printf("%.f\n", zad2(4, array2)[1]);
    printf("%.f\n", zad2(4, array2)[2]);

    zad3();

    zad4();

    zad5();

    zad6();

    zad7();

    zad8();

    zad9();
}
