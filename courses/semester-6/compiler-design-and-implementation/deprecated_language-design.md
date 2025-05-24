# Projekt własnego języka: Expression
## Opis ogólny języka

`Expression` jest statycznie pisanym językiem programowania, który cechuje się prostą składnią oraz obsługą dynamicznych struktur danych, takich jak tablice. Język oferuje podstawowe typy danych, operacje arytmetyczne, konstrukcje warunkowe i pętle. Zawiera również możliwość definiowania funkcji oraz manipulowania pamięcią dynamiczną za pomocą `malloc` i `free`.

## Podstawowe słowa kluczowe

* `int` — typ liczby całkowitej
* `double` — typ liczby zmiennoprzecinkowej
* `string` — typ łańcucha znaków
* `mut` — deklaracja zmiennej (może być zmieniana)
* `const` — deklaracja zmiennej stałej (niezmienialnej)

## Zasady składniowe
* `'!'` służy do wykonywania linii
* `'?'` służy do wykonywania linii oraz wypisywania jej na stdout
* Każda linia musi kończyć się znakiem `'!'` lub `'?'` w szczególnych przypadkach ze słowem kluczowym `as` lub `with` może się zakończyć `'"'` lub `')'`
* Komentarze w kodzie zapisujemy po słowie kluczowym `'//'`.
* Zmienna może mieć nazwę składającą się z liter, emotikonów i innych znaków, ale nie może zaczynać się wielką literą lub cyfrą.

## Przykładowe konstrukcje językowe


### Deklaracja zmiennych
```c
mut int a = 10! // Deklaracja zmiennej a typu int
mut string hello = "Hello"!  // Deklaracja zmiennej hello typu string
mut string wave = "Wave"!
```

### Deklaracja stałych
```c
const double pi = 3.14!
print(pi)!  // Wypisuje 3.14

pi = 4!  // Błąd: nie można zmieniać wartości zmiennej stałej
```

### Tablice jednowymiarowe i wielowymiarowe
```c
mut int arr[3] = [1, 2, 3]!  
// Tablica jednoelementowa typu int
mut int arr2[3][2] = [[1, 2], [3, 4], [5, 6]]!  
// Tablica dwuwymiarowa
arr2? as "int[][]" 
// wypisuje wszystkie elementy arr2
```

### Wypisywanie na stdout
```c
"Hello World"? 
// również wypisuje na stdout
print("Hello World!")!  
// Wypisuje "Hello World"
print(hello)!            
// Wypisuje zawartość zmiennej hello, czyli "World"
hello? // wypisuje na stdout "Hello"
```

### Czytanie z stdin
```c
mut int age = input("Wpisz swój wiek")? 
// wypisuje to co się wpisało do stdin
```

### Operacje arytmetyczne
```c
mut int num1 = 2!
mut int num2 = 4!
print(num1 + num2)!  // Wynik: 6
print(num1 - num2)!  // Wynik: -2
print(num1 * num2)!  // Wynik: 8
print(num1 / num2)!  // Wynik: 0.5

num1 = num2 + num1!  // Przypisuje do num1 sumę num1 + num2
num1?  // Wynik: 6
```

### Warunki if, else if, else, ">", "==", "<"
```c
if (num1 == num2) {
    print("True")!  
    // Jeśli num1 jest równe num2, wypisuje "True"
} else {
    print("False")!
}
if (num1 == num2) {
    "True"?  
    // Jeśli num1 jest równe num2, wypisuje "True"
} else if (num1 > num2) {
    "greater than num2"?
} else { 
    "lower than num2"?
}

if (a < b) {
    print("a is lower than b")!
} else if ( {
    print("b is greater than a")!
}
```

### Operacje negacji "~"
```c
mut int num4 = 10!
if (num4 ~= 10) {
    print("num4 is not 10!")!
} else {
    print("num4 is 10!")!  
    // Wypisuje "num4 is 10!"
}
```

### Pętla for
```c
for (mut int i = 0; i < num2; i = i + 1) {
    mut result = i * i? 
    // Wynik: 0, 1, 4, 9
}
```

### Pętla while
```c
mut int num3 = 4!
while (num3 > 0) {
    num3 = num3 - 1!
    print(num3)!  
    // Wynik: 3, 2, 1, 0
}
```

### Funkcje
```c
int f cube(mut int a) -> {  
// Definicja funkcji cube, zwracającej wartość a^3
    return a * a * a!
}
int result = cube(3)!
print(result)!  // Wynik: 27

int f sq(int x) -> {
    return x * x!
}

print(sq(4))!  // Wypisuje 16


int f(mut int x) minus2 -> { x - 2 }!
```

### Dynamiczna alokacja pamięci

```c
mut int[] a = malloc(int, 3)! 
// Dynamicznie alokuje pamięć na tablicę 3 elementów typu int.
a = [2, 3, 4]!  
// Inicjalizacja tablicy a
free(a)!  
// Zwalnianie pamięci
```

## Dodatkowe konstrukcje

### Słowo kluczowe "with"
```c
with ([4,6,8]) {
    for (int i=0; i<3; i++) {
        print(square()+"\n")! // Wypisuje 16, 36, 64 w nowych linijkach
    }
}
```

### Funkcje lambda (anonimowe)
```c
int f fib(mut int n) -> { if (n<2) {n!} else {fib(n-1) + fib(n-2)!} }
int f cube(mut int n) -> n*n*n!
int f add2nsq(mut int n) {
    mut int result = (n + 2)!
    result = result * result!
    return result!
}
|x <- { cube(add2nsq(x + fib(x))) }| with ([1, 2, 9, 15]) ? as "int[]"
// applies a lambda (anonymous function) - cube(add2nsq(x+fib(x)))
// to x which is passed as [1,2,9,15]
// ? as "int[]" -> print elements of the resulting int array


|[x, y] <- { cube(x+y) }| with ([1, 2, 9, 15], [3,4,5,6]) ? as "int[]"
// applies cube lambda function to array1[i] and array2[i] addition result
// print elements of the int array

mut int[] z = |[x,y] <- { cube(x+y) }| with ([1, 2, 3], [4, 5, 6])!? as "int[]"
```

### Słowo kluczowe "reverse"
```c
{
mut string hello = "Hello"!
print(hello)! // Wypisuje Hello ... po `reverse!` wypisuje jeszcze world!
hello = "world!"!
reverse!
}
```

### Użycie "!" wielokrotnie
```c
for (int i=0; i<12; i++) {
    i = i+1!!! // 0 = 3, 4=7, 8=11
    print(i)!!// 33 77 1111
    print("\n")!
}
```

### Inkrementacja argumentów tymczasowo 
```c
mut int number1 = 1!
mut int number2 = 2? // wypisuje 2
number2? // wypisuje 2
mut int number3 = 3!? // wypisuje 3
number3? with (+=1)? // wypisuje 4, 5
number3? // wypisuje 3
cube(number3)? ? with (+=1)?? // +=1, +=1, +=1
// wypisuje 9, 16, 25, 36
number3? // wypisuje 3
```
