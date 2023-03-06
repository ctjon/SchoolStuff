DESCRIBE employees;
--SELECT * from employees;
SELECT 'My name is ' || last_name as "Name"
FROM employees
WHERE UPPER(last_name) > 'I' AND UPPER(last_name) < 'N'
ORDER BY last_name;
