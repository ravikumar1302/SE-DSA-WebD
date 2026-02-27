# General Information:

0. AEM : Adobe Experience Manager
1. Content type allowed in AEM : Text, JSON, Images, PDF, PPT
2. AEM has folder like structure.  
   e.g. Site > Languages > products > details etc.

3. CRXDE : Content Repository eXtreme Development Environment.

```
- CRXDE is a JCR (Java Content Repository) interface.
- JCR is a file system, which contains both actual code and properties file
- AEM uses Apache Jackrabbit Oak, a hierarchical, node-based "NoSQL" content repository that underpins AEM.
  - It's a web/desktop-based tool used for directly interacting with the JCR (Java Content Repository).
  - Two main versions: Lite (built-in, web-based) and Full IDE (Eclipse-based desktop IDE, now largely deprecated)
  - CRXDE Lite is accessible in browser: http://localhost:4502/crx/de - (Replace localhost:4502 with your instance host & port)
  - It allows developers to:
    - Browse and edit the JCR repository structure (/apps, /content, etc.)
    - Create, delete, or modify nodes and properties
    - Upload/download files like .jsp, .xml, .html, .json, etc.
    - Manage permissions on content nodes
    - View and edit component definitions and configurations
    - Debug issues in the repository directly (carefully)
```

4. OSGI Container :
   <br><img src="../Images/AEM_Architecture.png" alt="AEM Architecture" width="40%" style="display: block; margin: auto;"><br>

```
- OSGi is a Java framework for developing and deploying modular software programs and libraries. It allows applications to be broken into reusable, dynamic modules (called bundles), which can be independently started, stopped, updated, or removed at runtime.

- AEM Architecture:
   - AEM (Application Layer): The Adobe Experience Manager application itself; implemented as OSGi bundles running within Felix.
   - Apache Sling (Web Application Framework): Runs on Felix; maps HTTP requests to JCR content and handles rendering.
   - Apache Jackrabbit Oak (JCR Repository / Storage Layer): Stores AEM's content and data. Felix provides its runtime environment.
   - Apache Felix (OSGi Java Container): The foundational runtime environment enabling modularity (install, start, stop, update bundles) without restarts.
```

5. AEM Templates, Components, Authoring :
   <br><img src="../Images/AEM_Author_and Publish_Flow.png" alt="AEM_Author_and Publish_Flow" width="40%" style="display: block; margin: auto;"><br>

    - AEM contains a lot of templates and options to select from like Container, Progress bar, Tabs, Accordian,Text Box, Paragraph, Buttons, Breadcrumb, Carousel etc
    - AEM Author Environment (CURD Page) : Changes can be done till this. After Authoring; Replication happens and Page is went to Publisher
    - AEM Publish Environment : From this environment, page goes to Apache Web server and then end user

6. AEM Page Render Flow

Flow (Developers - Read opposite) : User URL > CDN > Load balancer > Dispatcher > AEM Pub > AEM Author > CD > Developer

<img src="../Images/AEM_Page_Render_Flow.png" alt="AEM_Page_Render_Flow" width="40%" style="display: block; margin: auto;">
<br>

```
Remember the Newspaper Example for this.
   - CDN (Content Delivery Network): caches Static content geographically closer to users, speeding up delivery and reducing server load.
   - Load Balancer: Distributes user requests among multiple servers for performance and reliability.
   - Dispatcher: Caches AEM content, balances requests to AEM Publish instances and manage security (first line of defense for AEM).
   - AEM Pub (Publish Instance): Serves published website content to end-users.
   - AEM Author (Author Instance): Used by authors to create and manage website content.
   - CD (Code Deployment): The process of deploying application code (from developers) to AEM instances.

   - Web Server Functionality: The Dispatcher acts as a web server (typically an Apache HTTP Server with the AEM Dispatcher module). Its primary roles are to:
      - Serve static content directly from its cache.
      - Proxy requests for dynamic content to the AEM Publish instances.
      - Handle URL re-writing, vanity URLs, and other web server-level tasks.

   - Application Server Functionality: The AEM Pub (Publish) and AEM Author instances inherently provide the application server functionality.
   - AEM is a Java web application. It uses an embedded servlet engine (e.g., Jetty) or can deploy on external ones (e.g., Tomcat).
   - AEM instances process dynamic requests, render pages from content, execute Java code, and manage database interactions – essentially, the core application logic.
```

7. AEM SLING End to End Flow

```
1. [User Request]
   ↓
2. Web Browser
   ↓
3. CDN (optional cache layer)
   ↓
4. Web Server (httpd on port 8080)
   ↓
5. OSGI Framework
   ↓
6. OSGI HTTP Service (via namespace mapping)
   ↓
7. Sling Bundle (Registers Sling Main Servlet)
   ↓
8. Sling Main Servlet handles the request
   ↓
9. Sling Bundle checks if ResourceResolverFactory is available
   ↓
10. Resource Resolver Factory creates Resource Resolver
    ↓
11. Resource Resolver uses the URL to find the correct Resource
    ↓
12. Resource (JCR node) is resolved
    ↓
13. Sling uses Resource Type for Script or Servlet Resolution
    ↓
14. HTL or servlet renders the final content

```

8. HTL : HTML Template Language

```
   - HTL is a templating language created by Adobe for AEM
   - It's designed to replace JSP (JavaServer Pages) in AEM projects.
   - In AEM, Sling Template Language (Sightly) — now known as HTL is a templating language used to build dynamic components and web pages.
   - Purpose: Securely bind dynamic content into HTML templates in AEM.
   - e.g. <div data-sly-set="${variable}">
      Syntax is HTML-like but with dynamic elements (data-sly-\*, ${}).
   - HTL Scripts are also processed by AEM as servlet
   - HTL can do : Variable Setting, If Condition, Operators, Loops, Function, Include another file, Display Context, Global Objects etc
   - More Details on HTL in "Frontend > HTL" folder in this repository
```

9. Maven :
   Maven is a build and dependency management tool used in AEM to compile code, manage libraries, and deploy packages to AEM instances.

```
   - Project structure: Organizes AEM code (core, UI, content) using AEM Archetype.
   - Dependency management: Automatically fetches required AEM and Java libraries.
   - Build automation: Compiles Java code, creates deployable packages (.zip).
   - Deployment: Installs packages into AEM using commands like "mvn install"
   - Environment config: Supports different run modes and environments.

```

10. What are AEM Content Fragments?
    -   Content Fragments (CFs) in AEM are reusable, structured content units.
    -   They’re built using Content Fragment Models, which define fields like text, date, number, references, etc.
    -   CFs are perfect for omnichannel content delivery (web, mobile, voice, etc.) because they contain pure content, independent of layout or styling.
