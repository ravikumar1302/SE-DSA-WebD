BASIC Points :

1. Adding Js code
    - Inside HTML code : Edit the HTML file by adding a `<script> </script>` tag, inside `<head>` tag, and write Js code
        ```html
        <!DOCTYPE html>
        <html>
            <head>
            <title> JavaScript Test Site </title>
            <script>
                alert("Hello, World!");
            </script>
            </head>
        <body> ... </body>
        </html>
        ```
    - In a separate file (.js file) :
        ```html
        <!DOCTYPE html>
        <html>
        <head>
        <title> JavaScript Test Site </title>
        <script src="first.js">   </script>
        </head>
        <body> ... </body>
        </html>
        ```
        ```js
        // In JavaScript file called first.js

        alert('Coming to you from first.js!');
        ```

2. Camel Case : the standard is to capitalize each word after the first word
    ```js
    let firstName = "Matt";
    let lastName = "Lane";
    let fullName = firstName + " " + lastName;
    ```
    These examples also illustrate a common convention when writing JavaScript: when declaring variables using multiple words, the standard is to capitalize each word after the first word, and otherwise use lower-case letters (e.g. firstName, NOT firstname, first_name, FirstName, or some other variation).
    This casing convention is called camel case, and while your JavaScript code will work just fine if you don't abide by this convention, it's good to get in the habit of camel casing your variables.

3. Js is used both in frontend and backend
4. In a car, HTML is structure/ metallic body. CSS is color/ designs. Js is brain/engine
5. JS is a high-level dynamic interpreted programming language, that allows client-side scripting to create completely dynamic web applications and websites.
