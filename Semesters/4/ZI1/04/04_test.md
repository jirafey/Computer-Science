-- 1. Pokaż tablicę pracownicy (employees). Uporządkuj wiersze według wartości z kolumny officeCode malejąco.

-- 1/1 points
```sql
SELECT * FROM employees ORDER BY `officeCode` DESC
```
-- 2. Pokaż ilu pracowników zatrudnia każdy z oddziałów firmy. 
-- Pokaż numery oddziałów (officeCode) oraz liczbę zatrudnionych pracowników. 
-- Wiersze uporządkuj od największej liczby zatrudnionych osób.

-- 0.5/1 points
```sql
SELECT officeCode, employeeNumber FROM employees ORDER BY `officeCode` DESC
```
-- 3. Ilu klientów (tablica customers) jest z USA?

-- 0/1 points
```sql
SELECT DISTINCT `country` FROM customers WHERE country==`France` 
```
-- 4. Z tablicy products, pokaż średnią cenę zakupu (buyPrice) modeli z linii Classic Cars. 
-- Wartość zaokrąglij do dwóch miejsc po przecinku.

-- 0.5/1 points
```sql
SELECT * ROUND(SUM `buyPrice`/COUNT `buyPrice`,2) FROM products 
```
-- 5. Ile modeli których cena sprzedaży (MSRP) jest mniejsza niż 100 ma na magazynie firma. 
-- 0.5/1 points
```sql
SELECT * FROM products WHERE (MSRP <100)
```
-- 6. W tabeli szczegóły zamówienia (orderdetails) pogrupuj zamówienia według ich numerów (orderNumber). 
-- Dla każdego zamówienia zsumuj liczbę zamawianych modeli (quantityOrdered). 
-- Pokaż tylko te zamówienia w których liczba zamawianych modeli jest większa lub równa 500. Wyniki uporządkuj malejącą od najwyższej sumy. 
-- Pokaż numer zamówienia oraz liczbę zamawianych modeli.

-- 0/1 points
-- not answered.