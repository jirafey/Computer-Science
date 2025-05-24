#include <iostream>
#include <cmath>
#include "vector_locally.cpp"
using namespace std;
// can make a program to put all of the text into arrays and put inside the functions and template

// PĘTLE

// if count = 1 -> postive number

    

int fibbonacci(int index_given) {
    int first = 0;
    int second = 1;
    int third = 0;
    for (int i=2; i <= index_given; i++) {
        // 0 1 1 2 3 5 8
        third = first + second;
        first = second; 
        second = third; 
    }
    return third;
}
int factorial(int factorial_num_max) {
    int factorial_num = 1;
    for (int i=1; i<= factorial_num_max ;i++) {
            factorial_num *=i ;
        }
    return factorial_num;
}
// 1. Napisz program wczytujący ze standardowego wejścia
// dwie dodatnie liczby całkowite n i m, i wypisujący w
// kolejnych wierszach na standardowym wyjściu wszystkie
// dodatnie wielokrotności n mniejsze od m.
void zad1() {
    std::vector<int> values = getPositiveNumbers(2);
    int multiplied_num= values.at(0);
    int max = values.at(1);
    for (int i = 1;multiplied_num*i<max;i++) {
        cout << multiplied_num*i<< endl;
    }
}

// 2. Napisz program wczytujący ze standardowego wejścia dwie dodatnie
// liczby całkowite n i m, i wypisujący na
// standardowym wyjściu m pierwszych wielokrotności liczby n.
void zad2() {
    std::vector<int> values = getPositiveNumbers(2);
    int multiplied_num= values.at(0);
    int number_of_multiples = values.at(1);

    printf("\n");
        for (int i = 1; i <= number_of_multiples; i++) {
            cout << multiplied_num*i << endl;
        }
}

// 3. Napisz program wczytujący ze standardowego wejścia trzy dodatnie liczby całkowite n, m i k, i wypisujący w
// kolejnych wierszach wszystkie wielokrotności n większe od m i mniejsze od k.
void zad3() {
    std::vector<int> values = getPositiveNumbers(3);
    int n = values.at(0);
    int min = values.at(1);
    int max = values.at(2);

    for (int i=1; n*i< max; i++) {
        if (n*i > min && n*i < max) {
            cout << n*i << endl;
        }
    }
}

// 4. Napisz program, który wczytuje ze standardowego wejścia nieujemną liczbę całkowitą n i wypisuje na
// standardowym wyjściu liczbę n!.
void zad4(){
    std::vector<int> values = getPositiveNumbers(1);
    int factorial_num = values.at(0);
    cout << factorial(factorial_num) << endl;
}

// 5. Napisz program, który wczytuje ze standardowego wejścia nieujemną liczbę całkowitą n i wypisuje na
// standardowym wyjściu sumę kwadratów liczb od 0 do n, czyli wartość 02 + 12 + 32 + ... + n2.
void zad5(){
    std::vector<int> values = getPositiveNumbers(1);
    int number_of_squares= values.at(0);
    int sum_of_squares = 0;
    for (int i=1; i<=number_of_squares ;i++) {
        sum_of_squares+= i*i;
    }
    cout << sum_of_squares << endl;
}

// 6. Napisz program, który wczytuje ze standardowego 
// wejścia liczbę całkowitą n (n > 2) i wypisuje na
// standardowym wyjściu iloczyn liczb parzystych
// z zakresu od 2 do n (czyli 2 ∗ 4 ∗ . . . ∗ n dla n parzystych i 2 ∗
// 4 ∗ . . . ∗ (n − 1) w przeciwnym wypadku).
void zad6(){
    std::vector<int> values = getPositiveNumbers(1);
    int max = values.at(0);
    int result = 2;
    for (int i=2; i<=max; i=i+2) {
        result *= i; 
    }
    if (max % 2 == 1) {
        result*= max;
        cout << result << endl;
    }
    else {
        cout << result << endl;
    }
}

// 7. Napisz program, który wczytuje ze standardowego wejścia dwie liczby całkowite n i m (zakładamy, że n < m)
// i wypisuje na standardowym wyjściu liczbę n ∗ . . . ∗ m.
void zad7(){
    std::vector<int> values = getPositiveNumbers(2);
    int min = values.at(0);
    int max = values.at(1);
    int result = 1;
    while (max < min == true) {
        std::vector<int> values = getPositiveNumbers(2);
    }
    for (min; min<= max; min++) {
        result*= min;
    }
    cout << result << endl;
}

// 8. Napisz program, który wczytuje ze standardowego wejścia nieujemną liczbę całkowitą n i wypisuje na
// standardowym wyjściu element ciągu Fibonacciego o indeksie n.
void zad8(){
    std::vector<int> values = getPositiveNumbers(1);
    int fibbonacci_index_num = values.at(0);

    cout << fibbonacci(fibbonacci_index_num) << endl;
}

// 9. Napisz program, który wczytuje ze standardowego wejścia dodatnie liczby całkowite n i m, i wypisuje na
// standardowym wyjściu największy wspólny dzielnik tych liczb.
void zad9(){

    int n, m;
    int wynik = 0;

    cout << "Wprowadz liczbe n: ";
    cin >> n;
    while (n <= 0) {
        cout << "Liczba musi byc dodatnia" << endl;
        cout << "Wprowadz liczbe n: ";
        cin >> n;
    }

    cout << "Wprowadz liczbe m: ";
    cin >> m;
    while (m <= 0) {
        cout << "Liczba musi byc dodatnia" << endl;
        cout << "Wprowadz liczbe m: ";
        cin >> m;
    }

    for (int i = 1; i <= m && i <= n; i++) {
        if (n % i == 0) {
            if (m % i == 0) {
                wynik = i;
            }
        }
    }
    cout << wynik << endl;
}

