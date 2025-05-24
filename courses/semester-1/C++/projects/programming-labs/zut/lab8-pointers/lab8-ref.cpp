#include <iostream>

using namespace std;

/*int** p;

p = (int**)malloc(sizeof(int*) * 6);

for (int i = 0; i < 6; i++) {
    p[i] = (int*)malloc(sizeof(int) * 6);
}

p[5][5] = 10;
*/

// WSKAZNIKI
// ZAD 1
/*  Napisz funkcj� otrzymuj�c� jako argumenty wska�niki do dw�ch zmiennych typu int, kt�ra zwraca jako
    warto�� mniejsz� z liczb wskazywanych przez argumenty.
*/

int zad1_funkcja(int *a, int *b)
{
    if (*a < *b)
    {
        return *a;
    }
    else
    {
        return *b;
    }
}

void zad1()
{
    int a = 2, b = 1;
    int *wsk1 = &a;
    int *wsk2 = &b;

    cout << "Mniejsza wartosc jest rowna: " << zad1_funkcja(wsk1, wsk2) << endl;
}

// ZAD 2
/*  Napisz funkcj� otrzymuj�c� jako argumenty wska�niki do dw�ch zmiennych typu int, kt�ra zwraca jako
    warto�� wska�nik na zmienn� przechowuj�c� mniejsz� z liczb wskazywanych przez argumenty.
*/

int zad2_funkcja(int *a, int *b)
{
    if (*a < *b)
    {
        return *a;
    }
    else
    {
        return *b;
    }
}

void zad2()
{
    int a = 2, b = 221;
    int *wsk1 = &a;
    int *wsk2 = &b;

    cout << "Wartosc wskaznika mniejszej liczby: " << zad1_funkcja(wsk1, wsk2) << endl;
}

// ZAD 3
/*  Napisz funkcj� otrzymuj�c� jako argumenty wska�niki do dw�ch zmiennych typu int, kt�ra zamienia ze sob�
    warto�ci wskazywanych zmiennych.
*/

void zad3_funkcja(int *a, int *b)
{
    int zamiennik = 0;
    zamiennik = *a;
    *a = *b;
    *b = zamiennik;

    cout << "a: " << *a << " | b: " << *b << endl;
}

void zad3()
{
    int a = 1, b = 2;
    int *wsk1 = &a;
    int *wsk2 = &b;

    cout << "a: " << a << " | b: " << b << endl;

    zad3_funkcja(wsk1, wsk2);
}

// ZAD 4
/*  Napisz bezargumentow� funkcj�, kt�ra rezerwuje pami�� dla pojedynczej zmiennej typu int i zwraca jako
    warto�� wska�nik do niej.
*/

int *zad4_funkcja()
{
    int *wsk = (int *)malloc(sizeof(int));
    return wsk;
}

void zad4()
{
    int *wsk = zad4_funkcja();
    cout << wsk << endl;
    free(wsk);
}

// ZAD 5
/*  Napisz bezargumentow� funkcj�, kt�ra rezerwuje pami�� dla pojedynczej zmiennej typu double i zwraca
    jako warto�� wska�nik do niej.
*/

double *zad5_funkcja()
{
    double *wsk = (double *)malloc(sizeof(double));
    return wsk;
}

void zad5()
{
    double *wsk = zad5_funkcja();
    cout << wsk << endl;
    free(wsk);
}
double *zad5_funkcja()
{
    double *wsk = (double *)malloc(sizeof(double));
    return wsk;
}

void zad5()
{
    double *wsk = zad5_funkcja();
    cout << wsk << endl;
    free(wsk);
}

// ZAD 6
/*  Napisz funkcj�, kt�ra dostaje jako argument dodatni� liczb� ca�kowit� n, rezerwuje w pami�ci blok n
    zmiennych typu int i zwraca jako warto�� wska�nik do pocz�tku zarezerwowanego bloku pami�ci.
*/

int *zad6_funkcja(int n)
{
    int *wsk = (int *)malloc(sizeof(int) * n);
    return wsk;
}

void zad6()
{
    int n = 10;
    cout << zad6_funkcja(n) << endl;
}

// ZAD 7
/*  Napisz funkcj�, kt�ra dostaje jako argument dodatni� liczb� ca�kowit� n, rezerwuje w pami�ci blok n
    zmiennych typu double i zwraca jako warto�� wska�nik do pocz�tku zarezerwowanego bloku pami�ci.
*/

double *zad7_funkcja(int n)
{
    double *wsk = (double *)malloc(sizeof(double) * n);
    return wsk;
}

void zad7()
{
    int n = 10;
    cout << zad7_funkcja(n) << endl;
}

// ZAD 8
/*  Napisz funkcj�, kt�ra dostaje jako argument dodatni� liczb� ca�kowit� n, rezerwuje w pami�ci blok n
    zmiennych typu �int *� i zwraca jako warto�� wska�nik do pocz�tku zarezerwowanego bloku pami�ci.
*/

