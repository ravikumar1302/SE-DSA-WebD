# 🧭 AEM Frontend Developer Roadmap & Guide

## **Stage 1 — Core Web Foundation**

| Area                 | Subpart           | Details                                                           |
| -------------------- | ----------------- | ----------------------------------------------------------------- |
| **Learn & Practice** | HTML5             | semantic tags, forms, accessibility (a11y)                        |
|                      | CSS3              | flexbox, grid, responsive design, BEM methodology                 |
|                      | JavaScript (ES6+) | DOM manipulation, Fetch API, async-await, modules, event handling |
|                      | Optional          | TypeScript                                                        |
| **Tools**            | —                 | VS Code, Browser DevTools, Git/GitHub                             |

---

## **Stage 2 — Modern Frontend Workflow**

AEM frontend uses modern build tools to generate client libraries (`/etc.clientlibs`).

| Area         | Subpart            | Details                                              |
| ------------ | ------------------ | ---------------------------------------------------- |
| **Learn**    | Node.js + npm/yarn | —                                                    |
|              | Webpack or Vite    | —                                                    |
|              | Babel and PostCSS  | —                                                    |
|              | SCSS/SASS          | —                                                    |
|              | ESLint, Prettier   | —                                                    |
| **Practice** | —                  | Build a simple site using Webpack bundling SCSS + JS |
|              | —                  | Learn about minification, tree-shaking, source maps  |

---

## **Stage 3 — AEM Basics**

Understand how AEM works internally to connect frontend and backend.

| Area                    | Subpart               | Details                                                                                                                                                                  |
| ----------------------- | --------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Key Concepts**        | —                     | What is AEM (Adobe Experience Manager), Author vs Publish instances, Sites, Templates, Components, Sling models, HTL (Sightly), JCR repository, Dispatcher (for caching) |
| **Learn HTL (Sightly)** | —                     | `data-sly-use`, `data-sly-list`, `data-sly-test`                                                                                                                         |
|                         | Expressions           | `${properties.title}`                                                                                                                                                    |
|                         | Conditional Rendering | Conditional rendering and iteration                                                                                                                                      |
|                         | Clientlibs inclusion  | `<cq:includeClientLib>`                                                                                                                                                  |

---

## **Stage 4 — AEM Frontend Development (Practitioner Level)**

| Area                              | Subpart | Details                                            |
| --------------------------------- | ------- | -------------------------------------------------- |
| **Component Development**         | —       | Folder structure: `/apps/project/components/...`   |
|                                   | —       | Create HTL, CSS, JS for each component             |
|                                   | —       | Map backend Sling Models → HTL via `data-sly-use`  |
|                                   | —       | Configure `dialog.xml` for author editing          |
| **Client Libraries (clientlibs)** | —       | Organize under `/apps/project/clientlibs`          |
|                                   | —       | Use categories, dependencies                       |
|                                   | —       | Load CSS/JS correctly in components                |
|                                   | —       | Use `allowProxy=true` for `/etc.clientlibs` access |
| **Style System**                  | —       | Create policies in editable templates              |
|                                   | —       | Allow authors to select component variations       |
| **Frontend-Backend Integration**  | —       | JSON Exporter (via Sling Model Exporter)           |
|                                   | —       | Consume AEM content as JSON in React/JS            |

---

## **Stage 6 — Build & Deploy**

Understand how to package and deploy frontend code in AEM.

| Area      | Subpart                   | Details                                      |
| --------- | ------------------------- | -------------------------------------------- |
| **Learn** | Maven build structure     | `ui.frontend`, `ui.apps`, `ui.content`       |
|           | Integrate frontend builds | `frontend-maven-plugin`                      |
|           | Deploy                    | `mvn clean install -PautoInstallPackage`     |
|           | Setup                     | Use AEM as a Cloud Service / local SDK setup |

---

## **Stage 7 — Optimization & Best Practices**

| Area               | Subpart | Details                                                      |
| ------------------ | ------- | ------------------------------------------------------------ |
| **Performance**    | —       | Lazy loading images                                          |
|                    | —       | Minify JS/CSS                                                |
|                    | —       | Use CDN caching + Dispatcher rules                           |
| **Best Practices** | —       | Use `data-sly-resource` instead of `cq:include`              |
|                    | —       | Avoid inline JS/CSS                                          |
|                    | —       | Keep clientlibs modular                                      |
|                    | —       | Follow naming conventions (`component-name/clientlibs/site`) |

---

<br>

# Useful Links

| Topic                  | Link                                                                                                                                                                            |
| ---------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| HTML                   | [Learn HTML](https://web.dev/learn/html/welcome)                                                                                                                                |
| Forms                  | [Learn Forms](https://web.dev/learn/forms/welcome?continue=https%3A%2F%2Fweb.dev%2Flearn%2Fforms%23article-https%3A%2F%2Fweb.dev%2Flearn%2Fforms%2Fwelcome)                     |
| HTML Performance       | [HTML Performance](https://developer.mozilla.org/en-US/docs/Learn_web_development/Extensions/Performance/HTML)                                                                  |
| CSS                    | [Learn CSS](https://web.dev/learn/css/welcome?continue=https%3A%2F%2Fweb.dev%2Flearn%2Fcss%23article-https%3A%2F%2Fweb.dev%2Flearn%2Fcss%2Fwelcome)                             |
| SASS                   | [Learn SASS/SCSS](https://www.studytonight.com/sass/introduction-to-sass-scss)                                                                                                  |
| Responsive Design      | [Learn Responsive Design](https://web.dev/learn/design/welcome?continue=https%3A%2F%2Fweb.dev%2Flearn%2Fdesign%23article-https%3A%2F%2Fweb.dev%2Flearn%2Fdesign%2Fwelcome)      |
| Images                 | [Learn Images](https://web.dev/learn/images/welcome?continue=https%3A%2F%2Fweb.dev%2Flearn%2Fimages%23article-https%3A%2F%2Fweb.dev%2Flearn%2Fimages%2Fwelcome)                 |
| CSS Performance        | [CSS Performance](https://developer.mozilla.org/en-US/docs/Learn_web_development/Extensions/Performance/CSS)                                                                    |
| JavaScript             | [Learn JavaScript](https://web.dev/learn/javascript/welcome?continue=https%3A%2F%2Fweb.dev%2Flearn%2Fjavascript%23article-https%3A%2F%2Fweb.dev%2Flearn%2Fjavascript%2Fwelcome) |
| JavaScript (Advanced)  | [JavaScript.info](https://javascript.info/)                                                                                                                                     |
| JavaScript Performance | [JavaScript Performance](https://developer.mozilla.org/en-US/docs/Learn_web_development/Extensions/Performance/JavaScript)                                                      |
| Webpack                | [Webpack Basics](https://daily.dev/blog/webpack-basics-for-beginners)                                                                                                           |
