

#include <random>

#include <iostream>
#include "lista.h"

struct osoba
{
    int a;
    char b;
};

#include <iostream>
#include "lista.h"
int main()
{
    cout << "START" << endl;
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> distrubution(0, 99);
    int randomNumber = distrubution(mt);
    const int MAX_ORDER = 7; // maksymalny rzad wielkosci rozmiaru dodawanych danych
    lista <int*>* ll = new lista < int* >(); // stworzenie listy
    for (int o = 1; o <= MAX_ORDER; o++) // petla po kolejnych rzedach wielkosci
    {
        const int n = pow(10, o); // rozmiar danych
        // dodawanie do listy
        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            int randomNumber = rand() % 1000; //distrubution(mt);
            int* pointerToInt = &randomNumber;
            ll ->add_to_tail(pointerToInt);
        }
        clock_t t2 = clock();
        cout << o << endl;
        cout << "Czas: " << (t2 - t1) / (double)CLOCKS_PER_SEC << endl;
    }
    
    delete ll;
    cout << "END" << endl;
    return 0;
}