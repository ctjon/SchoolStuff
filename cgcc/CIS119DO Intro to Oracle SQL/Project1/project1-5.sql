DESCRIBE employees;
SELECT count(last_name)
FROM employees
WHERE last_name LIKE '%n'
