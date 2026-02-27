# SCSS (Sassy CSS)

-   **SCSS = Sassy CSS** – It’s a superset of CSS, offering extra features while remaining fully compatible with standard CSS.
-   File extension : `.scss`
-   SCSS is a syntax of SASS, which is a CSS preprocessor — it adds programming-like features to CSS:

-   Variables : Allows defining reusable values (like colors, fonts, sizes) with `$variable-name`
    ```
    $primary-color: #3498db;
    body { color: $primary-color; }
    ```
-   Nesting

    ```
    .nav {
        ul {
            li {
            a { color: red;  }
            }
        } }
    ```

-   **Features** – Supports mixins, inheritance, functions, loops and operators for modular and DRY (Don’t Repeat Yourself) code
-   But remember: SCSS compiles down to regular CSS, which browsers understand.

Summary Table
| Technology | Type | Purpose |
| ---------- | ---------------- | ------------------------------------------- |
| CSS | Styling language | Base language for styling |
| CSS3 | Version of CSS | Adds modern layout and effects |
| SCSS | CSS preprocessor | Adds logic, nesting, and reusability to CSS |

-   If you're working on larger or modular front-end projects, SCSS is very useful. But to work in SCSS, you need a build tool (like Webpack, Gulp, or AEM’s clientlibs processor) to compile it to CSS.
