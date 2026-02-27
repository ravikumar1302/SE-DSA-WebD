# BASIC HTML THEORY :

HTML was invented by Tim Berners Lee in 1993. He is the same man who invented internet, the World Wide Web

0. file Extension : file_name.html
1. Semantic tag are those tags, whose name signify thier work, like header, main, footer tags etc. While non-semantic can't signify like div and span tag

2. Inside Main tag :

    - Section Tag `<section>` For a section on your page
    - Article Tag `<article>` For an article on your page
    - Aside Tag `<aside>` For content aside main content(ads) : So that, search engine show your pages on the basis of main content, not ads. So, define them separately

3. All HTML elements can have attribute, Attributes usually come in name/value pairs like: name="value"
   The HTML standard does not require quotes around attribute values. However, W3C recommends quotes in HTML, and demands quotes for stricter document types like XHTML.

    Double quotes around attribute values are the most common in HTML, but single quotes can also be used. In some situations, when the attribute value itself contains double quotes, it is necessary to use single quotes.
    `<p title='John "ShotGun" Nelson'>` Or vice versa: `<p title="John 'ShotGun' Nelson">`

4. There are two ways to specify the URL in the src attribute:

    1. Absolute URL - Links to an external image that is hosted on another website. Example: src="https://www.w3schools.com/images/img_girl.jpg".

    2. Relative URL - Links to an image that is hosted within the website. Here, the URL does not include the domain name. If the URL begins without a slash, it will be relative to the current page.
        - Example: src="img_girl.jpg". If the URL begins with a slash, it will be relative to the domain. Example: src="/images/img_girl.jpg".

    Tip: It is almost always best to use relative URLs. They will not break if you change domain.

5. The title Attribute : It defines some extra information about an element. Iy will be displayed as a tooltip when you mouse over the element:

    - Example : `<p title="I'm a tooltip">This is a paragraph.</p>`

6. For internal linking using href : `<a href="#about us">About US</a>` and give id to that section, `<section id="about us">......</section>`

## <br>

### **Structural vs Semantic vs Non-Semantic tags** :

-   **Structural markup**

    -   Purpose: defines document structure (headings, paragraphs, sections).
    -   Example: `<h1>, <p>, <ul>, <li>, <table>`
    -   Structural elements can be semantic (e.g., `<h1>` tells us it's the most important heading) or non-semantic depending on context.

-   **Semantic markup**

    -   Purpose: conveys meaning about the content (importance, quotations, citations, emphasis).
    -   Example: `<em>, <strong>, <blockquote>, <abbr>, <cite>`
    -   These elements explicitly say what the text means. These tags are those tags which make some logical meaning (Text elements that doesn't affect the structure of your web pages, but they add extra information to the pages)
    -   There are some text elements that are not intended to affect the structure of your web pages, but they do add extra information to the pages — they are known as semantic markup

-   **Non-Semantic markup**

    -   Purpose: gives no inherent meaning, just generic structure or styling hooks.
    -   Example: `<div> and <span>`
    -   They don’t tell browsers or assistive tech what the content is, only provide grouping.
    -   SEO, screen-reader will easily acces your page if you have more semantic tags. As sematic tags make page more structured.

---

7. Empty elements : There are a few elements that do not have any words between an opening and closing tag. e.g. `<br>, <hr>`

8. White Space Collapsing : When the browser comes across two or more spaces next to each other, it only displays one space. Similarly if it comes across a line break, it treats that as a single space too. This is known as white space collapsing.

9. The `<div> and <span>` elements allow you to group block-level and inline elements together.

10.
