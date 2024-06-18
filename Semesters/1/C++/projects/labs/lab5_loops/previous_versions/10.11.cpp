#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    // PETLE 10.11
    
    // ZAD 1
    /* Napisz program wczytujący ze standardowego wejścia dwie dodatnie liczby całkowite n i m, i wypisujący w
       kolejnych wierszach na standardowym wyjściu wszystkie dodatnie wielokrotności n mniejsze od m. 
    */


    int n, m;

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

    for (int i = n; i < m; i=i*n) {
        cout << i << endl;
    }


    // ZAD 2
    /* Napisz program wczytujący ze standardowego wejścia dwie dodatnie liczby całkowite n i m, i wypisujący na
       standardowym wyjściu m pierwszych wielokrotności liczby n. 
    */

    /*
    int n, m;
    int wynik = 1;

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

    for (int i = 0; i < m; i++) {
        wynik = wynik * n;
        cout << wynik << endl;
    }
    */

    // ZAD 3
    /* Napisz program wczytujący ze standardowego wejścia trzy dodatnie liczby całkowite n, m i k, i wypisujący w
       kolejnych wierszach wszystkie wielokrotności n większe od m i mniejsze od k. 
    */

    /*
    int n, m, k;
    int wynik = 1;

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

    cout << "Wprowadz liczbe k: ";
    cin >> k;
    while (k <= 0) {
        cout << "Liczba musi byc dodatnia" << endl;
        cout << "Wprowadz liczbe k: ";
        cin >> k;
    }

    while (wynik < k) {
        wynik = wynik * n;
        if (wynik > m && wynik < k) {
            cout << wynik << endl;
        }
    }
    */

    // ZAD 4
    /* Napisz program, który wczytuje ze standardowego wejścia nieujemną liczbę całkowitą n i wypisuje na
       standardowym wyjściu liczbę n!.
    */

    /*
    int n;
    int wynik = 1;

    cout << "Wprowadz liczbe n: ";
    cin >> n;
    while (n <= 0) {
        cout << "Liczba musi byc dodatnia" << endl;
        cout << "Wprowadz liczbe n: ";
        cin >> n;
    }

    for (int i = 1; i <= n; i++) {
        wynik = wynik * i;
    }
    cout << wynik << endl;
    */

    // ZAD 5
    /* Napisz program, który wczytuje ze standardowego wejścia nieujemną liczbę całkowitą n i wypisuje na
       standardowym wyjściu sumę kwadratów liczb od 0 do n, czyli wartość 02 + 12 + 32 + ... + n2. 
    */

    /*
    int n;
    int wynik = 0;
    
    cout << "Wprowadz liczbe n: ";
    cin >> n;
    while (n <= 0) {
        cout << "Liczba musi byc dodatnia" << endl;
        cout << "Wprowadz liczbe n: ";
        cin >> n;
    }

    for (int i = 0; i <= n; i++) {
        wynik = wynik + i * i;
    }
    cout << wynik << endl;
    */
    
    // ZAD 6
    /* Napisz program, który wczytuje ze standardowego wejścia liczbę całkowitą n (n > 2) i wypisuje na
       standardowym wyjściu iloczyn liczb parzystych z zakresu od 2 do n (czyli 2 ∗ 4 ∗ . . . ∗ n dla n parzystych i 2 ∗
       4 ∗ . . . ∗ (n − 1) w przeciwnym wypadku).
    */

    /*
    int n;
    int wynik = 1;

    cout << "Wprowadz liczbe n: ";
    cin >> n;
    while (n <= 2) {
        cout << "Liczba musi byc wieksza od 2" << endl;
        cout << "Wprowadz liczbe n: ";
        cin >> n;
    }

    for (int i = 2; i <= n; i = i + 2) {
        wynik = wynik * i;
    }

    cout << wynik << endl;
    */

    // ZAD 7
    /* Napisz program, który wczytuje ze standardowego wejścia dwie liczby całkowite n i m (zakładamy, że n < m)
       i wypisuje na standardowym wyjściu liczbę n ∗ . . . ∗ m. 
    */

    /*
    int n, m;
    int wynik = 1;

    cout << "Wprowadz liczbe n: ";
    cin >> n;
    cout << "Wprowadz liczbe m: ";
    cin >> m;

    while (n >= m) {
        cout << "Liczba n musi byc mniejsza od m" << endl;
        cout << "Wprowadz liczbe n: ";
        cin >> n;
        cout << "Wprowadz liczbe m: ";
        cin >> m;
    }

    for (int i = n; i <= m; i = i++) {
        wynik = wynik * i;
    }

    cout << wynik << endl;
    */

    // ZAD 8
    /* Napisz program, który wczytuje ze standardowego wejścia nieujemną liczbę całkowitą n i wypisuje na
       standardowym wyjściu element ciągu Fibonacciego o indeksie n.
    */

    /*
    int n, a, b;
    a = b = 1;
    int wynik = 1;

    cout << "Wprowadz liczbe n: ";
    cin >> n;
    while (n <= 0) {
        cout << "Liczba musi byc dodatnia" << endl;
        cout << "Wprowadz liczbe n: ";
        cin >> n;
    }
    
    if (!(n == 1 || n == 2)) {
        for (int i = 3; i <= n; i++) {
            wynik = a + b;
            a = b;
            b = wynik;
        }
    }

    cout << wynik << endl;
    */

    // ZAD 9 
    /* Napisz program, który wczytuje ze standardowego wejścia dodatnie liczby całkowite n i m, i wypisuje na
       standardowym wyjściu największy wspólny dzielnik tych liczb. 
    */

    /*
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
    */

    // ZAD 10
    /* Napisz program, który wczytuje ze standardowego wejścia nieujemną liczbę n i wypisuje na standardowym
       wyjściu wartość ⌊√n⌋ (wartość √n zaokrągloną w dół do najbliższej wartości całkowitoliczbowej). Program
       napisz bez użycia funkcji z biblioteki matematycznej. 
    */

    /*
    float n, est, prev_est = 0;
    float delta = 0.01;

    cout << "Wprowadz liczbe n: ";
    cin >> n;
    while (n <= 0) {
        cout << "Liczba musi byc dodatnia" << endl;
        cout << "Wprowadz liczbe n: ";
        cin >> n;
    }

    est = n / 2.0;
    prev_est = est + 2 * delta;

    while (abs(prev_est - est) > delta) {
        prev_est = est;
        est = (est + n / est) / 2.0;
    }

    cout << trunc(est) << endl;
    */

    // ZAD 11
    /* Napisz program, który wczytuje ze standardowego wejścia liczby a, b, c, d i:
       a. wypisuje na standardowe wyjście najmniejszą nieujemną liczbę całkowitą x taką, że |a| ∗ x2 + b ∗ x + c >
       d.
       b. wypisuje na standardowe wyjście największą nieujemną liczbę całkowitą x taką, że 5∗x2+a∗x+b < c.
       Zakładamy, że taka nieujemna całkowita liczba x istnieje.
       c. wypisuje na standardowe wyjście największą nieujemną liczbę całkowitą x taką, że 5∗x2+a∗x+b ≤ c.
       Zakładamy, że taka nieujemna całkowita liczba x istnieje. 
    */

    /*
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
    */

    // ZAD 12
    /* Napisz program, który wczytuje ze standardowego wejścia dodatnią liczbę n i wypisuje na standardowym
       wyjściu sumę wszystkich liczb mniejszych od n, względnie pierwszych z n. 
    */

    /*
    int i, j, n;
    int suma = 0;
    int nwd = 0;
    i = 2;

    cout << "Wprowadz n: ";
    cin >> n;

    while (i < n) {
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
    */

    // ZAD 13
    /* Napisz program, który wczytuje ze standardowego wejścia nieujemną liczbę całkowitą n i wypisuje na
       standardowym wyjściu wartość 0! + 1! + . . . + n!. 
    */

    /*
    int n;
    int suma = 1;
    int poprzedni = 1;

    cout << "Wprowadz liczbe n: ";
    cin >> n;
    while (n <= 0) {
        cout << "Liczba musi byc dodatnia" << endl;
        cout << "Wprowadz liczbe n: ";
        cin >> n;
    }

    for (int i = 1; i <= n; i++) {
        suma = suma + poprzedni * i;
        poprzedni = poprzedni * i;
    }

    cout << "Wynik: " << suma << endl;
    */

    // ZAD 14
    /* Napisz program, który wczytuje ze standardowego wejścia liczbę n i wypisuje na standardowym wyjściu
       wszystkie trojki pitagorejskie (tj. trojki liczb całkowitych a, b, c takich, że a2 +b2 = c2), składające się z liczb
       mniejszych od n. 
    */

    /*
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
    */
}