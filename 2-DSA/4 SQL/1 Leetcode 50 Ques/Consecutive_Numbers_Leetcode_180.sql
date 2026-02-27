
/*
Consecutive_Numbers_Leetcode_180

Table: Logs

+-------------+---------+
| Column Name | Type    |
+-------------+---------+
| id          | int     |
| num         | varchar |
+-------------+---------+
In SQL, id is the primary key for this table.
id is an autoincrement column.
 

Find all numbers that appear at least three times consecutively.
Return the result table in any order.

The result format is in the following example.

        Example 1:

        Input: 
        Logs table:
        +----+-----+
        | id | num |
        +----+-----+
        | 1  | 1   |
        | 2  | 1   |
        | 3  | 1   |
        | 4  | 2   |
        | 5  | 1   |
        | 6  | 2   |
        | 7  | 2   |
        +----+-----+
        Output: 
        +-----------------+
        | ConsecutiveNums |
        +-----------------+
        | 1               |
        +-----------------+
        Explanation: 1 is the only number that appears consecutively for at least three times.
        */

select distinct (a.num) as ConsecutiveNums 
from Logs a, logs b, logs c
where a.id = b.id+1 and b.id = c.id+1
and a.num=b.num and b.num =c.num;


-- Using Joins
SELECT DISTINCT t1.num AS ConsecutiveNums
FROM logs t1
JOIN logs t2 ON t1.id = t2.id - 1 AND t1.num = t2.num
JOIN logs t3 ON t2.id = t3.id - 1 AND t2.num = t3.num;


-- Some users were using 'over' in thier solutions. Read about this 'over' keyword in sql and it's use