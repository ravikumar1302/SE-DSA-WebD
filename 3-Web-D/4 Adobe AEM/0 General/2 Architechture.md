# Architecure

**1. Genreal Web Development Architecture:**
Client (user browser) > Web server > App server > Database

    a) If it's a static page (url.html), request gets served from Web server itself.
    b) If dynamic content is needed, then Web server sends request to App server and App servers provides the content.
    c) Java framewrok : Looks the URL that came from client. Also, Java and it's class etc are all stored in App server

**2. AEM Web Development Architecture:**
Client (user browser) > Web server (Dispatcher) > App server (Sling Framework) > Database (JCR)

    a) App Server : Apache Sling Framework is used. It's work is to check which JAVA class/code block to use, when this URL is called.
    b) JCR : No-SQL Database

<div style="display: flex; flex-wrap: wrap; gap: 16px; justify-content: space-between;">
    <img src="../Images/AEM_Web_Development_Architecture.png" alt="AEM Web-D Architecture" width="47%">
    <img src="../Images/AEM_Architecture.png" alt="AEM Architecture" width="47%">
    <img src="../Images/AEM_Author_and Publish_Flow.png" alt="AEM_Author_and Publish_Flow" width="47%">
    <img src="../Images/AEM_Page_Render_Flow.png" alt="AEM_Page_Render_Flow" width="47%">
</div>
