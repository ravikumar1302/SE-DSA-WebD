# Before vs After Express JS

## Routing Example

### ❌ Without Express (Node `http`)

```
const http = require('http');

const server = http.createServer((req, res) => {
  if (req.url === '/' && req.method === 'GET') {
    res.end('Home');
  } else if (req.url === '/about' && req.method === 'GET') {
    res.end('About');
  } else {
    res.statusCode = 404;
    res.end('Not Found');
  }
});

server.listen(3000);
```

👉 Problems:

- Manual `if-else`
- Hard to scale
- No separation of concerns

---

### ✅ With **Express.js**

```
const express = require('express');
const app = express();

app.get('/', (req, res) => res.send('Home'));
app.get('/about', (req, res) => res.send('About'));

app.listen(3000);
```

👉 Benefits:

- Declarative routing
- Clean, readable
- Easily scalable
- Built in **http** and **url** module, so no need to write `const http = require('http');` and `const { URL } = require('url');`
- No need of `http.createServer()`, directly write `app.listen(3000)`

---

## Apart from Routing — Other Benefits of Express

### 1. Middleware System (Biggest Advantage)

- Chain multiple functions per request
- Used for auth, logging, validation, etc

### 2. Built-in Request Parsing

- JSON, URL-encoded data via middleware
- No manual stream handling

### 3. Simplified Response Handling

- `res.send`, `res.json`, `res.status`
- No need for `writeHead`, `end`

### 4. URL & Params Handling

- Easy access using :`req.params`, `req.query`

### 5. Error Handling Mechanism

- Centralized error middleware
- 👉 Cleaner than try-catch everywhere

### 6. Ecosystem (Plugins/Middleware)

- Large ecosystem (e.g., auth, security, logging)
- 👉 Plug-and-play features

### 7. Better Code Organization

- Supports separation:
    - routes
    - controllers
    - middleware

### 8. Faster Development

- Less boilerplate → more focus on logic
- 👉 Industry standard for quick APIs

## Final Insight

> Express doesn’t just simplify routing — it **standardizes backend development patterns** on top of Node
