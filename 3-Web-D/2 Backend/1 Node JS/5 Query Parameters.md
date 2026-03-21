# Query Parameters

It is Key-value pairs after `?` in URL. E.g., `/users?age=25&city=mumbai`

## Purpose

- Modify/filter data, not identify resource
- Used to pass optional data from client → server
- Used for : filtering, sorting, pagination, search
    - Filtering → /users?age=25
    - Sorting → /products?sort=price
    - Pagination → /users?page=2&limit=10
    - Search → /items?q=phone

## Access (Node.js core)

```
const { URL } = require("url");
const myUrl = new URL(req.url, `http://${req.headers.host}`);

const age = myUrl.searchParams.get("age");
```

## Type Reality

- Everything is string : `?page=2 → "2"`
- Convert explicitly: `const page = Number(myUrl.searchParams.get('page'));`

## Key Distinction from Route Params

- Query params → optional modifiers (`/users?age=25`)
- Route params → resource identity (`/users/25`)

| Feature  | Query Params        | Route Params      |
| -------- | ------------------- | ----------------- |
| Location | After `?`           | Inside path       |
| Example  | `/users?id=10`      | `/users/10`       |
| Use      | Filtering, optional | Resource identity |

## Best Practices

- Validate input : `const page = Number(req.query.page) || 1;`
- Set defaults
- Never trust query params (user-controlled)
- Sanitize for DB queries (avoid injection issues)

## Mental model:

- URL = Resource + Modifiers
- `Path = what` ? `Query = how/filter`