int *zad8_funkcja(int n)
{
    int *wsk = (int *)malloc(sizeof(int *) * n);
    return wsk;
}

void zad8()
{
    int n = 10;
    cout << zad8_funkcja(n) << endl;
}

// ZAD 9
/*	Napisz funkcj� kt�ra dostaje jako argumenty dwa wska�niki na tablice jednowymiarowe tegosamego
    rozmiaru oraz dodatni� liczb� zawieraj�c� ilo�� element�w w tablicy. Zadaniem funkcji jest zamiana
    warto�ci zapisanych w tablicach. Wy�wietl zawarto�ci tablic prze i po zmianie.
*/

void zad9_funkcja(int *tab1, int *tab2, int n)
{
    for (int i = 0; i < n; i++)
    {
        tab1[i] = i;
        tab2[i] = i;
    }

    cout << endl
         << "Po:" << endl
         << endl;

    for (int i = 0; i < n; i++)
    {
        printf("tab1[%d] = %d | tab2[%d] = %d\n", i, tab1[i], i, tab2[i]);
    }
}

void zad9()
{
    const int n = 10;
    int tab1[n] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int tab2[n] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *wsk1 = &tab1[0];
    int *wsk2 = &tab2[0];

    for (int i = 0; i < n; i++)
    {
        printf("tab1[%d] = %d | tab2[%d] = %d\n", i, tab1[i], i, tab2[i]);
    }

    zad9_funkcja(wsk1, wsk2, n);
}

// ZAD 10
/*  Napisz funkcj� kt�ra dostaje jako argumenty dwa wska�niki na tablice jednowymiarowe r�nego rozmiaru
    oraz dwie dodatnie liczby zawieraj�c� ilo�ci element�w w tablicach. Zadaniem funkcji jest zamiana
    warto�ci zapisanych w tablicach � nale�y zwr�ci� uwag� �e jedna tablica mo�e zawiera� mniej element�w
    od drugiej. Wy�wietl zawarto�ci tablic przed i po zmianie
*/

void zad10_funkcja(int *tab1, int *tab2, int n, int m)
{
    int pauza = 0;
    int zamiennik = 0;
    bool check = true;

    if (n >= m)
    {
        pauza = m;
        check = true;
    }
    else
    {
        pauza = n;
        check = false;
    }

    for (int i = 0; i < pauza; i++)
    {
        zamiennik = tab1[i];
        tab1[i] = tab2[i];
        tab2[i] = zamiennik;
    }

    cout << endl
         << " Po:" << endl
         << endl;

    for (int i = 0; i < pauza; i++)
    {
        printf("tab1[%d] = %d | tab2[%d] = %d\n", i, tab1[i], i, tab2[i]);
    }

    if (check == true)
    {
        for (int i = pauza; i < n; i++)
        {
            printf("tab1[%d] = %d |\n", i, tab1[i]);
        }
    }
    else
    {
        for (int i = pauza; i < m; i++)
        {
            printf("            | tab2[%d] = %d\n", i, tab2[i]);
        }
    }
}

void zad10()
{
    const int n = 5, m = 10;
    int tab1[n] = {5, 4, 3, 2, 1};
    int tab2[m] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int *wsk1 = &tab1[0];
    int *wsk2 = &tab2[0];

    int pauza = 0;
    bool check = true;

    if (n >= m)
    {
        pauza = m;
        check = true;
    }
    else
    {
        pauza = n;
        check = false;
    }

    for (int i = 0; i < pauza; i++)
    {
        printf("tab1[%d] = %d | tab2[%d] = %d\n", i, tab1[i], i, tab2[i]);
    }

    if (check == true)
    {
        for (int i = pauza; i < n; i++)
        {
            printf("tab1[%d] = %d |\n", i, tab1[i]);
        }
    }
    else
    {
        for (int i = pauza; i < m; i++)
        {
            printf("            | tab2[%d] = %d\n", i, tab2[i]);
        }
    }

    zad10_funkcja(wsk1, wsk2, n, m);
}

// ZAD 11
/*  Napisz funkcj�, kt�ra dostaje jako argument dodatnie liczby ca�kowite n i m, tworzy dynamiczn�
    dwuwymiarow� tablic� tablic element�w typu int o wymiarach n na m, i zwraca jako warto�� wska�nik do
    niej.
*/

int **zad11_funkcja(int n, int m)
{
    int **tab = (int **)malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++)
    {
        tab[i] = (int *)malloc(sizeof(int) * m);
    }

    return tab;
}

void zad11()
{
    int n = 5;
    int m = 10;

    int **wsk = zad11_funkcja(n, m);

    cout << zad11_funkcja(n, m) << endl;

    for (int i = 0; i < n; i++)
    {
        free(wsk[i]);
    }
    free(wsk);
}

