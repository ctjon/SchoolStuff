SET VERIFY OFF;
SET ECHO ON;

SELECT employee_id, last_name, department_id 
FROM employees
WHERE department_id = &p_dept_id;

SELECT employee_id, last_name, department_id 
FROM employees
WHERE job_id = UPPER('&p_job_id');

SELECT employee_id, last_name, &column_name 
FROM employees;

SELECT employee_id, last_name, &column_name 
FROM employees
WHERE &condition;

SELECT employee_id, last_name, &&column_name 
FROM employees
ORDER BY &column_name;

DEFINE;
DEFINE &column_name = salary;
UNDEFINE &column_name;