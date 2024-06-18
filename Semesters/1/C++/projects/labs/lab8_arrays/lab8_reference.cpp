#include <iostream>
#include <tuple>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>

using namespace std;

int nieujemna_n() {
	int n;
	cout << "Wprowadz liczbe n: ";
	cin >> n;
	while (n < 0) {
		cout << "Liczba musi byc dodatnia" << endl;
		cout << "Wprowadz liczbe n: ";
		cin >> n;
	}
	return n;
}

// ZAD 1
/*   Napisz funkcję, która otrzymuje dwa argumenty: nieujemną liczbę całkowitą n oraz n-elementową tablicę
	tab elementów typu int i:
	a. nadaje wartość zero wszystkim elementom tablicy tab,
	b. zapisuje do kolejnych elementów tablicy wartości równe ich indeksom (do komórki o indeksie i
	funkcja ma zapisywać wartość i),
	c. c) podwaja wartość wszystkich elementów w tablicy tab,
	d. d) do wszystkich komórek tablicy tab wstawia wartości bezwzględne ich pierwotnych wartości. 
*/

void zad1_funkcja(int * tab, int tab_lenght) {
	//a. nadaje wartość zero wszystkim elementom tablicy tab,
	for (int i = 0; i < tab_lenght; i++) {
		tab[i] = 0;
		printf("tab[%d] = %d\n", i, tab[i]);
	}

	//b. zapisuje do kolejnych elementów tablicy wartości równe ich indeksom(do komórki o indeksie i
	//funkcja ma zapisywać wartość i),
	cout << "" << endl;
	for (int i = 0; i < tab_lenght; i++) {
		tab[i] = i;
		printf("tab[%d] = %d\n", i, tab[i]);
	}

	//c. podwaja wartość wszystkich elementów w tablicy tab,
	cout << "" << endl;
	for (int i = 0; i < tab_lenght; i++) {
		tab[i] *= 2;
		printf("tab[%d] = %d\n", i, tab[i]);
	}

	//d. do wszystkich komórek tablicy tab wstawia wartości bezwzględne ich pierwotnych wartości.
	cout << "" << endl;
	for (int i = 0; i < tab_lenght; i++) {
		if (tab[i] < 0) {
			tab[i] *= -1;
		}
		printf("tab[%d] = %d\n", i, tab[i]);
	}
}

void zad1() {
	int tab[10];

	int tab_lenght = sizeof(tab) / sizeof(int);

	zad1_funkcja(tab, tab_lenght);
}

// ZAD 2
/*  Napisz funkcję, która otrzymuje dwa argumenty: dodatnią liczbę całkowitą n oraz n-elementową tablicę tab
	o elementach typu int i zwraca jako wartość:
	a. średnią arytmetyczną elementów tablicy tab.
	b. sumę elementów tablicy tab,
	c. sumę kwadratów elementów tablicy tab.
*/

tuple<int, int, int> zad2_funkcja(int * tab, int tab_lenght) {
	int srednia = 0;
	int suma = 0;
	int suma_kwadratow = 0;

	//a. średnią arytmetyczną elementów tablicy tab.
	for (int i = 0; i < tab_lenght; i++) {
		srednia += tab[i];
		printf("tab[%d] = %d\n", i, tab[i]);
	}
	srednia = srednia / tab_lenght;

	//b. sumę elementów tablicy tab,
	for (int i = 0; i < tab_lenght; i++) {
		suma += tab[i];
	}

	//c. sumę kwadratów elementów tablicy tab.
	for (int i = 0; i < tab_lenght; i++) {
		suma_kwadratow += tab[i] * tab[i];
	}
	return make_tuple(srednia, suma, suma_kwadratow);
}

void zad2() {
	int tab[10] = {1,2,3,4,5,6,7,8,9,10};

	int tab_lenght = sizeof(tab) / sizeof(int);

	auto dane = zad2_funkcja(tab, tab_lenght);

	cout << "" << endl;
	cout << "Srednia arytmetyczna: " << get<0>(dane) << endl;
	cout << "Suma elementow: " << get<1>(dane) << endl;
	cout << "Suma kwadratow: " << get<2>(dane) << endl;
}

