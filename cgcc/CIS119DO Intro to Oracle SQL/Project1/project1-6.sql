DESCRIBE employees;
SELECT last_name, hire_date
FROM employees
WHERE TO_CHAR(hire_date, 'DD') < '16'
ORDER BY hire_date desc;