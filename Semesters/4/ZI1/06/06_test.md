-- 1. Pokaż zamówienia w których zamówiono łącznie co najmniej 600 egzemplarzy modeli.
-- Pokaż numer zamówienia oraz ile modeli w nim zamówiono.
-- Uszereguj od najliczniejszego zamówienia.

-- 1/1 points
```sql
SELECT orderdetails.orderNumber, SUM(orderdetails.quantityOrdered) AS `quantityOfOrderedModels`
FROM orderdetails GROUP BY orderNumber
HAVING SUM( orderdetails.quantityOrdered ) >=600
ORDER BY `quantityOfOrderedModels` DESC
```
-- 2. Pokaż nazwy klientów(customerName), którzy nie złożyli żadnego zamówienia,
-- ale mają przypisanego pracownika odpowiedzialnego za kontakt(salesRepEmployeeNumber).

-- 1/1 points
```sql
SELECT customers.customerName
FROM customers
JOIN products on customers.customerNumber = products.customerNumber 
```
-- 3. Pokaż ile sztuk modeli średnio na jedno zamówienie sprzedawali producenci.
-- Uporządkuj te wyniki od największej wartości.
-- Pokaż nazwy producentów oraz wyniki zaokrąglone do dwóch miejsc po przecinku. 
-- Użyj funkcji JOIN, niezbędne dane są w tabelach producenci oraz szczegóły zamówienia(orderdetails).
![alt text](TAB.1.png)
-- 1/1 points
```sql
SELECT products.productVendor, ROUND(... ,2)
FROM products
JOIN orderdetails ON products.productCode = orderdetails.productCode
ORDER BY DESC
```
-- 4. Pokaż imiona i nazwiska pracowników(employees), 
którzy obsługują klientów(customers), którzy średnio na jeden przelew dokonywali najwyższych płatności. Istotne są tylko te powyżej 50000. Użyj zagnieżdżonego zapytania. Poniżej wynik jaki powinno dawać zapytanie. Kolejność nie jest istotna. 

![alt text](TAB.2.png)
-- 1/1 points
```sql
SELECT employees.lastName, employees.firstName
FROM employees
WHERE employees.employeeNumber IN (
    SELECT customers.salesRepEmployeeNumber
    FROM customers
    JOIN payments ON customers.customerNumber = payments.customerNumber
    GROUP BY payments.customerNumber
    HAVING AVG(payments.amount) > 50000 )
```