#include <math.h>
#include <iostream>
using namespace std;

void calc();
int main(){
    calc();
}

void calc()
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
        case '-':
        cout << a - b << endl; 
        case '/':
        cout << a / b << endl;
        case '*':
        cout << a * b << endl;
        case '^':
        cout << pow(a,b) << endl;
        case '!':
        double result = a;
        for (int i = b; i >0; i--){
            result*=i;
        }
        cout << result << endl;
        // printf("%lf", result);

    }

}

