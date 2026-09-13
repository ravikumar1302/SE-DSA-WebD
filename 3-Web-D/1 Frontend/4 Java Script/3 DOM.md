## DOM (Document Object Model) in JavaScript

1. The DOM is a programming interface that represents an HTML or XML document as a structured tree of objects.
    - Each element, attribute and piece of text in the document becomes a node in this tree, allowing programs (like JavaScript) to interact with and manipulate the content, structure and style of web pages dynamically.

2. DOM Model:

    ```
         Document (DOM)
             |
        <html>
       /      \
    <head>     <body>
      |          / | \    \
    <title>   Heading  p   <ul>
      |              |      |
     Text           Text    <li>
                                |
                              Text
    ```

    - The document is the root node of the DOM

    - Each HTML tag becomes an element node

    - Text inside tags becomes text nodes

    - Attributes (like href, id, class) become attribute nodes

    - This tree structure allows you to access and modify any part of the page

3.
