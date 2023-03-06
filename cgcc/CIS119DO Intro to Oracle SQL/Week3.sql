SELECT sysdate as Today 
FROM dual;

SELECT last_name, commission_pct 
FROM employees 
WHERE commission_pct IS NULL;

SELECT last_name, first_name 
FROM employees 
WHERE last_name LIKE '%s' AND first_name BETWEEN 'P' AND 'U' 
ORDER BY last_name asc;

SELECT department_id, LOWER(first_name)
FROM employees 
ORDER BY department_id, first_name;

SELECT last_name, first_name, job_id 
FROM employees 
ORDER by 3;

SELECT sysdate, NEXT_DAY(sysdate, 'FRIDAY') 
FROM DUAL;

SELECT last_name, TO_CHAR(hire_date, 'MON YY') AS "Hire Date"
FROM employees;

SELECT last_name, TO_CHAR(hire_date, 'MONTH YYYY') AS "Hire Date"
FROM employees;

SELECT last_name, TO_CHAR(hire_date, 'Month YYYY') AS "Hire Date"
FROM employees;

SELECT last_name, TO_CHAR(hire_date, 'Month Year') AS "Hire Date"
FROM employees;

SELECT TO_CHAR(sysdate, 'Month DD YYYY    HH:MM:SS')
FROM DUAL;

SELECT TO_CHAR(sysdate, 'Ddspth "of" Month YYYY    HH:MM:SS')
FROM DUAL;

SELECT TO_CHAR(salary, '$99,999.99')
FROM employees;

SELECT TO_CHAR(salary, '$099,999.99')
FROM employees;

SELECT last_name, hire_date
FROM employees
WHERE hire_date < '01-JAN-90';

SELECT last_name, hire_date
FROM employees
WHERE hire_date < TO_DATE('01-JAN-90', 'DD-MON-RR');

SELECT last_name, hire_date
FROM employees
WHERE hire_date < TO_DATE('01-JAN-90', 'DD-MON-YY');

SELECT last_name, salary, NVL(commission_pct,0), (salary * 12) + (salary * 12 * NVL(commission_pct, 0)) AS AN_SAL
FROM employees;

SELECT last_name, salary, commission_pct, NVL2(commission_pct, 'SAL+COM', 'SAL') AS income
FROM employees;

SELECT first_name, LENGTH(first_name) AS "expr1",
       last_name, LENGTH(last_name) AS "expr2",
       NULLIF (LENGTH(first_name), LENGTH(last_name)) AS result
FROM employees;

SELECT last_name,
       COALESCE(commission_pct, salary, 10) AS comm
FROM employees
ORDER BY commission_pct;

SELECT last_name, job_id, salary,
       CASE job_id WHEN 'IT_PROG' THEN 1.10*salary
                   WHEN 'ST_CLERK' THEN 1.15*salary
                   WHEN 'SA_REP' THEN 1.20*salary
ELSE salary END as "Revised Salary"
FROM employees;

-- ORACLE Syntax
-- Simple, Equijoin, Inner Join Example --
SELECT employees.employee_id, employees.department_id, departments.department_name 
FROM employees, departments
WHERE employees.department_id = departments.department_id;

SELECT e.employee_id, e.department_id, d.department_name
FROM employees e, departments d
WHERE e.department_id = d.department_id;

SELECT e.employee_id, e.department_id, d.department_name
FROM employees e, departments d
WHERE e.department_id = d.department_id
AND e.job_id LIKE '%S%';

-- Multiple Join --
SELECT e.employee_id, d.department_id, d.department_name, l.city
FROM employees e, departments d, locations l
WHERE e.department_id = d.department_id 
AND d.location_id = l.location_id;
-- for n tables, you need (n-1) join conditions

-- Non-Equijoin Example --
SELECT e.last_name, e.salary, j.highest_sal
FROM employees e, job_grades j
WHERE e.salary >j.highest_sal
AND j.grade_level > 'B';

-- Outer Join Example (shows employee who does not have a deptartment_id
SELECT e.employee_id, e.department_id, d.department_name
FROM employees e, departments d
WHERE e.department_id = d.department_id(+); -- ORACLE SYNTAX!!!!

-- Self Join Example
SELECT e.employee_id, e.last_name, e.manager_id, m.last_name
FROM employees e, employees m
WHERE e.manager_id = m.employee_id;

-- NOW ANSI 99 Syntax
SELECT e.employee_id, e.department_id, d.department_name 
FROM employees e JOIN departments d
ON (e.department_id = d.department_id);

SELECT e.employee_id, e.department_id, d.department_name 
FROM employees e LEFT OUTER JOIN departments d
ON (e.department_id = d.department_id);

SELECT e.employee_id, e.department_id, d.department_name 
FROM employees e RIGHT OUTER JOIN departments d
ON (e.department_id = d.department_id);

SELECT e.employee_id, e.department_id, d.department_name 
FROM employees e FULL OUTER JOIN departments d
ON (e.department_id = d.department_id);

-- Cartesian Product in ANSI 99 Standard	
SELECT e.employee_id, e.department_id, d.department_name 
FROM employees e CROSS JOIN departments d;

-- Natural Join (Not Recommended)
SELECT employee_id, department_id, department_name 
FROM employees NATURAL JOIN departments;