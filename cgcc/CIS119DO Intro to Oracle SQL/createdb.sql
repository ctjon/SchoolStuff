-- Sample script to create the employee database for the SQL class
-- 4 Sept 2004
-- Chris Tjon
-- Drop any of the tables that already exist

DROP TABLE countries;
DROP TABLE departments;
DROP TABLE employees;
DROP TABLE jobs;
DROP TABLE job_grades;
DROP TABLE job_history;
DROP TABLE locations;
DROP TABLE regions;
COMMIT;

  
-- Setup the Countries Table
CREATE TABLE countries
	(country_id CHAR(2) NOT NULL, 
	country_name VARCHAR2(40),
	region_id NUMBER);
DESCRIBE countries;
INSERT INTO countries VALUES ('CA','Canada','2');
INSERT INTO countries VALUES ('DE','Germany','1');
INSERT INTO countries VALUES ('UK','United Kingdom','1');
INSERT INTO countries VALUES ('US','United States of America','2');
SELECT COUNT (*) FROM countries;

-- Setup the Departments Table
CREATE TABLE departments
	(department_id NUMBER(4) NOT NULL,
	department_name VARCHAR2(30) NOT NULL,
	manager_id NUMBER(6),
	location_id NUMBER(4));
DESCRIBE departments;
INSERT INTO departments VALUES ('10','Administration','200','1700'); 
INSERT INTO departments VALUES ('20','Marketing','201','1800');
INSERT INTO departments VALUES ('50','Shipping','124','1500');
INSERT INTO departments VALUES ('60','IT','103','1400');  
INSERT INTO departments VALUES ('80','Sales','149','2500');
INSERT INTO departments VALUES ('90','Executive','100','1700');  
INSERT INTO departments VALUES ('110','Accounting','205','1700');  
INSERT INTO departments VALUES ('190','Contracting','','1700');
SELECT COUNT (*) FROM departments;

-- Setup the Employees Table
CREATE TABLE employees
	(employee_id NUMBER(6) NOT NULL,
	first_name VARCHAR2(20),
	last_name VARCHAR2(25) NOT NULL, 
	email VARCHAR2(25) NOT NULL,
	phone_number VARCHAR2(20),
	hire_date DATE NOT NULL,
	job_id VARCHAR2(10) NOT NULL,
	salary NUMBER(8,2),
	commission_pct NUMBER(2,2),
	manager_id NUMBER(6),
	department_id NUMBER(4));
DESCRIBE employees;
INSERT INTO employees VALUES ('100','Steven','King','SKING','515.123.4567','17-JUN-87','AD_PRES','24000','','','90');
INSERT INTO employees VALUES ('101','Neena','Kochhar','NKOCHHAR','515.123.4568','21-SEP-89','AD_VP','17000','','100','90');
INSERT INTO employees VALUES ('102','Lex','De Haan','LDEHAAN','515.123.4569','13-JAN-93','AD_VP','17000','','100','90');
INSERT INTO employees VALUES ('103','Alexander','Hunold','AHUNOLD','590.423.4567','03-JAN-90','IT_PROG','9000','','102','60');
INSERT INTO employees VALUES ('104','Bruce','Ernst','BERNST','590.423.4568','21-MAY-91','IT_PROG','6000','','103','60');
INSERT INTO employees VALUES ('107','Diana','Lorentz','DLORENTZ','590.423.5567','07-FEB-99','IT_PROG','4200','','103','60');
INSERT INTO employees VALUES ('124','Kevin','Mourgos','KMOURGOS','650.123.5234','16-NOV-99','ST_MAN','5800','','100','50');
INSERT INTO employees VALUES ('141','Trenna','Rajs','TRAJS','650.121.8009','17-OCT-95','ST_CLERK','3500','','124','50');
INSERT INTO employees VALUES ('142','Curtis','Davies','CDAVIES','650.121.2994','29-JAN-97','ST_CLERK','3100','','124','50');
INSERT INTO employees VALUES ('143','Randall','Matos','RMATOS','650.121.2874','15-MAR-98','ST_CLERK','2600','','124','50');
INSERT INTO employees VALUES ('144','Peter','Vargas','PVARGAS','650.121.2004','09-JUL-98','ST_CLERK','2500','','124','50');
INSERT INTO employees VALUES ('149','Eleni','Zlotkey','EZLOTKEY','011.44.1344.429018','29-JAN-00','SA_MAN','10500','.2','100','80');
INSERT INTO employees VALUES ('174','Ellen','Abel','EABEL','011.44.1644.429267','11-MAY-96','SA_REP','11000','.3','149','80');
INSERT INTO employees VALUES ('176','Jonathon','Taylor','JTAYLOR','011.44.1644.429265','24-MAR-98','SA_REP','8600','.2','149','80');
INSERT INTO employees VALUES ('178','Kimberely','Grant','KGRANT','011.44.1644.429263','24-MAY-99','SA_REP','7000','.15','149','');
INSERT INTO employees VALUES ('200','Jennifer','Whalen','JWHALEN','515.123.4444','17-SEP-87','AD_ASST','4400','','101','10');
INSERT INTO employees VALUES ('201','Michael','Hartstein','MHARTSTE','515.123.5555','17-FEB-96','MK_MAN','13000','','100','20');
INSERT INTO employees VALUES ('202','Pat','Fay','PFAY','603.123.6666','17-AUG-97','MK_REP','6000','','201','20');
INSERT INTO employees VALUES ('205','Shelley','Higgins','SHIGGINS','515.123.8080','07-JUN-94','AC_MGR','12000','','101','110');
INSERT INTO employees VALUES ('206','William','Gietz','WGIETZ','515.123.8181','07-JUN-94','AC_ACCOUNT','8300','','205','110');
SELECT COUNT (*) FROM employees;

