


-- Schema will have 2 Tables
-- Student - student_id, first_name, last_name, class, Phone_no
-- Friends - Student_id, first_name, address, Phone_no
-- Insert 3 entries in each table

  create table Student (
  student_id int,
  first_name varchar(255),
  last_name varchar(255),
  class_ int,
  Phone_no int
  );
  
  create table Friends (
  student_id int,
  first_name varchar(255),
  address varchar(255),
  class_ int,
  Phone_no int
  );
  
  insert into Student values(1, 'ravi', 'bansal', 3, 00000);
  insert into Student values(2, 'rishabh', 'bhandari', 3, 00001);
  insert into Student values(3, 'shaurabh', 'patil', 3, 00003);
  
  insert into Friends values(4, 'jhony', 'kumar', 3, 00004);
  insert into Friends values(5, 'aman', 'jandiyal', 3, 00005);
  insert into Friends values(6, 'shivansh', 'gupta', 3, 00006);
  
  select * from Student;
  select * from Friends;
  
  ALTER Table Friends DROP column Phone_no;
  select count(*) from employees;
  

--pl-sql
set serveroutput on

declare
  v_fname varcahr(20);
begin
  select first_name into v_fname from employees where employee_id=100;
  dbms_output.put_line(v_fname) :
exception
  --null;
end;
/
  



-- PL-SQL basics (4 aug 2023)

set serveroutput on

declare
  v_fname varchar2(20);
begin
  select first_name into v_fname from employees where employee_id=100;
  dbms_output.put_line('The first name of employee 100 is '|| v_fname);
end;
/

declare
  v_lname varchar2(20);
begin
  select last_name into v_lname from employees where first_name='John';
  dbms_output.put_line('John last name is :'  ||  v_lname);
exception
  When too_many_rows THEN
  dbms_output.put_line('Your select statment has too many rows, use CURSOR'  ||  v_lname);
end;
/