// ZAD 3
/*  Napisz funkcję, która otrzymuje dwa argumenty: dodatnią liczbę całkowitą n oraz n-elementową tablicę tab
	o elementach typu const int i zwraca jako wartość średnią arytmetyczną elementów tablicy tab.
*/

int zad3_funkcja(const int* tab, int tab_lenght) {
	int srednia = 0;

	for (int i = 0; i < tab_lenght; i++) {
		srednia += tab[i];
	}
	return srednia / tab_lenght;
}

void zad3() {
	const int tab[10] = { 1,2,3,4,5,6,7,8,9,10 };

	int tab_lenght = sizeof(tab) / sizeof(int);

	cout << "Srednia elementow: " << zad3_funkcja(tab, tab_lenght);
}

// ZAD 4
/*  Napisz funkcję, która otrzymuje trzy argumenty: dodatnią liczbę całkowitą n oraz dwie n-elementowe
	tablice tab1, tab2 o elementach typu int i:
	a. przepisuje zawartość tablicy tab1 do tablicy tab2,
	b. przepisuje zawartość tablicy tab1 do tablicy tab2 w odwrotnej kolejności (czyli element tab1[0] ma
	zostać zapisany do komórki tablicy tab2 o indeksie n − 1). 
*/

void zad4_funkcja(int tab1[], int tab2[], int n) {
	// a. przepisuje zawartość tablicy tab1 do tablicy tab2,
	for (int i = 0; i < n; i++) {
		tab2[i] = tab1[i];
		printf("tab2[%d] = %d | tab1[%d] = %d\n", i, tab2[i], i, tab1[i]);
	}
	cout << "" << endl;

	// przepisuje zawartość tablicy tab1 do tablicy tab2 w odwrotnej kolejności (czyli element tab1[0] ma
	// zostać zapisany do komórki tablicy tab2 o indeksie n − 1).
	for (int i = 0; i < n; i++) {
		tab2[n - (1 + i)] = tab1[i];
	}
	// druga petla do wyswietlenia wynikow
	for (int i = 0; i < n; i++) {
		printf("tab2[%d] = %d | tab1[%d] = %d\n", i, tab2[i], i, tab1[i]);
	}
}

void wypelnienie_tablicy_n_elementowej(int* tab, int tab_lenght) {
	for (int i = 0; i < tab_lenght; i++) {
		tab[i] = i + 1;
	}
}

void wypelnienie_tablicy_n_elementowej_odwrotnie(int* tab, int tab_lenght) {
	for (int i = tab_lenght-1; i >= 0; i--) {
		tab[i] = i+1;
	}
}

void zad4() {
	const int n = 10;
	int tab1[n], tab2[n];
	
	wypelnienie_tablicy_n_elementowej(tab1, n);
	wypelnienie_tablicy_n_elementowej_odwrotnie(tab2, n);

	zad4_funkcja(tab1, tab2, n);
}

// ZAD 5
/*  Napisz funkcję, która otrzymuje cztery argumenty: dodatnią liczbę całkowitą n oraz trzy n-elementowe
	tablice tab1, tab2 i tab3 o elementach typu int, i:
	a. przypisuje elementom tablicy tab3 sumę odpowiadających im elementów tablic tab1 i tab2 (do
	komórki tablicy tab3 o indeksie i powinna trafić suma elementów tab1[i] i tab2[i]),
	b. przypisuje elementom tablicy tab3 większy spośród odpowiadających im elementów tablic tab1 i
	tab2 (do komórki tablicy tab3 o indeksie i powinien trafić większy spośród elementów tab1[i] i
	tab2[i]),
	c. przypisuje zawartość tablicy tab1 do tablicy tab2, zawartość tablicy tab2 do tablicy tab3 oraz
	zawartość tablicy tab3 do tablicy tab1.
*/

void wypelnienie_tablicy_n_elementowej_losowo(int* tab, int tab_lenght) {
	for (int i = 0; i < tab_lenght; i++) {
		tab[i] = rand() % 10 + 1;
	}
}

