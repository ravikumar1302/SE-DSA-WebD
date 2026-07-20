# Practical uses of JS

1. JS can change HTML Content

    - `getElementById()` : document.getElementById("demo").innerHTML = "Hello JavaScript";

2. JS can change HTML Attribute Values

    ```
        <button onclick="document.getElementById('myImage').src='pic_bulbon.gif'">Turn on the light</button>
        <img id="myImage" src="pic_bulboff.gif" style="width:100px">
        <button onclick="document.getElementById('myImage').src='pic_bulboff.gif'">Turn off the light</button>
    ```

3. JS can change HTML Styles (CSS)

    - document.getElementById("demo").style.fontSize = "35px";

4. JS can hide/Show hiiden HTML elements

    - Hiding HTML elements can be done by changing the display style: document.getElementById("demo").style.display = "none";
    - Showing hidden HTML elements can also be done by changing the display style: document.getElementById("demo").style.display = "block";

## <br>

### JavaScript Output : Display Possibilities

1. Writing into an HTML element, using `innerHTML or innerText`

    ```
        <p id="demo"></p>
        <script>
        document.getElementById("demo").innerHTML = "<h2>Hello World</h2>";
        document.getElementById("demo").innerText = "Hello World";
        </script>
    ```

    - Use innerHTML when you want to change an HTML element
    - Use innerText when you only want to change the plain text

2. Writing into the HTML output using `document.write()`
    - The document.write() method should only be used for testing
    - Using document.write() after an HTML document is loaded, will delete all existing HTML:
    ```
        <script>
        document.write(5 + 6);
        </script>
    ```
3. Writing into an alert box, using `window.alert()`

    - `window` word is optional
    - In JS, the window object is the global scope object. This means that variables, properties, and methods by default belong to the window object. This also means that specifying the window keyword is optional:

    ```
        <script>
        window.alert(5 + 6);
        alert(5 + 6);
        </script>
    ```

4. Writing into the browser console, using `console.log()`

    - For debugging purposes, you can call the console.log() method in the browser to display data
    - `console.log(5 + 6);`

5. JavaScript Print
    - JavaScript does not have any print object or print methods. You cannot access output devices from JavaScript.
    - The only exception is that you can call the window.print() method in the browser to print the content of the current window.

## <br>

###
