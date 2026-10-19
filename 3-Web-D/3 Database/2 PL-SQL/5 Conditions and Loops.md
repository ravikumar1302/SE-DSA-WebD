# Conditions and Loops

- PL-SQL Conditions : (It is also called controlled structures)

    - **IF-THEN** :

        ```sql
        IF (a<=20) THEN     -- all these conditions are written inside BEGIN
            c := c+1;       -- Write either expressions or SQL statements
        END IF;
        ```

    - **IF-THEN-ELSE** :

        ```sql
        IF (a<=20) THEN
            c := c+1;
        ELSE
            c := c+2;
        END IF;
        ```

    - **IF-THEN-ELSEIF** :

        ```sql
        IF (a<=20) THEN
            c := c+1;
        ELSEIF (a=20) THEN
            c := c+3;
        ELSE
            c := c+2;
        END IF;
        ```

    - **CASE** :

        ```sql
        DECLARE
            var char(1) := 'A';
        BEGIN
            CASE var
                when 'A' then dbms_output.put_line('Excellent');
                when 'B' then dbms_output.put_line('Very Good');
                when 'c' then dbms_output.put_line('Well Done');
                when 'D' then dbms_output.put_line('You Passed');
                else dbms_output.put_line('Failed');        -- default case
            END CASE;
        END
        ```

    - **Searched CASE** : there is selector in each case

        ```sql
        DECLARE
            var char(1) := 'A';
        BEGIN
            CASE var
                when var = 'A' then dbms_output.put_line('Excellent');
                when var = 'B' then dbms_output.put_line('Very Good');
                when var = 'c' then dbms_output.put_line('Well Done');
                when var = 'D' then dbms_output.put_line('You Passed');
                else dbms_output.put_line('Failed');        -- default case
            END CASE;
        END
        ```

    - **nested IF-THEN-ELSE** :

---

- Loops : Basic, While and For loop

    - **Basic LOOP** : made using if-then

        ```sql
        DECLARE
            var number := 10;
        BEGIN
            Loop
                x := x+10;
                -- statements
                EXIT WHEN (x > 50);     -- we can also write :  IF x>50 THEN EXIT;  END IF;
            END LOOP;
        END
        ```

    - **WHILE LOOP** :

        ```sql
        DECLARE
            var number := 10;
        BEGIN
            WHILE a< 20 LOOP
                a := a+2;
            END LOOP;
        END
        ```

    - **FOR LOOP** :

        ```sql
        DECLARE
            var number := 10;
        BEGIN
            FOR a in 10 .. 20 LOOP      -- FOR a in REVERSE 10 .. 20 LOOP
                a := a+2;
            END LOOP;
        END
        ```

        - Use `REVERSE` keyword if you want value in reverse

    - **Nested loops** :

    - Loop Control statements : `EXIT`, `CONTINUE`, `GOTO`