void zad5_funkcja(int n, int tab1[], int tab2[], int tab3[]) {
	// a. przypisuje elementom tablicy tab3 sumę odpowiadających im elementów tablic tab1 i tab2 (do
	// komórki tablicy tab3 o indeksie i powinna trafić suma elementów tab1[i] i tab2[i]),
	cout << "a." << endl;
	for (int i = 0; i < n; i++) {
		tab3[i] = tab1[i] + tab2[i];
		printf("tab3[%d] = tab1[%d] + tab2[%d] | %d = %d + %d\n", i, i, i, tab3[i], tab1[i], tab2[i]);
	}

	// b. przypisuje elementom tablicy tab3 większy spośród odpowiadających im elementów tablic tab1 i
	// tab2(do komórki tablicy tab3 o indeksie i powinien trafić większy spośród elementów tab1[i] i
	// tab2[i]),
	cout << "" << endl;
	cout << "b." << endl;
	for (int i = 0; i < n; i++) {
		if (tab1[i] > tab2[i]) {
			tab3[i] = tab1[i];
		}
		else {
			tab3[i] = tab2[i];
		}
		printf("tab3[%d] = %d | tab1[%d] = %d | tab2[%d] = %d\n", i, tab3[i], i, tab1[i], i, tab2[i]);
	}

	// c. przypisuje zawartość tablicy tab1 do tablicy tab2, zawartość tablicy tab2 do tablicy tab3 oraz
	// zawartość tablicy tab3 do tablicy tab1.
	cout << "" << endl;
	cout << "c." << endl;

	cout << "" << endl;

	wypelnienie_tablicy_n_elementowej_losowo(tab1, n);
	wypelnienie_tablicy_n_elementowej_losowo(tab2, n);
	wypelnienie_tablicy_n_elementowej_losowo(tab3, n);

	for (int i = 0; i < n; i++) {
		printf("tab1[%d] = %d | tab2[%d] = %d | tab3[%d] = %d\n", i, tab1[i], i, tab2[i], i, tab3[i]);
	}

	cout << "" << endl;

	int zastepcza_tab1 = 0, zastepcza_tab2 = 0;

	for (int i = 0; i < n; i++) {
		zastepcza_tab1 = tab1[i];
		zastepcza_tab2 = tab2[i];
		tab1[i] = tab3[i];
		tab2[i] = zastepcza_tab1;
		tab3[i] = zastepcza_tab2;
		printf("tab1[%d] = %d | tab2[%d] = %d | tab3[%d] = %d\n", i, tab1[i], i, tab2[i], i, tab3[i]);
	}
}

void zad5() {
	const int n = 10;
	int tab1[n], tab2[n], tab3[n];

	wypelnienie_tablicy_n_elementowej(tab1, n);
	wypelnienie_tablicy_n_elementowej(tab2, n);
	wypelnienie_tablicy_n_elementowej(tab3, n);

	srand(time(NULL));
	zad5_funkcja(n, tab1, tab2, tab3);
}

// ZAD 6
/*  Napisz funkcję, która otrzymuje cztery argumenty: dodatnią liczbę całkowitą n, n-elementowe tablice tab1
	i tab2 oraz 2 · n-elementową tablicę tab3 o elementach typu double.
	a. Funkcja powinna przepisywać zawartość tablic tab1 i tab2 do tablicy tab3 w taki sposób, że na
	początku tablicy tab3 powinny się znaleźć elementy tablicy tab1, a po nich elementy tablicy tab2.
	b. Funkcja powinna przepisywać zawartość tablic tab1 i tab2 do tablicy tab3 w taki sposób, że w
	komórkach tablicy tab3 o nieparzystych indeksach powinny się znaleźć elementy tablicy tab1, a w
	komórkach tablicy tab3 o parzystych indeksach elementy tablicy tab2. 
*/

void zad6_funkcja(int n, int tab1[], int tab2[], double tab3[]) {
	// a. Funkcja powinna przepisywać zawartość tablic tab1 i tab2 do tablicy tab3 w taki sposób, że na
	//początku tablicy tab3 powinny się znaleźć elementy tablicy tab1, a po nich elementy tablicy tab2.
	wypelnienie_tablicy_n_elementowej_losowo(tab1, n);
	wypelnienie_tablicy_n_elementowej_losowo(tab2, n);
	for (int i = 0; i < (n*2); i++) {
		tab3[i] = rand() % 10 + 1.0;
	}

	for (int i = 0; i < n; i++) {
		printf("tab1[%d] = %d | tab2[%d] = %d\n", i, tab1[i], i, tab2[i]);
	}

	cout << "" << endl;

	for (int i = 0; i < (n*2); i++) {
		printf("tab3[%d] = %f\n", i, tab3[i]);
	}
	
	for (int i = 0; i < n; i++) {
		tab3[i] = tab1[i];
		
	}

	for (int i = n; i < (n * 2); i++) {
		tab3[i] = tab2[i%10];
	}

	cout << "" << endl;

	for (int i = 0; i < (n * 2); i++) {
		printf("tab3[%d] = %f\n", i, tab3[i]);
	}
}

