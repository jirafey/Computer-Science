-- 2. 
SELECT productName, quantityOrdered
FROM orderdetails
JOIN products ON orderdetails.productCode = products.productCode
WHERE orderNumber = 10217
-- 1.
SELECT contactFirstName
FROM  customers 
UNION SELECT firstName FROM employees
ORDER BY contactFirstName
-- 3.
SELECT firstName, lastName, customerName, offices.city
FROM customers
JOIN employees ON customers.salesRepEmployeeNumber = employeeNumber
JOIN offices ON employees.officeCode = offices.officeCode
WHERE customers.country="Canada"

