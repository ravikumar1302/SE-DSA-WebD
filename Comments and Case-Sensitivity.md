## Comments and Case-Sensitivity in Different Tech Stacks

| Category        | Language / Tech  | Comment Syntax                                                       | Case-Sensitivity                                                     |
| --------------- | ---------------- | -------------------------------------------------------------------- | -------------------------------------------------------------------- |
| **Programming** | C++              | Single: `// text` <br> Multi: `/* text */`                           | Sensitive (mostly lowercase)                                         |
|                 | Java             | Single: `// text` <br> Multi: `/* text */`                           | Sensitive (keywords lowercase, but ClassNames use PascalCase)        |
|                 | Python           | Single: `# text` <br> Multi: `""" text """`                          | Sensitive (except `True`, `False`, `None`)                           |
| **Front-End**   | HTML             | `<!-- text -->`                                                      | Case In-Sensitive <br> _(XHTML is Case-Sensitive)_                   |
|                 | Handlebars (hbs) | `{{!-- comment --}}` (won’t render in HTML)                          | Case In-Sensitive (follows HTML)                                     |
|                 | CSS              | `/* text */`                                                         | Both: Properties insensitive, Values sensitive (e.g. `red` vs `RED`) |
|                 | SCSS             | Single: `// text` (removed in compiled CSS) <br> Multi: `/* text */` | Same as CSS (Both)                                                   |
|                 | JavaScript       | Single: `// text` <br> Multi: `/* text */`                           | Sensitive                                                            |
| **Database**    | SQL / PL-SQL     | Single: `-- text` <br> Multi: `/* text */`                           | Case-Insensitive (keywords usually UPPERCASE)                        |

### Exceptions :

1. CSS selectors are generally case-insensitive, this includes class and ID selectors. So, CSS properties, values, pseudo class names, pseudo element names, element names are case INsensitive.

    - But HTML class names are case-sensitive. And CSS class, id , urls, font-families are case sensitive

2. By convention, Java programs are written entirely in lower-case characters with three exceptions :
    - The first letter of class names are capitalized to distinguish class names from member names.
    - The names of constant fields are written entirely capital letters. e.g., the built-in Java class Integer includes the constant static fields MIN_VALUE and MAX_VALUE.
    - The first letter in each word in a compound identifier after the first are capitalized. e.g., the built-in Java class Object includes a method called toString(). The capital S signifies the beginning of a word within the compound name toString().