void zad6() {
	const int n = 10;
	int tab1[n], tab2[n];
	double tab3[n * 2];

	srand(time(NULL));

	zad6_funkcja(n, tab1, tab2, tab3);
}

// ZAD 7
/*  Napisz funkcję, która otrzymuje cztery argumenty: dodatnią liczbę całkowitą n oraz trzy n-elementowe
	tablice tab1, tab2 i tab3 o elementach typu int i zamienia zawartości komórek otrzymanych w argumentach
	tablic w następujący sposób:
	• dla dowolnego i komórka tab1[i] powinna zawierać największą spośród pierwotnych wartości
	komórek tab1[i], tab2[i] oraz tab3[i],
	• dla dowolnego i komórka tab2[i] powinna zawierać drugą co do wielkości spośród pierwotnych
	wartości komórek tab1[i], tab2[i] oraz tab3[i],
	• dla dowolnego i komórka tab3[i] powinna zawierać najmniejszą spośród pierwotnych wartości
	komórek tab1[i], tab2[i] oraz tab3[i].
*/

void zad7_funkcja(const int n, int tab1[], int tab2[], int tab3[]) {
	// utworzenie kopii tablic do dzialan
	vector<int> tab1_oryginalna(tab1, tab1 + n);
	vector<int> tab2_oryginalna(tab2, tab2 + n);
	vector<int> tab3_oryginalna(tab3, tab3 + n);
	
	cout << "Poczatkowe wartosci" << endl;
	for (int i = 0; i < n; i++) {
		printf("tab1[%d] = %d | tab2[%d] = %d | tab3[%d] = %d\n", i, tab1[i], i, tab2[i], i, tab3[i]);
	}

	cout << "" << endl;
	
	//  dla dowolnego i komórka tab1[i] powinna zawierać największą spośród pierwotnych wartości
	//	komórek tab1[i], tab2[i] oraz tab3[i],

	cout << "Pierwszy podpunkt" << endl;

	int najwieksza = 0;
	int zastepcza = 0;

	for (int i = 0; i < n; i++) {
		najwieksza = tab1[i];
		if (tab2[i] > tab3[i]) {
			if (tab2[i] > najwieksza) {
				zastepcza = tab1[i];
				tab1[i] = tab2[i];
				tab2[i] = zastepcza;
			}
		}
		else {
			if (tab3[i] > najwieksza) {
				zastepcza = tab1[i];
				tab1[i] = tab3[i];
				tab3[i] = zastepcza;
			}
		}
		printf("tab1[%d] = %d | tab2[%d] = %d | tab3[%d] = %d\n", i, tab1[i], i, tab2[i], i, tab3[i]);
	}

	cout << "" << endl;

	//  dla dowolnego i komórka tab2[i] powinna zawierać drugą co do wielkości spośród pierwotnych
	//  wartości komórek tab1[i], tab2[i] oraz tab3[i],

	// przywracamy wartosci oryginalnych tablic
	copy(tab1_oryginalna.begin(), tab1_oryginalna.end(), tab1);
	copy(tab2_oryginalna.begin(), tab2_oryginalna.end(), tab2);
	copy(tab3_oryginalna.begin(), tab3_oryginalna.end(), tab3);

	cout << "Drugi podpunkt" << endl;

	int druga_najwieksza = 0;
	int indeks = 0;

	for (int i = 0; i < n; i++) {
		indeks = 0;
		najwieksza = tab1[i];
		druga_najwieksza = tab2[i];
		if (najwieksza < druga_najwieksza) {
			druga_najwieksza = najwieksza;
			indeks = 1;
			najwieksza = tab2[i];
		}
		if (najwieksza < tab3[i]) {
			druga_najwieksza = najwieksza;
			indeks = 2;
			najwieksza = tab3[i];
		}
		if (druga_najwieksza < tab3[i] && tab3[i] < najwieksza) {
			druga_najwieksza = tab3[i];
			indeks = 3;
		}
		switch (indeks) {
		case 1:
			zastepcza = tab1[i];
			tab1[i] = tab2[i];
			tab2[i] = zastepcza;
			break;
		case 3:
			zastepcza = tab3[i];
			tab3[i] = tab2[i];
			tab2[i] = zastepcza;
			break;
		}
		printf("tab1[%d] = %d | tab2[%d] = %d | tab3[%d] = %d\n", i, tab1[i], i, tab2[i], i, tab3[i]);
	}

	cout << "" << endl;

	//  dla dowolnego i komórka tab3[i] powinna zawierać najmniejszą spośród pierwotnych wartości
	//  komórek tab1[i], tab2[i] oraz tab3[i].

	// przywracamy wartosci oryginalnych tablic
	copy(tab1_oryginalna.begin(), tab1_oryginalna.end(), tab1);
	copy(tab2_oryginalna.begin(), tab2_oryginalna.end(), tab2);
	copy(tab3_oryginalna.begin(), tab3_oryginalna.end(), tab3);

	int najmniejsza = 0;

	cout << "Trzeci podpunkt" << endl;

	for (int i = 0; i < n; i++) {
		najmniejsza = tab3[i];
		if (tab2[i] < tab1[i]) {
			if (tab2[i] < najmniejsza) {
				zastepcza = tab3[i];
				tab3[i] = tab2[i];
				tab2[i] = zastepcza;
			}
		}
		else {
			if (tab1[i] < najmniejsza) {
				zastepcza = tab3[i];
				tab3[i] = tab1[i];
				tab1[i] = zastepcza;
			}
		}
		printf("tab1[%d] = %d | tab2[%d] = %d | tab3[%d] = %d\n", i, tab1[i], i, tab2[i], i, tab3[i]);
	}
}

