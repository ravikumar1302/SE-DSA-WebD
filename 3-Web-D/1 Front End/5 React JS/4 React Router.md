# React Router

- React Router is a standard library for routing in React
- It enables the navigation among views of various components in a React Application, allows changing the browser URL and keeps the UI in sync with the URL
- It enables client-side navigation, allowing users to move between different views or pages without the browser reloading the entire HTML document

- Core Functionality:
    - Declarative Routing: You define paths as components (e.g., `<Route path="/about" />`).
    - Dynamic UI: It synchronizes the browser URL with the component hierarchy displayed on the screen.
    - Single Page Application (SPA) Support: It mimics a multi-page experience by intercepting URL changes and rendering only the necessary component updates.

- Primary Components:
    - BrowserRouter: The top-level wrapper that uses the HTML5 History API to keep your UI in sync with the URL.
    - Routes: A container that looks through all its children Route elements to find one that matches the current URL.
    - Route: Maps a specific URL path to a specific React component.
    - Link: A replacement for the standard anchor (<a>) tag; it changes the URL without a page refresh.
    - useParams: A hook used to access dynamic values in the URL (e.g., /user/:id).

- React-router can be installed in `vite` using `npm install react-router-dom`
