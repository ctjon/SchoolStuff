--SHOWS USAGE OF CHARATER MANIPULATION FUNCTION - UPPER

SELECT employee_id, last_name, department_id
FROM employees
WHERE UPPER(last_name) = 'HIGGINS';

--SHOWS USAGE OF CHARATER MANIPULATION FUNCTION - LOWER

SELECT employee_id, last_name, department_id
FROM employees
WHERE LOWER(last_name) = 'higgins';

--SHOWS USAGE OF THE SUBSTR COMMAND

select first_name || last_name, JOB_ID 
FROM employees
WHERE SUBSTR (job_id, 4) = 'REP';

--PRACTICE QUESTION #1 - Display SYSTEM DATE

SELECT SYSDATE
FROM DUAL;

--PRACTICE QUESTION #2

SELECT employee_id, last_name, salary, salary * 1.15 AS "New Salary"
FROM employees

--PRACTICE QUESTION #3

SELECT employee_id, last_name, salary, TRUNC(salary * 1.15) AS "NEW SALARY", (TRUNC(salary * 1.15) - salary) AS Increase
FROM employees;