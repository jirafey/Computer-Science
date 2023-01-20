// Ogólne założenia:
// - Brak wycieków pamięci.
// - Przejrzysty kod - podział na funkcje, struktury, wcięcia, minimalizacja
// redundancji kodu.
// - Brak zmiennych globalnych.
// 
// 
//  ---------------------------------------------------------
//  Projekt 2
// 
//  Program do przechowywania danych osobowych (struktura) na liście dwukierunkowej
// (własna implementacja listy). Lista przechowywana i zarządzana jest w pamięci.
// 
//  Dane osobowe:
//  - nazwisko (dowolnej długości)
//  - imie (dowolnej długości)
//  - wiek
//  - pesel
//  - płeć
// 
//  Program umożliwia:
// 1. Dodawanie dowolnej liczby osób do listy
// 2. Wyszukiwanie osoby po nazwisku lub imieniu
// 3. Kasowanie wybranej osoby (po nazwisku)
// 4. Wyświetlanie listy - od przodu / od tyłu
// 5. Odczytywanie listy z pliku (elementy z pliku dodawane są do już istniejącej listy
// w pamięci)
// 6. Zapisywanie listy do pliku
// 7. Sortowanie listy po nazwisku (dowolny algorytm) - po jawnym wybraniu opcji z menu
// 8. Menu tekstowe do obsługi funkcjonalności.
//
// Jedynym ograniczeniem ilości elementów na liście to zasoby systemu.

#include <stdio.h>
 
int get_length() {
    char *length;
    scanf("%c", length);


    return length
}

struct personal_data{
    char *name;
    char *surname;
    int age;
    int id;
    int sex;
};

int main() {

}
