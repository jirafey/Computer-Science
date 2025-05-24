#include <iostream>
#include <math.h>
// #include "C:/Users/jiraf/New folder/ㅤ ㅤ/Workspace/Programming/C++/projects/other/calculator.cpp";

using namespace std;

// Zad.1
void zad1_abs()
{
    printf("\n1.\n");
    int n;

    cin >>  n;
    if (n < 0){
        cout << -1 *n << endl;
    }
    else
    {
        cout << n << endl;
    }
}

// Zad.2
void zad2_higher(){
    printf("\n2.\n");
    int high_low1;
    int high_low2;

    cin >> high_low1;
    cin >> high_low2;
    if (high_low1 > high_low2){
        cout << high_low1 << endl;
    }else if (high_low1 == high_low2)
    {
        cout << high_low1 << endl;
    }
    else
    {
        cout << high_low2 << endl;
    }
}

// Zad.3    
void zad3_highest_3(){
    printf("\n3.\n");

    int highest_1;
    int highest_2;
    int highest_3;

    cin >> highest_1;
    cin >> highest_2;
    cin >> highest_3; 
    int highest_val = highest_1;
    if (highest_2 > highest_val){
        highest_val = highest_2;
    } else if (highest_3 > highest_val)
        highest_val = highest_3;
    cout << highest_val << endl;
}

// Zad.4
void zad4_higher_abs(){
    printf("\n4.\n");
    int higher_abs_1;
    int higher_abs_2;

    cin >> higher_abs_1;
    cin >> higher_abs_2;
    if (abs(higher_abs_1) > abs(higher_abs_2)){
        cout << higher_abs_1<< endl;
    }
    else
    {
        cout << higher_abs_2 << endl;
    }
    }
// Zad.5
void zad5_area(){
    printf("\n5.\n");
    int side_a;
    int side_b;
    int side_c;
    int choice;

    cin >> choice;
    switch (choice){
        case 0:
        cin >> side_a;
        cin >> side_b;
        cin >> side_c; 
        int height_case0;
        height_case0 = pow(pow(side_c,2) - pow((side_a)/2,2),0.5);
        
        cout << (side_a*height_case0)/2 << endl;
        case 1:
        int height_case1;
        cin >> side_a;
        cin >> height_case1;
        cout << (side_a * height_case1) /2<< endl;
    }
}

// Zad.6    
void zad6_linear_equations(){
    // Solving a system of 2 linear equations by Cramer's Rule
    printf("\n6.\n");
    double a_1,b_1,c_1;
    double a_2,b_2,c_2;
    double wx,wy,w;

    cin >> a_1,b_1,c_1;
    cin >> a_2,b_2,c_2;

    wx = c_1*b_2 - b_1*c_2;
    wy = a_1*c_2 - c_1*a_2;
    w = a_1*b_2 - b_1*a_2;

    if (w==0){
        printf("Uklad nieoznaczony - nieskonczona liczba rozwiazann.\n");
        if (wx == 0 && wy == 0){
            printf("Uklad sprzeczny - nie ma rozwiazan w zbiorze liczb rzeczywistych.\n");
        }
    }else{
        cout << wx/w << endl;
        cout << wy/w << endl;
    }

}

// Zad.7
void zad7_quadratic_equation()
{
    printf("\n7.\n");
    int a_square;
    int b_square;
    int c_square;

    cin >> a_square;
    if (a_square ==0){
        printf("Nie ma rozwiazan dla a = 0");
    }
    else{
        cin >> b_square; 
        cin >> c_square;
    }

    int sqr_delta = pow((pow(b_square,2) - 4*a_square*b_square),0.5);

    int x1 = (-1*b_square - sqr_delta)/2*a_square;
    int x2 =  (-1*b_square + sqr_delta)/2*a_square;
    
    cout << x1 << endl;
    cout << x2 << endl;

}
// Zad.8
    void zad8_size_area(){
    printf("\n8.\n");
    double size_1;
    double size_2;
    double size_3;
    int sqr_rect_tri;
    printf("Prosze wpisac liczbe w zaleznosci od zamierzonego dzialania: 1- kwadrat, 2-prostokat, 3- trojkat");
    cin>> sqr_rect_tri;
    while (sqr_rect_tri == 1 || sqr_rect_tri == 2 || sqr_rect_tri == 3){
        if (sqr_rect_tri == 1){
                cin >> size_1; 
                cout << size_1*size_1 << endl;
            } else if (sqr_rect_tri == 2){
                cin >> size_1; 
                cin >> size_2; 
                cout << size_1*size_2 << endl;
            } else if (sqr_rect_tri == 3){
                cin >> size_1; 
                cin >> size_2; 
                cin >> size_3; 
                int height_case0;
                height_case0 = pow(pow(size_1,2) - pow((size_2)/2,2),0.5);
                cout << (size_2*height_case0)/2 << endl;

            } else{
                printf("Wprowadzono niepoprawna liczbe\n");
                printf("Proszę wprowadz 1/2/3\n");

            }
    } 
    }
// Zad.9
void zad9_calc()
{
    double a;
    double b;
    char op;

    cout << "Input value for the first number" << endl;
    cin >> a;
    cout << "Input value for the second number" << endl;
    cin >> b;
    cout << "Input the operator" << endl;
    cin >> op;
    
    switch(op){
        case '+':
        cout << a + b << endl;
        break;
        case '-':
        cout << a - b << endl; 
        break;
        case '/':
        cout << a / b << endl;
        break;
        case '*':
        cout << a * b << endl;
        break;
        case '^':
        cout << pow(a,b) << endl;
        break;
        case '!':
        double result = a;
        for (int i = b; i >0; i--){
            result*=i;
        }
        cout << result << endl;
        break;
        // printf("%lf", result);

    }

}
int main()
{   
    // Zad. 1.
    zad1_abs();
    
    // Zad. 2.
    zad2_higher();
    
    // Zad. 3.
    zad3_highest_3();
    
    // Zad. 4.
    zad4_higher_abs();
    
    // Zad. 5.
    zad5_area();
    
    // Zad. 6.
    zad6_linear_equations();
    
    // Zad. 7.
    zad7_quadratic_equation();
    
    // Zad. 8.
    zad8_size_area();
    
    // Zad. 9.
    zad9_calc();
}