SELECT department_id AS "Department", COUNT(employee_id) AS "Number of People"
FROM employees
GROUP BY department_id;

SELECT d.department_name AS "Department", COUNT(e.employee_id) AS "Number of People"
FROM departments d 
FULL OUTER JOIN employees e 
ON (d.department_id = e.department_id)
GROUP BY d.department_name;

SELECT last_name, salary
FROM employees
WHERE manager_id = (SELECT employee_id FROM employees WHERE UPPER(last_name) = 'ZLOTKEY');

SELECT last_name, salary, department_id
FROM employees
WHERE department_id = (SELECT department_id FROM employees WHERE UPPER(last_name) = 'HUNOLD')
AND NVL(commission_pct,0) = (SELECT NVL(commission_pct,0) FROM employees WHERE UPPER(last_name) = 'HUNOLD');
AND UPPER(last_name) <> 'HUNOLD';

--OR--

SELECT last_name, salary, department_id
FROM employees
WHERE (department_id, NVL(commission_pct,0)) IN (SELECT department_id, NVL(commission_pct,0) FROM employees WHERE UPPER(last_name) = 'HUNOLD')
AND UPPER(last_name) <> 'HUNOLD';