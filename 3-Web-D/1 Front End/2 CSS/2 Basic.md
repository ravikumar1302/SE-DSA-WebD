## BASIC CSS THEORY :

-   CSS was first proposed by Håkon Wium Lie on 10 October 1994. At the time, Lie was working with Tim Berners-Lee at CERN.
-   CSS (Cascading Style Sheets) is a language designed to simplify the process of making web pages presentable.
-   The main advantages are the separation of content (in HTML) and styling (in CSS). Also, the same CSS rules can be used across all pages and not have to be rewritten.
-   HTML uses tags and CSS uses rule sets. CSS styles are applied to the HTML element using selectors.

-   **Main Topics** :
    -   Type of CSS : Inline, internal and external CSS
    -   Selectors
    -   CSS Color & Background
    -   Fonts, colors, text-align, and font-family
    -   Psuedo Class :
        -   Positioning: static, relative, absolute, fixed
        -   Display properties: block, inline-block, flex
        -   Hover effects, focus styles, and transitions
    -   Box Model : CSS Border, Border margin and padding concepts

0.  file Extension : file_name.css
    -   Use "attribute-extra", here extra can be top, bottom, etc. Means if you want to specificly use one thing, just mention it with the attribute
1.  Breaking Acronym :

    -   Cascading : Falling of Styles
    -   Style : Adding designs/ Styling our HTML tags
    -   Sheets : Writing our style in different documents
    -   CSS describe the visual style and presentation of content written in HTML

2.  Basic Structure :

    ```Selector // The selector + Declaration Block is known as CSS Rule
    { // The block inside the curly braces is known as Delaration Block
    Property 1 : value; // Each such line is known as Declaration/ Style = Property + Value
    Property 2 : value;
    Property 3 : value;
    }
    ```

    -   Selector : Selects the element you want to target
    -   Few basic selector like tags, id's, and classes

3.  Three Type : Inline CSS, Internal CSS and External CSS :

    -   **Priority Order** : `Inline > Internal > External`
    -   In INLINE style attribute is used, in Internal `<Style>` tag is used. Add all CSS at one place in HTML file
    -   Demo Code of INTERNAL : Written inside `<head>` tag

    ```<html>
    <head>
        <style>
        <!-- Now choose selector like h1, p etc and give values -->
        h1{
        color : green;
        background-color : black;
        text-align : center;
        }
        </style>
    </head>
    </html>
    ```

    -   Use <link> tag in html to link EXTERNAL CSS file : `<link rel = "stylesheet" type = "text/css" href = "file_name.css">`

4.  Five Simple Selectors :

    -   Element/ Type Selector : Directly HTML tag name is used. For `<h1>` we used h1
    -   Id Selector (#) : Using 'id' attribute in HTML Document and '#' in CSS (`#id\*name` in CSS). Id can have any kind of value, character, digit etc.
    -   Class Selector (.) : Using 'class' attribute in HTML Document and '.' in CSS ('.class_name' in CSS). Differnt type of tags can be given same class, to have same styling
    -   Group Selector (,) : Just Write tags with comma, h1, h2, p {color : blue;}
    -   Universal Selector (`\*`) : It appy changes everywhere, {background-color : black;}

    Priority : Id > Class > Element

5.  CSS Color :

    -   RGB : takes 3 parameter, eg. for red rgb(255, 0, 0), each value vary from 0 to 255
    -   HEX : Start with '#' and has 6 digits, like #ff0000 for red, each set (pair of 2 digit, one set each for rgb), varies from 00 to ff
    -   HSL : Hue Saturation Light eg. (0, 100%, 50%) for red
    -   Website link to easyily findout color codes : https://htmlcolorcodes.com/

6.  CSS Background :

    -   background-image : This property is used to set an image as a background of an element. By default the image covers the entire element.
    -   background-repeat : by default, this property repeated the background image horizontally and vertically. Some images are repated only horizontally or vertically.
    -   background-position : this property is used to define initial position of the background image. By default, the background image is placed on the "top-left" of the web-page.

    ```
    E.g.,
    <style>
        body {
            background : url(images/download.jpg);
            background-repeat : no-repeat; // use repeat-x for horizontal repeat and repeat-y for vertical
            background-attachment : fixed; // Makes the image fixed, even if page is scrolled
            background-position : center; // To center the image on webpage
            background-size : cover; // To fill the web page with that image
        }
    </style>
    ```

7.  CSS Text and Font :

    -   TEXT:

        -   text-color
        -   text-align
        -   text-decoration : This property is used to set or remove decorations from text. The value "text-decoration : none;" is often used to remove underlines from links.
        -   text-trasform : This property is used to specify uppercase and lowercase letters, capitalise(first letter of each word capital) in a text.

    -   FONT: It is used to control look of texts.
        -   font-color
        -   font-size
        -   font-family : used to change the face of the font (like arial, times new roman etc.)
        -   font-style : the font-style property is mostly used to specify italic text. It has 3 properties : normal, italic and oblique.
        -   font-variant : specifies how to set font varient. It may be small-caps, normal
        -   font-weight : used to increase or decrease the boldness and lightness. It defines the weight of the font and specify how bold a font is. Values are : normal, bold, bolder, lighter or number(100, 200...upto 900)

8.  Pseudo Classes :

    -   It can be defined as a keyword which is combined to a selector that defines the special state of the selected elements. It is added to the selector for adding an effect to the existing element based on thier states.
    -   syntax : A pseudo-class starts with colon(:)
        selector : pseudo-class {
        property : value;
        }
    -   pseudi-class is generally of 4 types : link, visited, hover, active. It is mostly used to show state of links and nav-bar by showing differnet color for different state

    ```
        : active - used to add style to an active element
        : hover - adds special effects to an element when user moves the mouse pointer over the element
        : link - adds style to a un-visited link
        : visited - adds style to a visited link
        : first-child - adds special effects to an element, which is the first child of another element
    ```

    -   Eg.

    ```
        <style>
            h1 : hover{
            color : red;
            }
        </style>
    ```

9.  CSS Border : Sets up border for HTML elements. It has 4 properties :

    -   width
    -   color
    -   style - sets stlye of border like, solid, dashed, dotted, ridge, groove, inset, outset etc.
    -   radius - determines the roundness of theborder

    -   Top, bottom together can be clubbed and same goes for left and right. e.g. border-width : 2px 5px; sets top and bottom 2px and left and right 5px
    -   border can also be set in a single lines e.g. border : 2px solid blue;
    -   top right bottom left is the order followed if you give 4 values

10. CSS Box Model : Deals with three things : Border, Padding, MArgin

    -   It consists of 4 edges :

        -   Content edge : It comprises of the actual content, like the thin area near each alphabet, e.g. 'H'
        -   Padding edge : It lies in between content and border edge
        -   Margin edge : It is outside border and controls margin of the element
        -   Border edge : Padding is followed by the border edge

    -   Every element in CSS can be represented using Box Model. It helps developer to develop and manipulate the elements.
    -   E.g.,

    ```
    h1 {
    border : 2px solid blue;
    margin : 5px;
    padding : 20px; <!-- use padding-top : 20px for top padding only -->
    content : 50px;
    }
    ```

11.
