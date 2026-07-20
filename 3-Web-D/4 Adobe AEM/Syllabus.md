AEM Learning Path (Structured Syllabus)
========================================

**PART 1: Core AEM Foundation**

- AEM Architecture
- AEM Sling Resolution
- AEM Authoring
- AEM Project Structure

**PART 2: AEM Front-End Development**

- **Front-End Basics**
    - HTML, CSS, JavaScript & jQuery
    - Less / Sass CSS Framework
    - AEM ClientLibs (compiling CSS & JS in AEM)
- **AEM Templating**
    - AEM HTL Templating Language
- **Front-End Personalization & SPA**
    - AEM Context Hub & Personalization
    - Angular / React Framework / Experience
    - Angular / React State Management
    - AEM SPA Editor (Single Page Application Integration)

**PART 3: AEM Back-End Development**

- **Core Back-End Skills**
    - Maven & Dependency Management
    - AEM Custom Component Creation
    - Sling Servlets
    - OSGi Services (modular backend components)
    - Workflow Development / Administration
    - Content Model Creation (using Content Fragments, Models)
- **Java & Microservices**
    - Java Basics & OOP
    - Microservices Architecture / Experience
    - Integration of Java Microservices with AEM

---

AEM Learning Path with Detailed Topics
=======================================

**PART 1: Core AEM Foundation**

| Topic | Subtopics |
| ----- | --------- |
| **AEM Architecture** | • Author, Publish, Dispatcher model<br>• AEM as a CMS vs DAM<br>• JCR (Java Content Repository)<br>• AEM runtimes (Classic UI, Touch UI)<br>• Granite, Sling, and OSGi integration |
| **AEM Sling Resolution** | • Sling Resource Resolver<br>• Resource mapping and URL resolution<br>• Request processing with resource types and selectors<br>• `sling:resourceType` concept |
| **AEM Authoring** | • Page and template creation<br>• Editable templates vs static templates<br>• Dialogs, Design Dialogs, Multifield, Granite UI<br>• Touch UI authoring tools<br>• Content authoring best practices |
| **AEM Project Structure** | • Maven multi-module setup<br>• Core, UI.apps, UI.content, dispatcher modules<br>• Filter.xml and content packages<br>• AEM archetype project generation |

---

**PART 2: AEM Front-End Development**

**a) Front-End Basics**

| Topic | Subtopics |
| ----- | --------- |
| **HTML, CSS, JS & jQuery** | • Semantic HTML<br>• Responsive layout (Flexbox, Grid)<br>• DOM manipulation using JS/jQuery<br>• AEM-specific jQuery libraries |
| **Less / Sass CSS Framework** | • Variables, nesting, mixins<br>• Preprocessing and compilation<br>• Folder structure for maintainable CSS |
| **AEM ClientLibs** | • clientlibs-folder setup<br>• Categories and dependencies<br>• js.txt and css.txt files<br>• Embed vs Include vs Depends<br>• Loading and minification |

**b) AEM Templating**

| Topic | Subtopics |
| ----- | --------- |
| **AEM HTL Templating Language** | • Expression language syntax<br>• `data-sly-use`, `data-sly-test`, `data-sly-list`<br>• Calling Java classes (WCMUsePojo, Sling Models)<br>• HTL best practices |

**c) Front-End Personalization & SPA**

| Topic | Subtopics |
| ----- | --------- |
| **AEM Context Hub & Personalization** | • Context Hub configuration<br>• Segmentation rules and targeting<br>• Personalization in components |
| **Angular / React Framework / Experience** | • Basics of React / Angular setup<br>• JSX (for React), TypeScript (for Angular)<br>• Creating components and state management |
| **Angular / React State Management** | • React: useState, useEffect, Context API, Redux<br>• Angular: Services, RxJS, NgRx basics |
| **AEM SPA Editor** | • Editable templates for SPA<br>• SPA SDK integration<br>• Sling Model JSON exporter<br>• Connecting AEM components with front-end SPA |

---

**PART 3: AEM Back-End Development**

**a) Back-End Development**

| Topic | Subtopics |
| ----- | --------- |
| **Maven & Dependency Management** | • Parent/child POM structure<br>• Adding dependencies for AEM APIs<br>• Embedding and shading libraries |
| **AEM Custom Component Creation** | • Java classes using Sling Models or WCMUsePojo<br>• Component dialogs and configurations<br>• Backend logic for dynamic components |
| **Sling Servlets** | • `@SlingServlet` vs resourceTypes vs paths<br>• GET and POST methods handling<br>• Returning JSON data |
| **OSGi Services** | • `@Component`, `@Service` annotations<br>• OSGi Configuration with annotations or config files<br>• Service references and dependency injection |
| **Workflow Development / Administration** | • Creating and managing workflows<br>• Custom workflow steps<br>• Launcher and models<br>• Workflow console and runtime debugging |
| **Content Model Creation** | • Content Fragments (structured/unstructured)<br>• Models using Content Fragment Models Editor<br>• Consuming CFs in GraphQL or via REST APIs |

**b) Java & Microservices**

| Topic | Subtopics |
| ----- | --------- |
| **Java Basics & OOP** | • Classes, interfaces, inheritance, polymorphism<br>• Collections, Exception handling, I/O<br>• Basic JDBC, REST calls, multithreading |
| **Microservices Architecture / Experience** | • REST APIs design (GET, POST, PUT, DELETE)<br>• JSON serialization/deserialization<br>• API documentation (Swagger/OpenAPI)<br>• Authentication/Authorization (JWT, OAuth)<br>• CI/CD basics and containerization (Docker) |
| **Integration of Java Microservices with AEM** | • Consuming external services in AEM<br>• Scheduler jobs & background services<br>• Error handling and retries<br>• Secure connection (HTTPS, authentication) |
