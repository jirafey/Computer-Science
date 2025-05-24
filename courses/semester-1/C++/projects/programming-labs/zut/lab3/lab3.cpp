#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <math.h>

using namespace std;

int main()
{
    // Zadanie 1.
    printf("\n1.\n");
    cout << "Hello World" << endl;
    
    // Zadanie 2.
    printf("\n2.\n");
    cout << "Bardzo\ndlugi\nnapis" << endl;

    // Zadanie 3.
    printf("\n3.\n");
    cout << "Napis zawierajacy rozne dziwne znaczki // \\ \\ $ & %" << endl;

    // Zadanie 4.
    printf("\n4.\n");
    int input_val; 
    cin >> input_val;
    cout << "Wpisana wartosc to: " << input_val << endl;
    
    // Zadanie 5.
    printf("\n5. Wpisz liczbe wymierna\n");
    float liczba_wymierna;
    cin >> liczba_wymierna;
    cout << "Wpisana liczba wymierna to: " << liczba_wymierna << endl;
    
    // Zadanie 6.
    printf("\n6.\n");
    int num1,num2,num3;
    cin >> num1;
    cin >> num2;
    cin >> num3;
    printf("Wpisane liczby to:");
    cout << num1 << endl;
    cout << num2 << endl;
    cout << num3 << endl;
    
    // Zadanie 7.
    printf("\n7.\n");
    int num4;
    cin >> num4;
    cout << num4+1 << endl;
    
    // Zadanie 8.
    printf("\n8.\n");
    int num5,num6,num7;
    cin >> num5;
    cin >> num6;
    cin >> num7;
    cout << (num5+num6+num7) /3 << endl;
    
    // Zadanie 9.
    printf("\n9.\n");
    float x;
    cin >> x;
    cout << pow(x,0.5) << endl;
    
    // Zadanie 10.
    printf("\n10.\n");
    float absolute_val_num;
    cin >> absolute_val_num;
    cout << abs(absolute_val_num) << endl;
    
    // Zadanie 11.
    printf("\n11.\n");
    float num8;
    cin >> num8;
    cout << num8 << setprecision(6)<< endl;
    
    // Zadanie 12.
    printf("\n12.\n");
    float num9;
    cin >> num9;
    cout << scientific << num9 << endl;
}