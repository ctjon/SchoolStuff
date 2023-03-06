--Ch 20 scripts for MultiTable inserts- PB created from combining 
--the individual scripts

DROP TABLE emp_history;
CREATE TABLE emp_history
  (employee_id    NUMBER(6) NOT NULL,
   resignation_date DATE)
   
/

insert into emp_history
  values(1, TO_DATE('13-AUG-1992', 'DD-MON-YYYY'));
insert into emp_history
  values(10,TO_DATE( '07-DEC-1997', 'DD-MON-YYYY'));
insert into emp_history
  values(20, TO_DATE( '27-NOV-1998', 'DD-MON-YYYY'));
insert into emp_history
  values(30, TO_DATE( '10-NOV-1996', 'DD-MON-YYYY'));
 
COMMIT;

DROP TABLE hiredate_history;
CREATE TABLE hiredate_history
(DEPARTMENT_ID	NUMBER(4),
HIREDATE	DATE);

DROP TABLE hiredate_history_00;
CREATE TABLE hiredate_history_00
(DEPARTMENT_ID	NUMBER(4),
HIREDATE	DATE);

DROP TABLE hiredate_history_99;
CREATE TABLE hiredate_history_99
(DEPARTMENT_ID	NUMBER(4),
HIREDATE	DATE);

DROP TABLE MGR_HISTORY;
CREATE table MGR_HISTORY
(EMPLOYEE_ID	NUMBER(6),
MANAGER_ID	NUMBER(6),
SALARY	NUMBER(8,2));

DROP TABLE REWARDS;
CREATE TABLE rewards
  (employee_id    NUMBER(6) NOT NULL,
   pay_raise NUMBER(8,2),
   payraise_date DATE NOT NULL
   )
/

insert into rewards
  values(103, 10000, TO_DATE('13-AUG-1992', 'DD-MON-YYYY'));
insert into rewards
  values(141, 2500,TO_DATE( '07-DEC-1997', 'DD-MON-YYYY'));
insert into rewards
  values(201, 4875, TO_DATE( '27-NOV-1998', 'DD-MON-YYYY'));
insert into rewards
  values(206, 1800, TO_DATE( '10-NOV-1996', 'DD-MON-YYYY'));
 
COMMIT;

DROP TABLE SAL_HISTORY;
CREATE table SAL_HISTORY
(EMPLOYEE_ID	NUMBER(6),
HIRE_DATE	DATE,
SALARY	NUMBER(8,2));

drop TABLE SALES_INFO;
CREATE TABLE SALES_INFO
(employee_id 	NUMBER(6),
WEEK	NUMBER(2),
SALES	NUMBER(8,2));

drop TABLE SALES_SOURCE_DATA;
CREATE TABLE SALES_SOURCE_DATA
(employee_id 	NUMBER(6),
WEEK_ID	NUMBER(2),
SALES_MON	NUMBER(8,2),
SALES_TUE	NUMBER(8,2),
SALES_WED	NUMBER(8,2),
SALES_THUR	NUMBER(8,2),
SALES_FRI	NUMBER(8,2));

drop TABLE SPECIAL_SAL;
CREATE table SPECIAL_SAL
(EMPLOYEE_ID	NUMBER(6),
SALARY	NUMBER(8,2));


INSERT INTO SALES_SOURCE_DATA VALUES
(178, 6, 1750,2200,1500,1500,3000);
commit;


INSERT INTO SALES_SOURCE_DATA VALUES
(176, 6, 2000,3000,4000,5000,6000);
commit;