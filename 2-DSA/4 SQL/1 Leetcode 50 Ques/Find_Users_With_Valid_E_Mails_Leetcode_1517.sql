
/*

Find_Users_With_Valid_E_Mails_Leetcode_1517

Table: Users

+---------------+---------+
| Column Name   | Type    |
+---------------+---------+
| user_id       | int     |
| name          | varchar |
| mail          | varchar |
+---------------+---------+
user_id is the primary key (column with unique values) for this table.
This table contains information of the users signed up in a website. Some e-mails are invalid.
 

Write a solution to find the users who have valid emails.

A valid e-mail has a prefix name and a domain where:

The prefix name is a string that may contain letters (upper or lower case), digits, underscore '_', period '.', and/or dash '-'. The prefix name must start with a letter.
The domain is '@leetcode.com'.
Return the result table in any order.

The result format is in the following example.

        Example 1:

        Input: 
        Users table:
        +---------+-----------+-------------------------+
        | user_id | name      | mail                    |
        +---------+-----------+-------------------------+
        | 1       | Winston   | winston@leetcode.com    |
        | 2       | Jonathan  | jonathanisgreat         |
        | 3       | Annabelle | bella-@leetcode.com     |
        | 4       | Sally     | sally.come@leetcode.com |
        | 5       | Marwan    | quarz#2020@leetcode.com |
        | 6       | David     | david69@gmail.com       |
        | 7       | Shapiro   | .shapo@leetcode.com     |
        +---------+-----------+-------------------------+
        Output: 
        +---------+-----------+-------------------------+
        | user_id | name      | mail                    |
        +---------+-----------+-------------------------+
        | 1       | Winston   | winston@leetcode.com    |
        | 3       | Annabelle | bella-@leetcode.com     |
        | 4       | Sally     | sally.come@leetcode.com |
        +---------+-----------+-------------------------+
        Explanation: 
        The mail of user 2 does not have a domain.
        The mail of user 5 has the # sign which is not allowed.
        The mail of user 6 does not have the leetcode domain.
        The mail of user 7 starts with a period.

*/

select 
user_id, name, mail
from Users
where mail regexp '^[a-zA-Z][a-zA-Z0-9_.-]*@leetcode[.]com$';


-- Approach
The regular expression may be broken down in chunks and explained as follows (refer to the documentation immediately below if needed):

- ^[a-zA-Z] : The email must start with an alphanumeric letter (i.e., not digit). [Ref: D2, D5a]
-  [a-zA-Z0-9_.-]* : 
    The next zero or more characters must be either alphanumeric (letters a-z, A-Z, or digits 0-9) [Ref: D4, D5a]
    or a _ or . [Ref: D5b]
    or a - [Ref: D5c]
- @leetcode[.]com$: + @leetcode: The next sequence of characters must exactly match @leetcode + [.]: The . character within a [] pair does not have special meaning so it must be matched exactly after @leetcode. [Ref: D5c] + com$: The string must end with com. [Ref: D3]


-- Documentation : The following documentation is largely from the MySQL docs on regular expressions.

(D1) REGEXP: expr REGEXP pat: Returns 1 if the string expr matches the regular expression specified by the pattern pat, 0 otherwise. If expr or pat is NULL, the return value is NULL. REGEXP and RLIKE are synonyms for REGEXP_LIKE().

(D2) ^: Match the beginning of a string with ^:
    mysql> SELECT REGEXP_LIKE('fo\nfo', '^fo$');                   -> 0
    mysql> SELECT REGEXP_LIKE('fofo', '^fo');                      -> 1

(D3) $: Match the end of a string with $:
    mysql> SELECT REGEXP_LIKE('fo\no', '^fo\no$');                 -> 1
    mysql> SELECT REGEXP_LIKE('fo\no', '^fo$');                    -> 0

(D4) *: Match any sequence of zero or more a characters.
    mysql> SELECT REGEXP_LIKE('Ban', '^Ba*n');                     -> 1
    mysql> SELECT REGEXP_LIKE('Baaan', '^Ba*n');                   -> 1
    mysql> SELECT REGEXP_LIKE('Bn', '^Ba*n');                      -> 1

(D5) [a-dX], [^a-dX]: Matches any character that is (or is not, if ^ is used) either a, b, c, d or X. A - character between two other characters forms a range that matches all characters from the first character to the second. For example, [0-9] matches any decimal digit. To include a literal ] character, it must immediately follow the opening bracket [. To include a literal - character, it must be written first or last. Any character that does not have a defined special meaning inside a [] pair matches only itself.
    mysql> SELECT REGEXP_LIKE('aXbc', '[a-dXYZ]');                 -> 1
    mysql> SELECT REGEXP_LIKE('aXbc', '^[a-dXYZ]$');               -> 0
    mysql> SELECT REGEXP_LIKE('aXbc', '^[a-dXYZ]+$');              -> 1
    mysql> SELECT REGEXP_LIKE('aXbc', '^[^a-dXYZ]+$');             -> 0
    mysql> SELECT REGEXP_LIKE('gheis', '^[^a-dXYZ]+$');            -> 1
    mysql> SELECT REGEXP_LIKE('gheisa', '^[^a-dXYZ]+$');           -> 0
    
(D5a): Character sets [a-z] and [A-Z] behave as expected, and we can combine ranges in character classes as follows: [a-zA-Z0-9].

(D5b): Note the part about including a literal dash -: "To include a literal - character, it must be written first or last. Any character that does not have a defined special meaning inside a [] pair matches only itself."

(D5c): The characters _ and ., when enclosed within a [] pair, do not have special meaning.
