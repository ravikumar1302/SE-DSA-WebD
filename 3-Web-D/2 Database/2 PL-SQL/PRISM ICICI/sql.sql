
-- In Dheeraj Triphati sir

select last_name, salary from employees where salary between 8000 and 12000;

select * from employees;

select employee_id, last_name, salary, salary+300 as sal_with_bonus from employees;

select employee_id, last_name, salary, salary+300 sal_with_bonus from employees;

select employee_id, last_name, salary,commission_pct, COALESCE((salary + salary*commission_pct)*12, salary*12) annual_sal_with_commision from employees;
select employee_id, last_name, salary,nvl(commission_pct,0), (salary + salary*nvl(commission_pct,0))*12  from employees;
-- The above two lines gives same output, we are dealing with null values here, in 2nd one we are converting null to 0



select employee_id, last_name, salary from employees where manager_id IN (100, 101, 201);

select employee_id, last_name, hire_date, salary from employees where EXTRACT (YEAR from hire_date) > 2006 ;
select employee_id, last_name, hire_date, salary from employees where hire_date > '31-Dec-06' ;
-- The above two output are same


select employee_id, first_name, last_name, hire_date, salary from employees where first_name like 'S%';
select employee_id, first_name from employees where first_name like '_s%';

select employee_id, last_name, job_id from employees where job_id NOT IN ('IT_PROG', 'ST_CLERK', 'SA_REP');


select employee_id, last_name, hire_date, salary from employees where hire_date > '31-Dec-06' ORDER BY hire_date;

-- substitution variable
select last_name, salary from employees where employee_id = &x;
select employee_id, last_name, &a from employees WHERE &b ORDER BY &c;


-- functions
    -- LOWER, UPPER functions with || or CONCAT operator
        select 'The job id of ' || UPPER(first_name) || ' is ' || LOWER(job_id) from employees;
    
    -- TRUNC/ ROUND
        select round(45.926, 1), round(44.926, -1) from dual;
        select round(45.926, 1), trunc(44.926, -1) from dual;

-- sysdate 
  select last_name, hire_date, TRUNC((SYSDATE - hire_date)/7,0) as weeks from employees;
  
-- Display the employee_id, hire date, number of months employed, Six-month Confirmation date, first Friday after hire date, and the last day of the hire month for all employees who have been employed for less than 300 Months…
  
  select employee_id, hire_date, months_between(sysdate, hire_date) as tenure, add_months(hire_date, 6) CONFIRMATION_DATE, next_day(hire_date, 'friday'), last_day(hire_date)
  from employees where months_between(sysdate,hire_date) < 300;

-- Some more date formats
    select employee_id, last_name, to_char(hire_date, 'MM/YY') as hiredate from employees;
    select employee_id, last_name, to_char(hire_date, 'DD Month YYYY') as hiredate from employees;
    
    select employee_id, last_name, to_char(salary, '$99,999.00') as salary from employees;

-- Some nval functions
    select last_name, salary, commission_pct, (salary + nvl2(commission_pct, commission_pct*salary,0) ) as source from employees;

-- CASE     
    select last_name, job_id, salary, 
    CASE job_id
      WHEN 'IT_PROG' THEN salary*1.1
      WHEN 'ST_CLERK' THEN salary*1.15
      WHEN 'SA_REP' THEN salary*1.2
      ELSE salary
    END as revised_salary
    from employees;


-- Some group functions - AVG, SUM, MAX, MIN
    select sum(commission_pct)/107  from employees;     -- it is divied by 107 because these functions ignore null value
    select avg(nvl(commission_pct,0)) from employees;    -- It is same as above

    select min(hire_date) from employees; 
    select avg(salary), job_id from employees  group by job_id; 


-- JOINS
    select e.last_name, d.department_name, l.city  from (employees e join department d) 
    ON (e.department_id = d.department_id) join locations l on  (d.location_id = l.location_id);
  
  
-- Assignment on 2 aug 2023

 -- 1
    DESC departments;
--2
    select unique(job_id) from employees;

-- 3
    select (last_name || ' , ' || job_id) as "Employee and Title" from employees;

--4
  select last_name, salary from employees where salary > 12000;

--5
  select last_name, job_id, hire_date from employees 
  where last_name IN ('Matos','Taylor') ORDER BY hire_date;

--6
  select last_name, salary from employees 
  where salary > &x;


--7
    select last_name, job_id, salary from employees 
    where job_id IN ('ST_CLERK', 'SA_REP') and salary NOT IN (2500, 3500, 7000) ;


--8
    select CONCAT(UPPER(SUBSTR(last_name,1,1)), LOWER(SUBSTR(last_name, 2))) as 'LAST_NAME', 
    LENGTH(last_name) 'NAME LENGTH' from employees 
    where last_name LIKE 'J%' OR last_name LIKE 'A%' last_name LIKE 'M%'  
    ORDER BY last_name ;

--8    
    select initcap(last_name), LENGTH(last_name) from employees 
    where first_name LIKE 'J%' OR first_name LIKE 'A%' OR first_name LIKE 'M%'  
    ORDER BY last_name;
    

--9
    select max(salary) as MAXIMUM, min(salary) as Minimu_m,
    sum(salary) as Su_m, ROUND(avg(salary)) as AVERAGE from employees;

--10
    select e.last_name, e.job_id, e.department_id, d.department_name
    from employees e join departments d 
    ON (e.department_id=d.department_id)
    join locations l
    ON (d.location_id = l.location_id)
    where city='Toronto';


-- 3 Aug 2023 (Normal class)
    select * from employees;
    
    alter user hr as ravi;
    update user $ set name ='ravi';
    alter user ravi identified by icicib3;
    
    
    
    
    
    
    
    
