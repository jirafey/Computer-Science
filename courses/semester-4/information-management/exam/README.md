## Exam group: 3A 
Date: 28/06/2024


### Question 1:
Calculate the average number of days between the order date and the shipped date, rounded to two decimal places.

#### Answer:
```sql
SELECT ROUND(AVG(DATEDIFF(o.shippedDate, o.orderDate)), 2) AS avg_days
FROM orders o;
```
### Question 2:
Retrieve the names of customers whose names contain 'tr'.

#### Answer:
```sql
SELECT c.customerName
FROM customers c
WHERE c.customerName LIKE '%tr%';
```
### Question 3:
List the first three customer last names in alphabetical order.

#### Answer:
```sql
SELECT c.contactLastName
FROM customers c
ORDER BY c.contactLastName ASC
LIMIT 3;
```
### Question 4:
For each day of the week, find the total quantity ordered, ordering the results by the maximum quantity ordered in descending order.

#### Answer:
```sql
SELECT DAYOFWEEK(o.orderDate) AS day_of_week, SUM(od.quantityOrdered) AS total_quantity
FROM orders o
JOIN orderdetails od ON o.orderNumber = od.orderNumber
GROUP BY DAYOFWEEK(o.orderDate)
ORDER BY total_quantity DESC;
```
### Question 5:
Retrieve the order number, status, and customer number for each order.

#### Answer:
```sql
SELECT o.orderNumber, o.status, c.customerNumber
FROM orders o
JOIN customers c ON o.customerNumber = c.customerNumber;
```
### Question 6:
Get the first and last names of employees who work in the USA.

#### Answer:
```sql
SELECT e.firstName, e.lastName
FROM employees e
JOIN offices o ON e.officeCode = o.officeCode
WHERE o.country = 'USA';
```
### Question 7:
For the customer with customer number 124, retrieve the check number, payment date, and the number of days between the order date and the shipped date for each payment.

#### Answer:
```sql
SELECT p.checkNumber, p.paymentDate, DATEDIFF(o.shippedDate, o.orderDate) AS days_diff
FROM payments p
JOIN customers c ON p.customerNumber = c.customerNumber
JOIN orders o ON c.customerNumber = o.customerNumber
WHERE c.customerNumber = 124;
```
### Question 8:
For each product, find the number of transactions and the total quantity ordered. Only include products with more than 2500 units sold and more than 40 transactions.

#### Answer:
```sql
SELECT p.productName, COUNT(od.orderNumber) AS transaction_count, SUM(od.quantityOrdered) AS total_quantity
FROM products p
JOIN orderdetails od ON p.productCode = od.productCode
GROUP BY p.productName
HAVING total_quantity > 2500 AND transaction_count > 40;
```
### Question 9:
Find the total amount of payments made each quarter in 2003 for customers in NYC.

#### Answer:
```sql
SELECT SUM(p.amount) AS total_amount, QUARTER(p.paymentDate) AS payment_quarter
FROM payments p
JOIN customers c ON p.customerNumber = c.customerNumber
JOIN employees e ON c.salesRepEmployeeNumber = e.employeeNumber
JOIN offices o ON e.officeCode = o.officeCode
WHERE o.city = 'NYC' AND YEAR(p.paymentDate) = 2003
GROUP BY QUARTER(p.paymentDate);
```
### Question 10:
Count the number of customers assigned to each office.

#### Answer:

```sql
SELECT o.officeCode, COUNT(c.customerNumber) AS customer_count
FROM customers c
JOIN employees e ON c.salesRepEmployeeNumber = e.employeeNumber
JOIN offices o ON e.officeCode = o.officeCode
GROUP BY o.officeCode;
```