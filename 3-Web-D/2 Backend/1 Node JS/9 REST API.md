# What is a REST API ?

## 1. Definition

- REST (Representational State Transfer) is an **architectural style** for designing networked applications (mainly web APIs)
- A REST API allows clients (frontend/mobile) to interact with backend via **HTTP in a standardized way**

- It is based on **resources + representations**
    - 👉 Resource = data (user, product)
    - 👉 Representation = format (usually JSON)

- REST enforces a **uniform interface** → Same rules for all APIs (URLs, HTTP methods, status codes)
- Communication is typically **client-server based** → Frontend and backend are independent systems
- It is **stateless by design** → Server does not store client context between requests
- Uses **standard web protocols (HTTP/HTTPS)** → No custom communication system needed

👉 Not a protocol, not a library → just a **set of design principles**

#### One liner :

> REST API = **standardized way to expose and manipulate resources over HTTP using stateless communication**

---

## 2. Core Idea

- Everything is a **resource** (users, products, orders)
- Each resource is identified by a **URL**

```
/users
/products
/orders
```

👉 API = interface to interact with these resources

---

## 3. HTTP Methods = Actions

| Method | Example     | Meaning               |
| ------ | ----------- | --------------------- |
| GET    | `/users`    | Fetch all users       |
| GET    | `/users/10` | Fetch user with id 10 |
| POST   | `/users`    | Create new user       |
| PUT    | `/users/10` | Replace user          |
| DELETE | `/users/10` | Delete user           |

👉 Same URL, different method → different behavior

---

## 4. Stateless Nature (Important)

- Server does **not store client state**
- Each request must contain all required info

👉 Improves scalability

---

## 5. JSON as Data Format

- Most REST APIs use JSON for communication

```
{
    "id": 1,
    "name": "Ravi"
}
```

## 6. Resource-Based URLs (What you operate on)

- In REST, everything is a **resource (noun, not verb)**

❌ Bad:

```
GET /getUsers
POST /createUser
```

✅ Good:

```
/users
```

👉 Example:

- `/users` → collection
- `/users/10` → specific user

---

## 7. Request + Response Example

### Request

```
POST /users
Content-Type: application/json

{
  "name": "Ravi",
  "age": 24
}
```

### Response

```
{
  "id": 101,
  "name": "Ravi",
  "age": 24
}
```

👉 Client sends data → server processes → returns JSON

---

## 8. REST vs Normal API

| Feature   | REST API          | Random API    |
| --------- | ----------------- | ------------- |
| Structure | Standardized      | Arbitrary     |
| URLs      | Resource-based    | Action-based  |
| Methods   | Proper HTTP usage | Often ignored |

---

## 9. How it connects to Express

Using **Express.js**:

```
app.get("/users", handler);
app.post("/users", handler);
```

👉 Express makes building REST APIs easy

---

## 10. Key Principles (Interview Important)

- Resource-based URLs
- Proper HTTP methods
- Stateless
- Consistent structure

## 11. Express Example (Real Implementation)

Using **Express.js**:

```js
app.get("/users", (req, res) => {
    res.json([{ id: 1, name: "Ravi" }]);
});

app.get("/users/:id", (req, res) => {
    res.json({ id: req.params.id });
});

app.post("/users", (req, res) => {
    res.json({ message: "User created", data: req.body });
});
```

---

## 12. Stateless Example (Important)

❌ Bad (stateful thinking):

```
// server remembers user between requests
```

✅ REST:

```
GET /profile
Authorization: Bearer token123
```

👉 Each request carries its own auth → server doesn’t “remember”

---

## 13. Real-World API Example

E-commerce:

```
GET    /products
GET    /products/5
POST   /orders
DELETE /cart/2
```

👉 Clear, predictable, scalable

## TL;DR

- REST API = **standard way to design backend APIs**
- Uses:
    - URLs → resources
    - HTTP methods → actions

- Stateless + predictable → scalable systems
