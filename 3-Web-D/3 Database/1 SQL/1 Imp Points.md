BASIC Points :

- SQL was developed in 1970 by Donald Chamberlin & Raymond Boyce
- file Extension : `file_name.sql`
    - In general, the file extensions that we use for SQL Server data files are MDF (Primary Data File), NDF (Secondary Data File - this is optional) and LDF (Transaction Log File)
    - SQL Server works fine with any file extension but Microsoft recommends we use MDF, NDF and LDF

1. Different SQL IDE are : MySQL, Oracle Database, PostgreSQL, Microsoft SQL Server, SQLite, IBM DB2 and all these follow ANSI Standard
2. SQL is standardized by ANSI (American National Standard Institute) in 1986.
    SEQUEL : Structured English Query Language (It is initially known as this)
    SQL : Structured Query Language
3. SQL is not case-sensitive language. But it is preferred to write keyword in UPPER-CASE and objects we are referring to like table are taken in LOWER-CASE
    Also, Variable names are also not case-sensitive. Name == name == NAME in SQL
4. Every command in SQL ends with semi-colon (`;`)
5. Execute (All or Selection) -> `Ctrl + Shift + Enter`
    Execute Current Statement -> `Ctrl + Enter`
6. Single (`''`) and double (`" "`) both quotes are allowed in SQL for string, but single quote is preferred
7. Using SQL in Your Web Site : To build a web site that shows data from a database, you will need
    - An RDBMS database program (i.e. MS Access, SQL Server, MySQL)
    - To use a server-side scripting language, like PHP or ASP
    - To use SQL to get the data you want
    - To use HTML / CSS to style the page
8. INSERT INTO : It is possible to write the INSERT INTO statement in two ways:
    - Specify both the column names and the values to be inserted: `INSERT INTO table_name (column1, column2, column3, ...) VALUES (value1, value2, value3, ...);`
    - If you are adding values for all the columns of the table, you do not need to specify the column names in the SQL query. However, make sure the order of the values is in the same order as the columns in the table
        `INSERT INTO table_name VALUES (value1, value2, value3, ...);`
9. While using UPDATE, DELETE, The WHERE clause specifies which record(s) should be modified. If you omit the WHERE clause, all records in the table will be modified
