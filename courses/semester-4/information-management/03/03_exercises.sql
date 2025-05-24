-- 1.
SELECT customerName
FROM customers
WHERE city = "OSLO"

-- 2.
SELECT productName
FROM products
WHERE MSRP > 200

-- 3.
SELECT DISTINCT customerNumber
FROM payments
WHERE amount > all(SELECT amount from payments where customerNumber = (321 or 148))

-- 4.
SELECT city
FROM customers
WHERE postalCode IS NULL
AND state IS NOT NULL

-- 5.1.
SELECT e.firstName, e.lastName
FROM employees e
JOIN offices o ON e.officeCode = o.officeCode
WHERE o.city = "Paris";

-- 5.2.
SELECT firstName, lastName
FROM employees
WHERE officeCode = (
SELECT officeCode
FROM offices
WHERE city = "Paris" ) 

-- 6.
SELECT productName
FROM products
WHERE productscale = "1:10" AND productVendor = "Second Gear Diecast"