void zad7() {
	const int n = 10;
	int tab1[n], tab2[n], tab3[n];

	srand(time(NULL));

	wypelnienie_tablicy_n_elementowej_losowo(tab1, n);
	wypelnienie_tablicy_n_elementowej_losowo(tab2, n);
	wypelnienie_tablicy_n_elementowej_losowo(tab3, n);

	zad7_funkcja(n, tab1, tab2, tab3);
}

// ZAD 8
/*  Napisz funkcję, która otrzymuje dwa argumenty: dodatnią liczbę całkowitą n oraz n-elementową tablicę tab
	o elementach typu int i:
	a. zwraca największą wartość przechowywaną w tablicy tab,
	b. zwraca najmniejszą wartość przechowywaną w tablicy tab,
	c. zwraca indeks elementu tablicy tab o największej wartości,
	d. zwraca indeks elementu tablicy tab o najmniejszej wartości,
	e. zwraca największą spośród wartości bezwzględnych elementów przechowywanych w tablicy tab,
	f. zwraca indeks elementu tablicy tab o największej wartości bezwzględnej. 
*/

tuple<int, int, int, int, int, int> zad8_funkcja(const int n, int tab[]) {
	int najwieksza_wartosc = 0, najmniejsza_wartosc = tab[0], indeks_najwiekszego_elementu = 0;
	int indeks_najmniejszego_elementu = 0, najwieksza_wartosc_bezwzgledna = 0, indeks_najwiekszej_wartosci_bezwzglednej = 0;
	
	// a. zwraca największą wartość przechowywaną w tablicy tab,
	for (int i = 0; i < n; i++) {
		if (tab[i] > najwieksza_wartosc) {
			najwieksza_wartosc = tab[i];
		}
	}

	// b. zwraca najmniejszą wartość przechowywaną w tablicy tab,
	for (int i = 0; i < n; i++) {
		if (tab[i] < najmniejsza_wartosc) {
			najmniejsza_wartosc = tab[i];
		}
	}

	// c. zwraca indeks elementu tablicy tab o największej wartości,
	najwieksza_wartosc = 0;
	for (int i = 0; i < n; i++) {
		if (tab[i] > najwieksza_wartosc) {
			najwieksza_wartosc = tab[i];
			indeks_najwiekszego_elementu = i;
		}
	}

	// d. zwraca indeks elementu tablicy tab o najmniejszej wartości,
	najmniejsza_wartosc = tab[0];
	for (int i = 0; i < n; i++) {
		if (tab[i] < najmniejsza_wartosc) {
			najmniejsza_wartosc = tab[i];
			indeks_najmniejszego_elementu = i;
		}
	}

	// e.zwraca największą spośród wartości bezwzględnych elementów przechowywanych w tablicy tab,
	int wartosc_bezwzgledna = 0;
	
	for (int i = 0; i < n; i++) {
		wartosc_bezwzgledna = tab[i];
		if (wartosc_bezwzgledna < 0) {
			wartosc_bezwzgledna *= -1;
		}
		if (wartosc_bezwzgledna > najwieksza_wartosc_bezwzgledna) {
			najwieksza_wartosc_bezwzgledna = wartosc_bezwzgledna;
		}
	}

	// f. zwraca indeks elementu tablicy tab o największej wartości bezwzględnej. 
	najwieksza_wartosc_bezwzgledna = 0;
	
	for (int i = 0; i < n; i++) {
		wartosc_bezwzgledna = tab[i];
		if (wartosc_bezwzgledna < 0) {
			wartosc_bezwzgledna *= -1;
		}
		if (wartosc_bezwzgledna > najwieksza_wartosc_bezwzgledna) {
			najwieksza_wartosc_bezwzgledna = wartosc_bezwzgledna;
			indeks_najwiekszej_wartosci_bezwzglednej = i;
		}
	}

	return make_tuple(najwieksza_wartosc, najmniejsza_wartosc, indeks_najwiekszego_elementu, indeks_najmniejszego_elementu, najwieksza_wartosc_bezwzgledna, indeks_najwiekszej_wartosci_bezwzglednej);
}

