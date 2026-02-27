# Java Script Theory

1. Hoisting : in JavaScript refers to the behavior where variable and function declarations are moved (or "hoisted") to the top of their scope (global or function scope) during the compilation phase, before the code is executed.

    - Function declarations → Hoisted completely
    - var → Hoisted, initialized with undefined
    - let / const → Hoisted, but inaccessible until declared (TDZ)
    - Function expressions / Arrow functions → Hoisted like variables, not as functions

2. The Scope Chain, Scope & Lexical Environment

    - Scope of a variable is directly dependent on the lexical environment.
    - Whenever an execution context is created, a lexical environment is created. Lexical environment is the local memory along with the lexical environment of its parent. Lexical as a term means in hierarchy or in sequence
    - Having the reference of parent's lexical environment means, the child or the local function can access all the variables and functions defined in the memory space of its lexical parent
    - The JS engine first searches for a variable in the current local memory space, if its not found here it searches for the variable in the lexical environment of its parent, and if its still not found, then it searches that variable in the subsequent lexical environments, and the sequence goes on until the variable is found in some lexical environment or the lexical environment becomes NULL
    - The mechanism of searching variables in the subsequent lexical environments is known as Scope Chain. If a variable is not found anywhere, then we say that the variable is not present in the scope chain

3. **Variables in JS**

    1. **Var** :
        - Variables declared with the var always have Global Scope. It cannot have Block Scope.
        - These can be re-declared and values can be updated
        - Variables defined with var are hoisted to the top and can be initialized at any time. Meaning: You can use the variable before it is declared
        ```
            E.g., below is okay
            carName = "Volvo";
            var carName;
        ```
    2. **Let** :
        - Variables declared with let have Block Scope
        - These variables must be Declared before use
        - These cannot be redeclared in the same scope, but there values can be updated
        - Variables defined with let are also hoisted to the top of the block, but not initialized. Meaning: Using a let variable before it is declared will result in a ReferenceError
    3. **Const** :

        - JavaScript const variables must be assigned a value when they are declared : const PI = 3.14159265359;
        - Variables defined with const cannot be Redeclared and thier values cannot be Reassigned
        - Variables defined with const have Block Scope

        - The keyword const is a little misleading. It does not define a constant value. It defines a constant reference to a value.
        - Because of this you can NOT: Reassign a constant value, constant array or constant object
        - But you CAN: Change the elements of constant array, Change the properties of constant object

        - **Constant Arrays**

        ```
            // You can create a constant array:
            const cars = ["Saab", "Volvo", "BMW"];

            // You can change an element:
            cars[0] = "Toyota";

            // You can add an element:
            cars.push("Audi");

           => But you can NOT reassign the array:
                const cars = ["Saab", "Volvo", "BMW"];
                cars = ["Toyota", "Volvo", "Audi"];    // ERROR
        ```

        - **Constant Object**

        ```
           => You can change the elements of a constant array:

            // You can create a constant array:
            const cars = ["Saab", "Volvo", "BMW"];

            // You can change an element:
            cars[0] = "Toyota";

            // You can add an element:
            cars.push("Audi");
        ```

    ### Difference Between var, let and const

    | Keyword   | Scope | Redeclare | Reassign | Hoisted | Binds 'this' |
    | --------- | ----- | --------- | -------- | ------- | ------------ |
    | **var**   | No    | Yes       | Yes      | Yes     | Yes          |
    | **let**   | Yes   | No        | Yes      | No      | No           |
    | **const** | Yes   | No        | No       | No      | No           |

4. `let & const in JS (Temporal Dead Zone)`

    - let and const are hoisted but its memory is allocated at other place than window which cannot be accessed before initialisation
    - Temporal Dead Zone exists until variable is declared and assigned a value
    - window.variable OR this.variable will not give value of variable defined using let or const
    - We cannot redeclare the same variable with let/const(even with using var the second time)
    - const variable declaration and initialisation must be done on the same line

    - There are three types of error:

        - referenceError {given where variable does not have memory allocation}
            - Like when accessing 'let' variables before declaration, as they were in TDZ (Temporal Dead Zone)
            - Like when accessing, a variable which is not declared (or present in code)
        - typeError {given when we change type that is not supposed to be changed}
            - Like re-assigning value to a const variable
        - syntaxError {when proper syntax(way of writing a statement) is not used}
            - Like when const variable is declared without initialisation

    - Use const wherever possible followed by let, Use var as little as possible(only if you have to). It helps avoid error
    - Initialising variables at the top is good idea, helps shrinks TDZ to zero
    - Level of strictness ... var << let << const

5. BLOCK SCOPE & Shadowing in JS

    - **Block Scope** : Code inside curly bracket `{}` is called block
    - Blocks are used to group multiple statements together, typically in constructs like if, else, for, while, function, etc.
    - Block values are stored inside separate memory than global. They are stored in block (the reason `let and const` are called block scope)
    - Variables declared with var are not block-scoped. They are stored in the nearest enclosing function scope (or the global scope if outside a function)
    - **Shadowing** - Shadowing occurs when a variable declared inside a block has the same name as a variable declared in an outer scope
    - The inner variable “shadows” (overrides) the outer one within that block
    - Shadowing is allowed as long as it doesn’t violate scoping rules
    - Shadowing with let or const inside a block is legal, provided the shadowed variable remains in its own scope
    - **Illegal Shadowing**: Shadowing a let or const variable with var in the same or inner scope causes an error, because var is function/global scoped and tries to overwrite the block scope.

    ```
        let a = 5;
        {
        var a = 10; // ❌ Illegal shadowing
        }
    ```

    - var → function/global scoped, accessible outside the block
    - let & const → block scoped, accessible only within the block they are defined

6.
