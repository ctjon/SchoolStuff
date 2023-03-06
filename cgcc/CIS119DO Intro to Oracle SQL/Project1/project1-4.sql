DESCRIBE employees;
DESCRIBE jobs;
SELECT j.job_id AS "Job", SUM(e.salary) AS "Payroll"
FROM jobs j
JOIN employees e
ON e.job_id = j.job_id
GROUP BY j.job_id
ORDER BY "Payroll";
