-- 1.
SELECT orderdetails.orderNumber, SUM(orderdetails.quantityOrdered) 
AS `liczba zamowionych modeli` 
FROM orderdetails
GROUP BY 1 HAVING SUM(orderdetails.quantityOrdered) >= 600 ORDER BY 2 DESC

-- 4.
SELECT employees.lastName, employees.firstName
FROM employees
WHERE employees.employeeNumber IN (
    SELECT customers.salesRepEmployeeNumber
    FROM customers
    JOIN payments ON customers.customerNumber = payments.customerNumber
    GROUP BY payments.customerNumber
    HAVING AVG(payments.amount) > 50000
)