-- Setup the Jobs Table
CREATE TABLE jobs
	(job_id VARCHAR2(10) NOT NULL,
	job_title VARCHAR2(35) NOT NULL,
	min_salary NUMBER(6),
	max_salary NUMBER(6));
DESCRIBE jobs;
INSERT INTO jobs VALUES ('AD_PRES','President','20000','40000');
INSERT INTO jobs VALUES ('AD_VP','Administration Vice President','15000','30000');
INSERT INTO jobs VALUES ('AD_ASST','Administration Assistant','3000','6000');
INSERT INTO jobs VALUES ('AC_MGR','Accounting Manager','8200','16000');
INSERT INTO jobs VALUES ('AC_ACCOUNT','Public Accountant','4200','9000');
INSERT INTO jobs VALUES ('SA_MAN','Sales Manager','10000','20000');
INSERT INTO jobs VALUES ('SA_REP','Sales Representative','6000','12000');
INSERT INTO jobs VALUES ('ST_MAN','Stock Manager','5500','8500');
INSERT INTO jobs VALUES ('ST_CLERK','Stock Clerk','2000','5000');
INSERT INTO jobs VALUES ('IT_PROG','Programmer','4000','10000');
INSERT INTO jobs VALUES ('MK_MAN','Marketing Manager','9000','15000');
INSERT INTO jobs VALUES ('MK_REP','Marketing Representative','4000','9000');
SELECT COUNT (*) FROM jobs;

CREATE TABLE job_grades
	(grade_level VARCHAR2(3),
	lowest_sal NUMBER,
	highest_sal NUMBER);
DESCRIBE job_grades;
INSERT INTO job_grades VALUES ('A','1000','2999');
INSERT INTO job_grades VALUES ('B','3000','5999');
INSERT INTO job_grades VALUES ('C','6000','9999');
INSERT INTO job_grades VALUES ('D','10000','14999');
INSERT INTO job_grades VALUES ('E','15000','24999');
INSERT INTO job_grades VALUES ('F','25000','40000');
SELECT COUNT (*) FROM job_grades;

-- Setup the Job_history Table
CREATE TABLE job_history
	(employee_id NUMBER(6) NOT NULL,
	start_date DATE NOT NULL,
	end_date DATE NOT NULL,
	job_id VARCHAR2(10) NOT NULL,
	department_id NUMBER(4));
DESCRIBE job_history;
INSERT INTO job_history VALUES ('102','13-JAN-93','24-JUL-98','IT_PROG','60');
INSERT INTO job_history VALUES ('101','21-SEP-89','27-OCT-93','AC_ACCOUNT','110');
INSERT INTO job_history VALUES ('101','28-OCT-93','15-MAR-97','AC_MGR','110');
INSERT INTO job_history VALUES ('201','17-FEB-96','19-DEC-99','MK_REP','20');
INSERT INTO job_history VALUES ('114','24-MAR-98','31-DEC-99','ST_CLERK','50');
INSERT INTO job_history VALUES ('122','01-JAN-99','31-DEC-99','ST_CLERK','50');
INSERT INTO job_history VALUES ('200','17-SEP-87','17-JUN-93','AD_ASST','90');
INSERT INTO job_history VALUES ('176','24-MAR-98','31-DEC-98','SA_REP','80');
INSERT INTO job_history VALUES ('176','01-JAN-99','31-DEC-99','SA_MAN','80');
INSERT INTO job_history VALUES ('200','01-JUL-94','31-DEC-98','AC_ACCOUNT','90');
SELECT COUNT (*) FROM job_history;

-- Setup the Locations Table
CREATE TABLE locations
	(location_id NUMBER(4) NOT NULL,
	street_address VARCHAR2(40),
	postal_code VARCHAR2(12),
	city VARCHAR2(30) NOT NULL,
	state_province VARCHAR2(25),
	country_id CHAR(2));
DESCRIBE locations;
INSERT INTO locations VALUES ('1400','2014 Jabberwocky Rd','26192','Southlake','Texas','US');
INSERT INTO locations VALUES ('1500','2011 Interiors Blvd','99236','South San Francisco','California','US');
INSERT INTO locations VALUES ('1700','2004 Charade Rd','98199','Seattle','Washington','US');
INSERT INTO locations VALUES ('1800','460 Bloor St. W.','ON M5S 1X8','Toronto','Ontario','CA');
INSERT INTO locations VALUES ('2500','Magdalen Centre, The Oxford Science Park','OX9 9ZB','Oxford','Oxford','UK');
SELECT COUNT (*) FROM locations;

-- Setup the Regions Table
CREATE TABLE regions
	(region_id NUMBER NOT NULL,
	region_name VARCHAR2(25));
DESCRIBE regions;
INSERT INTO regions VALUES ('1','Europe');
INSERT INTO regions VALUES ('2','Americas');
INSERT INTO regions VALUES ('3','Asia');
INSERT INTO regions VALUES ('4','Middle East and Africa');
SELECT COUNT (*) FROM regions;

-- Create a list of all tables
SELECT table_name FROM user_tables;

-- Commit changes to the Database;
COMMIT;
