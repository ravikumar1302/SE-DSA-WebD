
/*
Managers_with_at_Least_5_Direct_Reports_Leetcode_570

Table: Employee

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| id          | int     |
| name        | varchar |
| department  | varchar |
| managerId   | int     |
+-------------+---------+
id is the primary key (column with unique values) for this table.
Each row of this table indicates the name of an employee, their department, and the id of their manager.
If managerId is null, then the employee does not have a manager.
No employee will be the manager of themself.
 

Write a solution to find managers with at least five direct reports.
Return the result table in any order.
The result format is in the following example.

 
        Example 1:

        Input: 
        Employee table:
        +-----+-------+------------+-----------+
        | id  | name  | department | managerId |
        +-----+-------+------------+-----------+
        | 101 | John  | A          | None      |
        | 102 | Dan   | A          | 101       |
        | 103 | James | A          | 101       |
        | 104 | Amy   | A          | 101       |
        | 105 | Anne  | A          | 101       |
        | 106 | Ron   | B          | 101       |
        +-----+-------+------------+-----------+
        Output: 
        +------+
        | name |
        +------+
        | John |
        +------+

*/

select b.name 
from Employee as a inner join Employee as b
where a.managerId = b.ID
group by a.managerId
having count(*) >=5;


-- Another poosible solution, using subqueries
select name 
from employee 
where id in
(select managerId from employee 
group by managerId
having (count(distinct id)>=5));
