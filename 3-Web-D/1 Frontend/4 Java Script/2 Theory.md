BASIC JavaScript THEORY :

JavaScript was first proposed by => Brendan Eich in 1995

Main Topics : Closures, Prototype, Event Loop, Async Await

0. file Extension : `file_name.js`
- **0.1 JS is Case-Sensitive.**
    - i.e., X is different from x
    - Hyphens are not allowed in JavaScript variable names (first-name not allowed). They are reserved for subtractions.
    - JavaScript accepts both double and single quotes: `"hello" == 'hello'`
    - JavaScript is a programming language of the web, that is essential for web development
    - Any web page you interact with today, JavaScript is most likely providing the action on the page
    - JavaScript can be used to change the status of a button when it is clicked on, create a chat window at the bottom of your screen, or even create a web-based game
    - With modern tools like Node.js, JavaScript can now also be used to save data to a database or to create desktop applications. The applications are limitless
    - It can calculate, manipulate and validate data
    - It can update and change both HTML and CSS
- **0.2 DEFINITIONS**
    - JS is a High level, just in time compiled programming language (means it compiles at run time, unlike java you don't have to first compile and then run it)
    - JS is a lightweight, interpreted, object-oriented language with first-class functions, and is best known as the scripting language for Web pages, but it's used in many non-browser environments as well
    - It is a prototype-based, multi-paradigm scripting language that is dynamic and supports object-oriented, imperative and functional programming styles
    - JS runs on browsers and servers (NodeJS) or JS run on the client side of the web, which can be used to design / program how the web pages behave on the occurrence of an event. JS is an easy to learn and also powerful scripting language, widely used for controlling web page behavior.
    - It has application programming interfaces (APIs) for working with text, dates, regular expressions, standard data structures, and the Document Object Model (DOM).

1. Everything in JS happens inside an Execution Context. It is like a big box that contains 2 things :
    - **Memory or Variable environment** (Stores variable and functions as a key : value pair)
    - **Code or Thread of execution** (means the coding part)

2. Memory portion of Execution Context is created as soon as you start writing variables and functions. While the code portion runs while you run the code

    Example :
    ```js
    var n = 2;
    function square(num) {
        var ans = num * num;
        return ans;
    }
    var square2 = square(n);
    var square4 = square(4);
    ```

    The memory portion stores like this :
    - for variable like n, square2, variable name with special value : undefined is stored : (n : undefined)
    - for functions the whole code is stored : (square : and the whole code)

    When the 2nd phase, Execution phase starts,
    - For variable : the undefined value gets replaced by the value given by user. In the above code the n : undefined will become n : 2, in the execution phase
    - For function : whenever a function is invoked, a nested Execution Context Box is created within code section of existing or main or Global Execution Context Box and calculations are done, and when return statement is reached, that nested Execution Context Box ends. After the whole program is done, the main or Global Execution Context Box is also deleted
        This is why, Functions are also called as "Heart of JS"
    - JS manages this Global and nested functions Execution Context Box using Call Stack. Call Stack maintains the order of execution contexts, so Firstly global Execution Context is entered and then nested functions Execution Context
    - Call stack has various names : Call Stack, Execution Context Stack, Program Stack, Control Stack, Runtime Stack, Machine Stack.

---

3. JS is a Synchronous, Single threaded language
    Synchronous : executes in a specific order, means firstly the first line and then the second and so on
    Single threaded : executes one command at a time like interpreter

4. React is a JS library
5. JS Applications
    - Web/ Mobile Apps
    - Real Time Applications
    - Desktop/ Command line tools
    - Games Development

6. JS is run by JS engine on browsers. Like V8 engine on chrome, Spider monkey on mozilla
    Also, Nodejs is a JS runtime built on Chrome V8 JS engine for executing JS outside browser

7. `<script>` tag is used inside HTML document to use JS. But it is recommended to make a separate file and then link it using src attribute in script tag.

---

8. Primitive Data Types in JS

    JavaScript has 6 primitive data types, but we'll only talk about 5 of them. Here's what they look like:
    ```js
    let greeting = "hello";         // string
    let favoriteNum = 33;           // number
    let isAwesome = true;           // boolean
    let foo;                        // undefined
    let setToUndefined = undefined; // undefined
    let empty = null;               // null - Null is not the same as undefined. It signifies an intentional absence of data.
    ```

    JavaScript is known as a "weakly" typed language. What this means is that when you create variables and assign them to values, you do not have to specify the type of data you are working with.
    In statically (or strongly) typed languages, like Java and C++, you do need to specify the type like int, string, char

    ```js
    let c = Math.sqrt(a * a + b * b);

    let noValue;                   // Any variable created without a value is undefined
    let favoriteFood = undefined;  // You can also explicitly set a variable to undefined
    ```
