# HTTP Anatomy

Every backend framework, Express included, is just a structured way to handle HTTP requests and send HTTP responses. Before touching Express, it helps to know exactly what a request and response actually contain.

## The request-response cycle

```
Client (browser, app, curl)
      |
      |  HTTP Request
      v
  Your Server
      |
      |  HTTP Response
      v
Client receives it
```

One request always gets exactly one response. The client waits (unless it chooses not to) until the response arrives.

## Parts of an HTTP request

```
POST /api/problems HTTP/1.1
Host: localhost:3000
Content-Type: application/json
Authorization: Bearer eyJhbGciOi...

{
  "title": "Two Sum",
  "difficulty": "easy"
}
```

| Part | Example above | What it is |
|---|---|---|
| Method | `POST` | The action being requested |
| Path | `/api/problems` | Which resource on the server |
| Headers | `Content-Type`, `Authorization` | Metadata about the request |
| Body | The JSON object | The actual data being sent, not present on every request |

## HTTP methods

| Method | Meaning | Typical use |
|---|---|---|
| `GET` | Read data | Fetch a list or a single item, never changes data |
| `POST` | Create data | Add a new resource |
| `PUT` | Replace data | Update a resource by replacing it entirely |
| `PATCH` | Partially update data | Update only some fields of a resource |
| `DELETE` | Remove data | Delete a resource |

⚠️ **Pitfall**: `GET` requests should never change data on the server. A `GET /problems/5/delete` endpoint looks convenient but breaks a basic HTTP rule, browsers and tools may pre-fetch `GET` links, accidentally triggering the delete.

### PUT vs PATCH

```
PUT /problems/5
{ "title": "New Title", "description": "New Desc", "difficulty": "easy" }
→ replaces the whole problem, missing fields may get wiped

PATCH /problems/5
{ "title": "New Title" }
→ updates only the title, everything else stays as it was
```

## Where data lives in a request

| Location | Example | Used for |
|---|---|---|
| Route params | `/problems/:id` → `id` | Identifying a specific resource |
| Query params | `/problems?difficulty=easy&page=2` | Filtering, sorting, pagination |
| Body | JSON sent with `POST`/`PUT`/`PATCH` | The actual data being created or updated |
| Headers | `Authorization`, `Content-Type` | Metadata: auth tokens, content format, custom info |

This gets its own detailed file later in this folder, since typing and reading each one correctly in Express is a common source of beginner bugs.

## Naming resources, nouns not verbs

A REST URL names a **resource** (a thing: a user, a problem, a submission), the HTTP method is what carries the action. Putting a verb into the URL itself duplicates what the method already says, and breaks the pattern.

```
Bad, verbs in the URL:            Good, nouns only, method carries the action:
GET  /getUsers                     GET    /users
POST /createUser                   POST   /users
GET  /deleteUser/5                 DELETE /users/5
```

```
/problems      -> the collection of all problems
/problems/5    -> one specific problem, id 5
```

📌 **Rule of thumb**: if a URL contains a verb, the method is very likely wrong or missing. `/users` plus `POST` already means "create a user", writing `/createUser` says the same thing twice, one of them badly.

## Parts of an HTTP response

```
HTTP/1.1 201 Created
Content-Type: application/json

{
  "id": 5,
  "title": "Two Sum",
  "difficulty": "easy"
}
```

| Part | Example above | What it is |
|---|---|---|
| Status code | `201` | A number telling the client what happened |
| Headers | `Content-Type: application/json` | Tells the client how to interpret the body |
| Body | The JSON object | The actual data being returned, optional |

## Status codes

Status codes are grouped by their first digit.

| Range | Category | Meaning |
|---|---|---|
| 1xx | Informational | Rarely used directly in normal API work |
| 2xx | Success | The request worked |
| 3xx | Redirection | The client should go somewhere else |
| 4xx | Client error | The client did something wrong |
| 5xx | Server error | The server did something wrong |

### The ones you will use constantly

| Code | Name | When to use it |
|---|---|---|
| `200` | OK | Successful `GET`, `PUT` or `PATCH` |
| `201` | Created | Successful `POST` that created something new |
| `204` | No Content | Successful `DELETE`, nothing to send back |
| `400` | Bad Request | The request body/data is invalid |
| `401` | Unauthorized | Not logged in, missing or invalid credentials |
| `403` | Forbidden | Logged in, but not allowed to do this action |
| `404` | Not Found | The resource does not exist |
| `500` | Internal Server Error | Something broke on the server, unexpected |

⚠️ **Pitfall**: returning `200` for every response, including errors, is one of the most common beginner mistakes. The client cannot tell success from failure without checking the body manually. Correct status codes are part of a usable API's basic contract, covered further in [`06-apis.md`](../0%20Concepts/06-apis.md).

### 401 vs 403, the one that trips everyone up

| | 401 Unauthorized | 403 Forbidden |
|---|---|---|
| Meaning | "I don't know who you are" | "I know who you are, but you can't do this" |
| Example | Missing or invalid login token | Logged in, but trying to edit someone else's data |
| Fix from client side | Log in again | Nothing to fix, this action is not allowed for this user |

## Key takeaways

- A request has a method, a path, headers and an optional body. A response has a status code, headers and an optional body.
- `GET` never changes data, `POST` creates, `PUT` replaces, `PATCH` partially updates, `DELETE` removes.
- Status codes tell the client what actually happened, using the right one is not optional polish, it is basic API correctness.
- `401` means "who are you", `403` means "I know you, but no".
