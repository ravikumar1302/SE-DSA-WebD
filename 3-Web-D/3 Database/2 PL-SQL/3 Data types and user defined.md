# Data Types and User-Defined Subtypes

- Data Types :

    - **Scalar** : Single values with no internal components such as a NUMBER, DATE or BOOLEAN
        - **Numeric** : for arithmetic operations
            - `PLS_INTEGER`, `BINARY_INTEGER`, `BINARY_FLOAT`, `INT`, `FLOAT`, `REAL`, `SMALLINT` etc
        - **Character** : Alphanumeric values of single or string of characters
            - `CHAR`, `VARCHAR2`, `RAAWA`, `NCHAR`, `NVARCHAR2`, `LONG`, `LONGRAW` etc
        - **Boolean** : Logical values (True/False)
        - **Datetime** : Dates and Times

    - **Large OBject (LOB)** : Pointers to large objects that are stored separately from other data items, such as text, graphic images, video clips and sound waveforms
    - **Composite** : Data items that have internal components that can be accessed individually, e.g., collections and records
    - **Reference** : Pointers to other data items
    - PL-SQL don't allow multiple variable declarations in one line, declare each one of them in different line

---

- User-Defined Subtypes :

    - Subtype is a subset of another data type, which is called its base type
    - PL-SQL predefines several subtypes in package STANDARD
    - E.g., it predefines subtype CHARACTER & INTEGER as follows :

        ```sql
        DECLARE
            SUBTYPE name IS char(20);
            SUBTYPE msg IS varchar2(100);
            salutation name;
            greetings msg;
        BEGIN
            salutation :='Reader';
            greetings := 'Har har mahadev';
            dbms_output.put_line('Hello' || salutaion || greetings);    -- here || means appending or adding
        END;
        /
        ```
