Describe Employees;
SELECT * from employees;
SELECT last_name, job_id AS "JOB" 
FROM employees
WHERE INITCAP(last_name) = ANY(INITCAP('HUNOLD'),INITCAP('LORENTZ'),INITCAP('WHALEN'))
AND INITCAP(job_id) = ANY(INITCAP('IT_PROG'),INITCAP('ST_CLERK'),INITCAP('MK_MAN'))
AND salary > 5000;