// ZAD 12
/*  Napisz funkcj�, kt�ra dostaje jako argumenty wska�nik do tablicy dwuwymiarowej element�w typu int
    oraz jej wymiary n i m, i usuwa z pami�ci otrzyman� tablic�.
*/

void zad12_funkcja(int **wsk, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        free(wsk[i]);
    }
    free(wsk);
}

void zad12()
{
    int n = 5;
    int m = 10;

    int **wsk = zad11_funkcja(n, m);

    zad12_funkcja(wsk, n, m);
}

// ZAD 13
/*  Rozwi�� powy�sze dwa zadania w wersji z tr�jwymiarowymi tablicami.
 */

int ***zad13_funkcja_tworzenia(int n, int m, int o)
{
    int ***tab = (int ***)malloc(sizeof(int **) * n);

    for (int i = 0; i < n; i++)
    {
        tab[i] = (int **)malloc(sizeof(int *) * m);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            tab[i][j] = (int *)malloc(sizeof(int) * o);
        }
    }

    return tab;
}

void zad13_funkcja_usuwania(int ***wsk, int n, int m, int o)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            free(wsk[i][j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        free(wsk[i]);
    }

    free(wsk);
}

void zad13()
{
    int n = 5;
    int m = 10;
    int o = 15;

    int ***wsk = zad13_funkcja_tworzenia(n, m, o);

    zad13_funkcja_usuwania(wsk, n, m, o);
}

// ZAD 14
/*	Napisz funkcj�, kt�ra dostaje w argumentach tablic� dwuwymiarow� element�w typu int oraz jej wymiary
    n i m, i wype�nia j� zerami.
*/

void zad14_funkcja(int **wsk, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            wsk[i][j] = 0;
        }
    }
}

void zad14()
{
    int n = 5, m = 10;
    int **wsk = zad11_funkcja(n, m);

    zad14_funkcja(wsk, n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("tab[%d][%d] = %d ", i, j, wsk[i][j]);
        }
        cout << endl;
    }

    zad12_funkcja(wsk, n, m);
}

// ZAD 15
/*  Napisz funkcj�, kt�ra dostaje w argumentach tablic� dwuwymiarow� o elementach typu int oraz jej
    wymiary n i m, i zwraca jako warto�� sum� warto�ci element�w tablicy.
*/

void zad15_funkcja_zapisania_liczb(int **wsk, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            wsk[i][j] = j;
        }
    }
}

int zad15_funkcja(int **wsk, int n, int m)
{
    int suma = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            suma += wsk[i][j];
        }
    }
    return suma;
}

void zad15()
{
    int n = 5, m = 10;
    int **wsk = zad11_funkcja(n, m);

    zad15_funkcja_zapisania_liczb(wsk, n, m);
    cout << "Suma elementow tablic jest rowna: " << zad15_funkcja(wsk, n, m) << endl;
    zad12_funkcja(wsk, n, m);
}

// ZAD 16
/*  Napisz funkcj�, kt�ra dostaje jako argumenty dwuwymiarow� tablic� tablic o elementach typu int oraz jej
    wymiary, i zwraca jako warto�� indeks wiersza o najwi�kszej �redniej warto�ci element�w. Przyjmujemy,
    �e dwa elementy le�� w tym samym wierszu, je�eli maj� taki sam pierwszy indeks.
*/

void zad16_funkcja_zapisania_roznych_liczb(int **wsk, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            wsk[i][j] = i + j;
        }
    }
}

int zad16_funkcja(int **wsk, int n, int m)
{
    int najwiekszy_wiersz = 0;
    int poprzednia_srednia = 0;
    int srednia = 0;

    for (int i = 0; i < n; i++)
    {
        srednia = 0;
        for (int j = 0; j < m; j++)
        {
            srednia += wsk[i][j];
        }
        if (srednia > poprzednia_srednia)
        {
            najwiekszy_wiersz = i;
            poprzednia_srednia = srednia;
        }
    }

    return najwiekszy_wiersz;
}

void zad16()
{
    int n = 5, m = 10;
    int **wsk = zad11_funkcja(n, m);

    zad16_funkcja_zapisania_roznych_liczb(wsk, n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("tab[%d][%d] = %d ", i, j, wsk[i][j]);
        }
        cout << endl;
    }

    cout << "Indeks wiersza o najwiekszej sredniej wartosci elementow: " << zad16_funkcja(wsk, n, m) << endl;
    zad12_funkcja(wsk, n, m);
}

int main()
{
    zad1();
    zad2();
    zad3();
    zad4();
    // zad5();
    // zad6();
    // zad7();
    // zad8();
    // zad9();
    // zad10();
    // zad11();
    // zad12();
    // zad13();
    // zad14();
    // zad15();
    //  zad16();
}