//Użytkownik wprowadza wymiary macierzy
//Inicjalizacja macierzy losowymi wartościami
//Mnożymy macierze
//Wyświetlamy na ekran
//Sprzątamy po sobie

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int wysokosc() {
    int n;
    printf("Podaj ilosc wierszy: ");
    scanf(" %d", &n);
    if (n > 0) {
        return n;
    }
    else {
        printf("ilosc wierszy nie moze byc mniejsza od 1!\n");
        wysokosc();
    }
}

int szerokosc() {
    int m;
    printf("Podaj ilosc kolumn: ");
    scanf(" %d", &m);
    if (m > 0) {
        return m;
    }
    else {
        printf("ilosc kolumn nie moze byc mniejsza od 1!\n");
        szerokosc();
    }
}
int** rozmiar(int n, int m) {

    int** tab = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        tab[i] = (int*)malloc(m * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            tab[i][j] = rand()%101;

        }
    }

    return tab;
}
void wypisywanie(int** tab, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("[%d] ", tab[i][j]);
        }
        printf("\n");
    }
}
void mnozenie(int** taba, int** tabb, int** tabc,int n, int m, int p) {
    int wynik = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                wynik += taba[i][k] * tabb[k][j];
            }
            tabc[i][j] = wynik;
            wynik = 0;
        }
    }
}

int main()
{
    int n, m;
    printf("Podaj wymiary macierzy A: \n");
    n = wysokosc();
    m = szerokosc();
    printf("Wymiary macierzy A to: %dx%d\n", n, m);
    int** taba;
    taba = rozmiar(n, m);
    printf("Podaj wymiary macierzy B: \n");
    int n2 = wysokosc();
    int m2 = szerokosc();
    printf("Wymiary macierzy A to: %dx%d\n", n2, m2);
    int** tabb;
    tabb = rozmiar(n2, m2);
    printf("Macierz A:\n");
    wypisywanie(taba, n, m);
    printf("Macierz B:\n");
    wypisywanie(tabb, n2, m2);
    int** tabc;
    tabc = rozmiar(n, m2);
    if (m == n2) {
        mnozenie(taba, tabb, tabc, n, m2, n2);
        printf("C = A*B \nMacierz C:\n");
        wypisywanie(tabc, n, m2);
    }
    else {
        printf("Nie mozna pomnozyc tych macierzy");
    }

    for (int i = 0; i < n; i++)
        free(taba[i]);
    free(taba);
    for (int i = 0; i < n2; i++)
        free(tabb[i]);
    free(tabb);
    for (int i = 0; i < n; i++)
        free(tabc[i]);
    free(tabc);
    return 0;
}