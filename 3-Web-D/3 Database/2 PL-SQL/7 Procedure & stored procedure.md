# Procedure & stored procedure

- PL/SQL stored procedure is a subprogram that performs a particular task to avoid repeated task to be done manually, these subprograms are combined to form a larger programs
- it is a block which performs one or more specific tasks. Procedure contains header and body.
- **Header** : contains name and parameters or variables passed to Procedure
- **Body** : contains a declaration, execution & exception section similar to general PL-SQL block
- 3 ways to pass parameters : `IN`, `OUT` & `INOUT` parameters
- Procedure may or may not return any value
- E.g., `CREATE TABLE user (id number(10) primary key, name varchar2(100));`

    ```sql
    -- Procedure code :
    CREATE or REPLACE PROCEDURE "insertuser" (id IN NUMBMER, name IN VARCHAR2)
    IS      -- IS or AS : 2 ways
    BEGIN
        INSERT INTO user VALUES (id, name);
    END ;
    /
    -- To call above Procedure
    BEGIN
        insertuser(101, 'Rahul');
        dbms_output.put_line('record inserted successfully');
    END;
    /
    ```

    - Now you can call the procedure using : `EXECUTE insertuser` OR using : `BEGIN insertuser END; /`
