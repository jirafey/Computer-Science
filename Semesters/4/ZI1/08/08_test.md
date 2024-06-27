-- 1. Pokaż wszystkie imiona znajdujące się w bazie (bez powtórzeń!) . Imiona zarówno pracowników jak i przedstawicieli klientów. Uporządkuj alfabetycznie.

-- 1/1 points
SELECT customers.contactFirstName
FROM customers
UNION SELECT employees.firstName
FROM employees
ORDER BY 1

-- 2. Dla zamówienia 10217 pokaż nazwy wszystkich zamówionych modeli oraz ile sztuk każdego z nich zamówiono. 
-- Użyj funkcji JOIN.

-- 1/1 points
SELECT products.productName, orderdetails.quantityOrdered
FROM products
JOIN orderdetails ON orderdetails.productCode = products.productCode
WHERE orderdetails.orderNumber = "10217"

-- 3. Pokaż nazwy kanadyjskich firm(klienci) wraz z odpowiedzialnymi za nie pracownikami. Dla pracowników pokaż ich imiona, nazwiska oraz miasta w których pracują. Potrzebujesz trzech tablic. 
-- Użyj funkcji JOIN.

-- 1/1 points
SELECT employees.firstName, employees.lastName, customers.customerName, offices.city
FROM customers
JOIN employees ON customers.salesRepEmployeeNumber = employeeNumber
JOIN offices ON employees.officeCode = offices.officeCode
WHERE customers.country="Canada"

-- 4. Pokaż WSZYSTKIE! niemieckie firmy. Dla każdej nazwy klienta pokaż również imię i nazwisko zajmującego się nim pracownika (jeżeli taki jest).
-- Użyj funkcji JOIN.

-- 1/1 points
SELECT employees.firstName, employees.lastname, customers.customerName
FROM employees
JOIN customers ON employees.employeeNumber = customers.salesRepEmployeeNumber
JOIN offices ON employees.officeCode = offices.officeCode WHERE customers.country="Germany"

-- Pokaż wszystkich klientów oraz ile złożyli zamówień. Wyniki uszereguj według ilości zamówień rosnąco. Tabela ma zawierać wszystkich klientów, a więc również takich którzy niczego nie zamawiali.
-- Użyj funkcji JOIN.

-- 5. 0.5/1 points
SELECT customers.firstName, customers.lastName FROM customers GROUP BY ASC

-- Pokaż imię i nazwisko każdego sprzedawcy (czyli "Sales Rep"). Oprócz imienia i nazwiska dla każdego sprzedawcy pokaż z ilu różnych krajów (czyli bez powtórzeń) pochodzą jego klienci. Uszereguj od tego sprzedawcy który "obsługuje" najwięcej krajów. 
-- Użyj funkcji JOIN.

-- 6. 0/1 points
-- not answered.