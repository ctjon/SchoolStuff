DESCRIBE employees;
DESCRIBE departments;
--SELECT * from employees;
--SELECT * from departments;
SELECT d.department_name, e.last_name, e.salary
FROM departments d
JOIN employees e
ON e.department_id = d.department_id
WHERE UPPER(d.department_name) = UPPER('Shipping')
ORDER BY e.last_name;