void zad8() {
	const int n = 10;
	int tab[n];

	srand(time(NULL));

	for (int i = 0; i < n; i++) {
		tab[i] = rand() % 21 -10;
	}

	auto dane = zad8_funkcja(n, tab);

	for (int i = 0; i < n; i++) {
		printf("tab[%d] = %d\n", i, tab[i]);
	}

	cout << "" << endl;
	cout << "Najwieksza wartosc: " << get<0>(dane) << endl;
	cout << "Najmniejsza wartosc: " << get<1>(dane) << endl;
	cout << "Indeks najwiekszego elementu: " << get<2>(dane) << endl;
	cout << "Indeks najmniejszego elementu: " << get<3>(dane) << endl;
	cout << "Najwieksza wartosc bezwzgledna: " << get<4>(dane) << endl;
	cout << "Indeks najwiekszej wartosci bezwzglednej: " << get<5>(dane) << endl;
}

// ZAD 9
/*  Napisz funkcję, która otrzymuje dwa argumenty: dodatnią liczbę całkowitą n oraz dwie n-elementowe
	tablice tab o elementach typu double przechowujące n-wymiarowe wektory i zwraca jako wartość iloczyn
	skalarny wektorów otrzymanych w argumentach. 
*/

void wypelnienie_losowe_funkcji_double(double* tab, int n) {
	for(int i = 0; i < n; i++) {
		tab[i] = rand() % 10 + 1;
	}
}

double zad9_funkcja(double* tab1, double* tab2, int n) {
	double iloczyn_skalarny = 0;

	for (int i = 0; i < n; i++) {
		iloczyn_skalarny += tab1[i] * tab2[i];
	}

	return iloczyn_skalarny;
}

void zad9() {
	const int n = 10;
	double tab1[n], tab2[n];

	srand(time(NULL));
	
	wypelnienie_losowe_funkcji_double(tab1, n);
	wypelnienie_losowe_funkcji_double(tab2, n);

	for (int i = 0; i < n; i++) {
		printf("tab1[%d] = %f | tab2[%d] = %f\n", i, tab1[i], i, tab2[i]);
	}

	cout << endl << "Iloczyn skalarny wektorow jest rowny: " << zad9_funkcja(tab1, tab2, n) << endl;
}

int main() {
	//zad1();
	//zad2();
	//zad3();
	//zad4();
	//zad5();
	//zad6();
	//zad7();
	//zad8();
	zad9();
}