## Core Java for AEM: A Beginner’s Guide

Few “Core java” concept one need to learn before deep dive into AEM, there are multiple concepts like OOPs (Encapsulation, Abstraction, Inheritance, Polymorphism) Multithreading and many more.. below are some important concepts that will help you to begin and will essentials on daily basis tasks.

-   Variables
-   Methods
-   Classes and Objects
-   Interfaces
-   Loops and Conditional operators
-   Collections
-   Exception Handling

<br>

1. **Variables**: Variables in Java are like cookie jars that can hold different types of cookies (data) such as the number of cookies (int), their flavors (String), or their prices (double).

    ```
    int numberOfCookies = 10;
    String flavor = "Chocolate";
    double price = 2.99;
    ```

2. **Methods (functions)**: Methods in Java are like cookie recipes. They define instructions on how to make and decorate cookies, allowing you to reuse the recipe (method) multiple times.
    ```
    public void bakeCookies() {
    // Instructions for baking cookies
    }
    ```
3. **Classes and Objects** : It’s similar to using a cookie cutter to create cookies. The class is the cookie cutter, and the object is the cookie produced from it, Classes in Java are blueprints that define the attributes and behaviors of objects. Objects are instances of classes, representing real-world entities.

    ```
    public class Cookie {
    // Cookie class with attributes and behaviors
    }
    Cookie myCookie = new Cookie()
    ```

4. **Interface (similar to abstract classes with pure virtual functions in C++)**: Interfaces in Java are like cookie molds that define a common shape (methods) for different types of cookies. Classes can implement multiple interfaces to have different flavors (methods)

    ```
    public interface CookieFlavor {
    void setFlavor(String flavor);
    String getFlavor();
    }
    class Cookie implements CookieFlavor{
        public void setFlavor(String flavor) {
            System.out.println("Set Cookie flavor");
        }
    public String getFlavor() {
            return "Cookie flavour"
        }
    }
    ```

5. **Collections (Comparable to STL containers (vector, map, set, etc.) in C++.)** : Collections in Java are like cookie jars with different types, such as ArrayList (a jar that can hold multiple cookies), HashMap (a jar with cookies indexed by flavors), etc.

    ```
    ArrayList<String> cookieJar = new ArrayList<>();
    cookieJar.add("Chocolate Chip");
    cookieJar.add("Oatmeal Raisin");
    // Hashmap
    HashMap<String, String> cookieJarMap = new HashMap<>();
    ```

6. **Exception Handling** : It is like having a backup plan in case a cookie recipe goes wrong. It allows you to catch errors and handle them gracefully, so your program doesn’t crash.

    ```
    try {
        // Code that may throw an exception
    } catch (Exception e) {
        // Handling the exception
    }
    ```
