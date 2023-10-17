// lab_01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

struct osoba
{
    int a;
    char b;
};

int cmp_int(int a, int b) {
    return a - b;
}

//boool operator ==(osoba o1, osoba o2)

int cmp_osoby(osoba o1, osoba o2) {
    return o1.a - o2.a;
}

#include <iostream>
#include "lista.h"
int main()
{
    lista<int> lista_test;
    //lista_test.search_data(1);
    lista_test.add_to_head(1);
    cout << lista_test.search_data(1) << endl;
    lista_test.add_to_head(2);
    cout << lista_test.search_data(1) << endl;
    cout << lista_test.search_data(2) << endl;
    lista_test.add_to_head(3);
    lista_test.add_to_head(4);
    lista_test.add_to_head(5);
    lista_test.add_to_tail(6);
    lista_test.add_to_tail(7);
    lista_test.add_to_tail(8);
    lista_test.add_to_tail(9);
    lista_test.add_to_tail(10);
    cout << lista_test << endl;
    lista<osoba> l2;
    osoba pattern;
    pattern.a = 13;

    cout<< lista_test.search_data(9)<<endl;
    cout << lista_test.to_string(-1) << endl;
    lista_test.clear();
    cout << lista_test.to_string(-1) << endl;

}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