// 10. Napisz program, który wczytuje ze standardowego wejścia nieujemną liczbę n i wypisuje na standardowym
// wyjściu wartość ⌊√n⌋ (wartość √n zaokrągloną w dół do najbliższej wartości całkowitoliczbowej). Program
// napisz bez użycia funkcji z biblioteki matematycznej.
void zad10(){

    float n2, est, prev_est = 0;
    float delta = 0.01;

    cout << "Wprowadz liczbe n: ";
    cin >> n2;
    while (n2 <= 0) {
        cout << "Liczba musi byc dodatnia" << endl;
        cout << "Wprowadz liczbe n: ";
        cin >> n2;
    }

    est = n2 / 2.0;
    prev_est = est + 2 * delta;

    while (abs(prev_est - est) > delta) {
        prev_est = est;
        est = (est + n2 / est) / 2.0;
    }

    cout << trunc(est) << endl;

}

// 11. Napisz program, który wczytuje ze standardowego wejścia liczby a, b, c, d i:
// a. wypisuje na standardowe wyjście najmniejszą nieujemną liczbę całkowitą x taką, że |a| ∗ x2 + b ∗ x + c >
// d.
// b. wypisuje na standardowe wyjście największą nieujemną liczbę całkowitą x taką, że 5∗x2+a∗x+b < c.
// Zakładamy, że taka nieujemna całkowita liczba x istnieje.
// c. wypisuje na standardowe wyjście największą nieujemną liczbę całkowitą x taką, że 5∗x2+a∗x+b ≤ c.
// Zakładamy, że taka nieujemna całkowita liczba x istnieje.
void zad11(){
    int a, b, c, d;
    int x = 1;
    
    cout << "Wprowadz a: ";
    cin >> a;
    cout << "Wprowadz b: ";
    cin >> b;
    cout << "Wprowadz c: ";
    cin >> c;
    cout << "Wprowadz d: ";
    cin >> d;

    while (!((abs(a) * x * x + b * x + c) > d)) {
        x++;
    }

    cout << x << endl;

    x = 1;

    while (5 * x * x + a * x + b < c) {
        x++;
    }

    cout << x-1 << endl;

    x = 1;

    while (5 * x * x + a * x + b <= c) {
        x++;
    }

    cout << x - 1 << endl;
}

// 12. Napisz program, który wczytuje ze standardowego wejścia dodatnią liczbę n i wypisuje na standardowym
// wyjściu sumę wszystkich liczb mniejszych od n, względnie pierwszych z n.
void zad12(){
    int i, j, n3;
    int suma = 0;
    int nwd = 0;
    i = 2;

    cout << "Wprowadz n: ";
    cin >> n3;

    while (i < n3) {
        nwd = 0;
        j = 1;
        while (j < i) {
            if (i % j == 0) {
                nwd = j;
            }
            j++;
        }
        if (nwd == 1) {
            suma = suma + j;
            cout << j << endl;
        }
        i++;
    }
    cout << "Suma liczb wzglednie pierwszych: " << suma << endl;
    
}

// 13. Napisz program, który wczytuje ze standardowego wejścia nieujemną liczbę całkowitą n i wypisuje na
// standardowym wyjściu wartość 0! + 1! + . . . + n!.
void zad13(){
    std::vector<int> values = getPositiveNumbers(1);
    int factorial_max = values.at(0);
    int factorial_result = 0;
    for (int i=0; i<=factorial_max; i++) {
        factorial_result += factorial(i);
    }
    cout << factorial_result << endl;
}

// 14. Napisz program, który wczytuje ze standardowego wejścia liczbę n i wypisuje na standardowym wyjściu
// wszystkie trojki pitagorejskie (tj. trojki liczb całkowitych a, b, c takich, że a2 +b2 = c2), składające się z liczb
// mniejszych od n.
void zad14(){
    int n;

        cout << "Wprowadz liczbe n: ";
        cin >> n;

        for (int a = 1; a < n; a++) {
            for (int b = 1; b < n; b++) {
                for (int c = 1; c < n; c++) {
                    if (a * a + b * b == c * c && a < b) {
                        cout << a << " " << b << " " << c << endl;
                    }
                }
            }
        }

}
int main(){
    // Zad 1
    printf("Zad.1\n");

    zad1();

    // Zad 2
    printf("\nZad.2\n");
    zad2();

    // Zad 3
    printf("Zad.3\n");
    zad3();
    
    // Zad 4
    printf("Zad.4\n");
    zad4();
    
    // Zad 5
    printf("Zad.5\n");
    zad5();
    
    // Zad 6
    printf("Zad.6\n");
    zad6();
    
    // Zad 7
    printf("Zad.7\n");
    zad7();
    
    // Zad 8
    printf("Zad.8\n");
    zad8();
    
    // Zad 9
    printf("Zad.9\n");
    zad9();
    
    // Zad 10
    printf("Zad.10\n");
    zad10();
    
    // Zad 11
    printf("Zad.11\n");
    zad11();
    
    // Zad 12
    printf("Zad.12\n");
    zad12();
    
    // Zad 13
    printf("Zad.13\n");
    zad13();
    
    // Zad 14
    printf("Zad.14\n");
    zad14();
}



 