// lab_01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "lista.h"
int main()
{
    std::cout << "Hello World!\n";
    lista<int> lista_test;
    std::cout << "Hello World!\n";

    lista_test.add_head(2);
    lista_test.add_head(3);
    lista_test.add_head(4);
    lista_test.add_head(5);
    lista_test.add_head(6);
    std::cout << "Hello World!\n";

    std::cout << lista_test.output_dane(0) << std::endl;
    std::cout << lista_test.output_dane(1) << std::endl;
    std::cout << lista_test.output_dane(2) << std::endl;
    std::cout << lista_test.output_dane(3) << std::endl;
    std::cout << lista_test.output_dane(4) << std::endl;

    std::cout << "Hello World!\n";
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
