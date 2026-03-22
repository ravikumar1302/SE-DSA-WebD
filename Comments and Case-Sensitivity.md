## Comments and Case-Sensitivity in Different Tech Stacks

| Category        | Language / Tech  | Comment Syntax                              | Case-Sensitivity                                                                                   |
| --------------- | ---------------- | ------------------------------------------- | -------------------------------------------------------------------------------------------------- |
| **Programming** | C++              | Single: `// text` <br> Multi: `/* text */`  | Sensitive (keywords lowercase, variables/functions case-sensitive)                                 |
|                 | Java             | Single: `// text` <br> Multi: `/* text */`  | Sensitive (keywords lowercase, ClassNames PascalCase)                                              |
|                 | Python           | Single: `# text` <br> Multi: `""" text """` | Sensitive (`var` ≠ `Var`; special constants like `True`, `False`, `None`)                          |
| **Front-End**   | HTML             | `<!-- text -->`                             | Case-Insensitive _(XHTML is case-sensitive)_                                                       |
|                 | Handlebars (hbs) | `{{!-- comment --}}`                        | Case-Insensitive (follows HTML behavior)                                                           |
|                 | CSS              | `/* text */`                                | Mixed: Properties insensitive, values sometimes sensitive (`red` vs `RED`)                         |
|                 | SCSS             | `// text` (not in output) <br> `/* text */` | Same as CSS                                                                                        |
|                 | JavaScript       | Single: `// text` <br> Multi: `/* text */`  | Sensitive                                                                                          |
|                 | React (JSX)      | JS: `//`, `/* */` <br> JSX: `{/* text */}`  | Sensitive (Components PascalCase, HTML tags lowercase, variables case-sensitive)                   |
| **Backend**     | Node.js          | Single: `// text` <br> Multi: `/* text */`  | Sensitive (inherits JavaScript; variables, functions, file names case-sensitive)                   |
|                 | Express.js       | Single: `// text` <br> Multi: `/* text */`  | Sensitive (inherits JavaScript; routes can be case-sensitive depending on config)                  |
| **Database**    | SQL / PL-SQL     | Single: `-- text` <br> Multi: `/* text */`  | Case-Insensitive (keywords usually uppercase; table/column sensitivity depends on DB system)       |
|                 | MongoDB          | `// text` (shell) <br> `/* text */`         | Sensitive (collection & field names case-sensitive; queries case-sensitive unless using collation) |

### Quick Notes (to remember easily)

- Most programming languages → ✅ Case-sensitive
- HTML → ❌ Case-insensitive
- CSS → ⚠️ Mixed behavior
- JavaScript ecosystem (Node.js, Express, React) → ✅ Fully case-sensitive
- SQL → ❌ Mostly case-insensitive (depends on DB)
- MongoDB → ✅ Case-sensitive by default

### Exceptions :

1. CSS selectors are generally case-insensitive, this includes class and ID selectors. So, CSS properties, values, pseudo class names, pseudo element names, element names are case INsensitive.
    - But HTML class names are case-sensitive. And CSS class, id , urls, font-families are case sensitive

2. By convention, Java programs are written entirely in lower-case characters with three exceptions :
    - The first letter of class names are capitalized to distinguish class names from member names.
    - The names of constant fields are written entirely capital letters. e.g., the built-in Java class Integer includes the constant static fields MIN_VALUE and MAX_VALUE.
    - The first letter in each word in a compound identifier after the first are capitalized. e.g., the built-in Java class Object includes a method called toString(). The capital S signifies the beginning of a word within the compound name toString().
