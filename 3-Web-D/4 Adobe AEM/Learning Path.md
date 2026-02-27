# AEM Learning Path

---

## 🧱 PART 1: Core AEM Foundation

| Topic             | Subtopics                                                                                                                                                                                  |
| ----------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| AEM Architecture  | - Author, Publish, Dispatcher model <br> - AEM as a CMS vs DAM <br> - JCR (Java Content Repository) <br> - AEM runtimes (Classic UI, Touch UI) <br> - Granite, Sling, and OSGi integration |
| Sling Resolution  | - Sling Resource Resolver <br> - Resource mapping and URL resolution <br> - Request processing with resource types and selectors <br> - sling:resourceType concept                         |
| AEM Authoring     | - Page and template creation <br> - Editable vs static templates <br> - Dialogs, Design Dialogs, Multifield <br> - Touch UI tools <br> - Content authoring best practices                  |
| Project Structure | - Maven multi-module setup <br> - Core, UI.apps, UI.content, dispatcher modules <br> - filter.xml and content packages <br> - AEM archetype project generation                             |

---

## 🎨 PART 2: AEM Front-End Development

### a) Front-End Basics

| Topic                  | Subtopics                                                                                                                                                       |
| ---------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| HTML, CSS, JS & jQuery | - Semantic HTML <br> - Responsive layout (Flexbox, Grid) <br> - DOM manipulation using JS/jQuery <br> - AEM-specific jQuery libraries                           |
| Less / Sass Framework  | - Variables, nesting, mixins <br> - Preprocessing and compilation <br> - Folder structure for maintainable CSS                                                  |
| AEM ClientLibs         | - clientlibs-folder setup <br> - Categories and dependencies <br> - js.txt and css.txt <br> - Embed vs Include vs Depends <br> - Minification, loading strategy |

### b) AEM Templating

| Topic         | Subtopics                                                                                                                               |
| ------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| HTL (Sightly) | - Expression language syntax <br> - data-sly-use/test/list <br> - Java class usage (Sling Models, WCMUsePojo) <br> - HTL best practices |

### c) Personalization & SPA

| Topic                         | Subtopics                                                                                                              |
| ----------------------------- | ---------------------------------------------------------------------------------------------------------------------- |
| Context Hub & Personalization | - Context Hub configuration <br> - Segmentation & targeting <br> - Personalization in components                       |
| Angular / React               | - Basics of React/Angular <br> - JSX (React), TypeScript (Angular) <br> - Creating components                          |
| State Management              | - React: useState, useEffect, Context API, Redux <br> - Angular: Services, RxJS, NgRx                                  |
| AEM SPA Editor                | - Editable templates for SPA <br> - SPA SDK integration <br> - JSON exporter <br> - Frontend-backend component mapping |

---

## 🔙 PART 3: AEM Back-End Development

### a) Backend Development

| Topic                     | Subtopics                                                                                            |
| ------------------------- | ---------------------------------------------------------------------------------------------------- |
| Maven & Dependencies      | - Parent/child POM structure <br> - AEM API dependencies <br> - Embedding/shading libraries          |
| Custom Component Creation | - Sling Models or WCMUsePojo <br> - Dialogs, configurations <br> - Backend logic                     |
| Sling Servlets            | - @SlingServlet (path/resourceTypes) <br> - GET/POST methods <br> - JSON response handling           |
| OSGi Services             | - @Component, @Service <br> - Configuration via annotations/files <br> - Service injection           |
| Workflow Administration   | - Create/manage workflows <br> - Custom workflow steps <br> - Launchers, workflow console            |
| Content Models            | - Content Fragments (structured/unstructured) <br> - CF Model Editor <br> - GraphQL/REST integration |

### b) Java & Microservices

| Topic                         | Subtopics                                                                                                                             |
| ----------------------------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| Java Basics & OOP             | - Classes, interfaces, polymorphism <br> - Collections, exceptions, I/O <br> - JDBC, REST, threading                                  |
| Microservices Architecture    | - REST API design <br> - JSON serialization (Jackson/Gson) <br> - API docs (Swagger) <br> - Auth (JWT/OAuth) <br> - CI/CD, Docker     |
| AEM Integration with Services | - HTTP client usage <br> - Scheduled jobs/background services <br> - Error handling & retries <br> - Secure HTTPS/authenticated calls |
