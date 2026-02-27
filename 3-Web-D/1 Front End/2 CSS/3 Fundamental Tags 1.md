# Basic/ Fundamental Tags

1. CSS is written as a rule set, which consists of a selector and a declaration block. The basic syntax of CSS is as follows:
    - The selector is a targeted HTML element or elements to which we have to apply styling.
    - The Declaration Block or " { } " is a block in which we write our CSS.

## Selectors in CSS

1. Universal Selector: Applies styles to all elements.

    ```
    * {
    margin: 0;
    padding: 0;
    }
    ```

2. Type Selector: Targets specific HTML elements.

    ```
    h1 { font-family: Arial, sans-serif;}
    ```

3. Class Selector: Styles elements with a specific class attribute.

    ```
    .box {
    border: 1px solid black;
    padding: 10px;
    }
    ```

4. ID Selector: Targets a single element with a specific ID.
    ```
    #header {
    background-color: lightgray;
    }
    ```

## Grouping and Nesting of CSS Selectors

You can group selectors to apply the same styles or nest them for hierarchical targeting.

1. Grouping

    ```
    h1, h2, h3 {
        color: darkblue;
    }
    ```

2. Nesting
    ```
    ul li {
        list-style-type: square;
    }
    ```

## Pseudo-classes and Pseudo-elements

-   Pseudo-classes and pseudo-elements are used for styling specific states or parts of elements.
-   Pseudo classes target's the elements based on a particular state and pseudo elements targets the elements on basis of a particular part of that element.

    ```
    /*pseudo-class selector*/
    a:hover {
        color: green;
    }

    /*pseudo-element selector*/
    p::first-line {
        font-weight: bold;
    }
    ```
