# 06 - APIs: Design & Management

An **API (Application Programming Interface)** is the contract through which one piece of software talks to another. For backend work, it usually means the HTTP endpoints your server exposes so that frontends, mobile apps, or other services can use it. The API *is* your product's public face to developers - designing it well matters as much as the logic behind it.

💡 **Why it matters:** an API is a **contract**. Once others depend on it, changing it breaks them. Good API design is about making that contract clear, consistent, predictable and stable - so consumers can rely on it and you can evolve it without chaos.

---

## Part A - API styles: REST vs GraphQL vs gRPC

### REST (Representational State Transfer)
The dominant style for web APIs. Not a protocol - a set of *conventions* over HTTP. Core ideas:
- **Resources** are things (users, orders), each with a URL: `/users`, `/users/123`
- **HTTP methods** express the action:
  - `GET` - read (safe, no side effects)
  - `POST` - create
  - `PUT` - replace entirely
  - `PATCH` - update partially
  - `DELETE` - remove
- **Stateless** - each request carries everything needed; the server keeps no client session between calls
- **Status codes** communicate outcome (below)
- Data usually as **JSON**

✅ Simple, universal, cacheable, uses plain HTTP, huge tooling.
❌ **Over-fetching** (endpoint returns more than you need) and **under-fetching** (you must call several endpoints to assemble one screen). Fixed response shapes.

### GraphQL
A query language for APIs. The client asks for **exactly** the fields it wants in **one** request, from a single endpoint.

✅ Solves over/under-fetching - client shapes the response; great for complex, nested data and varied clients (web + mobile wanting different fields).
❌ More complex server setup; caching is harder (it's not just URLs); easy to write expensive queries; overkill for simple APIs.

### gRPC
A high-performance, contract-first RPC framework using Protocol Buffers (binary) over HTTP/2. You call remote *functions*, not resources.

✅ Very fast and compact (binary), strongly typed contracts, streaming, excellent for **service-to-service** communication (microservices).
❌ Not browser-friendly by default, binary (not human-readable), steeper learning curve.

⚖️ **Which style when:**

| | REST | GraphQL | gRPC |
|---|---|---|---|
| Best for | Public/standard web APIs | Complex/varied client data needs | Internal service-to-service |
| Format | JSON (text) | JSON (text) | Protobuf (binary) |
| Fetching | Fixed per endpoint | Client-specified | Fixed per method |
| Learning curve | Low | Medium | Medium-high |
| Caching | Easy (HTTP) | Harder | Custom |
| Human-readable | Yes | Yes | No |

📌 **Default:** learn and use **REST** - it's the backbone of the web, simplest and what most jobs expect. Add GraphQL if client data needs are genuinely complex; use gRPC for internal microservice chatter. (There's also **WebSockets** for realtime/bidirectional - chat, live updates - a different tool for a different job, see file 10.)

---

## Part B - Designing a good REST API

### Resource naming
- Use **nouns**, not verbs: `/users`, not `/getUsers` (the HTTP method is the verb).
- **Plural** collections: `/users`, `/users/123`, `/users/123/orders`.
- Keep it **hierarchical & predictable**: `/users/123/orders/456`.
- Lowercase, hyphenated if needed: `/order-items`.

### Use HTTP status codes correctly
| Range | Meaning | Common ones |
|---|---|---|
| **2xx** | Success | 200 OK, 201 Created, 204 No Content |
| **3xx** | Redirection | 301 Moved, 304 Not Modified |
| **4xx** | Client's fault | 400 Bad Request, 401 Unauthorized, 403 Forbidden, 404 Not Found, 409 Conflict, 422 Unprocessable, 429 Too Many Requests |
| **5xx** | Server's fault | 500 Internal Error, 502 Bad Gateway, 503 Unavailable |

⚠️ **Pitfall:** returning `200 OK` with `{"error": "..."}` inside. Use the status code to signal outcome - clients and tools rely on it. 401 vs 403 matters: **401 = who are you? (not authenticated)**, **403 = I know you, you're not allowed (not authorized)**.

### Consistent response & error shapes
Pick one envelope and use it everywhere:
```json
// success
{ "data": { ... }, "error": null }
// error
{ "data": null, "error": { "code": "VALIDATION_FAILED", "message": "Email is invalid", "details": [...] } }
```
💡 Consistency means the client writes *one* handler for all responses, not a special case per endpoint. Inconsistent APIs are miserable to consume.

### Pagination, filtering, sorting
Never return unbounded lists - a `/users` with a million rows will melt. Support:
- **Pagination:** `?page=2&limit=20` (offset) or cursor-based (`?after=abc`) for large/live data.
- **Filtering:** `?status=active&role=admin`
- **Sorting:** `?sort=-createdAt` (- for descending)
- Return metadata: total count, next-page info.

### Idempotency
An operation is **idempotent** if doing it repeatedly has the same effect as doing it once. `GET`, `PUT`, `DELETE` should be idempotent; `POST` typically isn't (two POSTs = two records). 💡 Matters because networks retry - a retried non-idempotent request can double-charge someone. For critical POSTs, use an **idempotency key** so retries are safe.

### Validation at the boundary
Validate every incoming request (types, required fields, ranges) *before* it touches business logic. Reject bad input early with a clear `400`. (This is also security - file 07. Tools: Zod, Pydantic, Joi.)

---

## Part C - Versioning

Once people depend on your API, you can't just change it. **Versioning** lets you evolve without breaking existing consumers.

- **URL versioning:** `/v1/users`, `/v2/users` - most common, explicit, easy.
- **Header versioning:** version in a request header - cleaner URLs, less visible.

💡 **Breaking vs non-breaking changes:** *adding* a new optional field is safe (non-breaking). *Removing* a field, renaming or changing types breaks consumers - that needs a new version. Design responses to tolerate additive change.

📌 Start at `v1`. Introduce `v2` only for genuinely breaking changes, and give consumers time to migrate (run both for a while, then deprecate v1).

---

## Part D - API management concerns

Beyond raw design, running an API in production involves:

### Authentication & Authorization
Who is calling, and what may they do. **API keys** (simple, per-client), **OAuth 2.0** (delegated access, "log in with Google"), **JWT** (stateless tokens). Full treatment in file 07.

### Rate limiting & throttling
Cap how many requests a client can make per time window (e.g., 100/min). Protects against abuse, runaway scripts and accidental overload; ensures fair use. Exceed it → `429 Too Many Requests`. (Often done at the gateway.)

### API Gateway
A single entry point in front of your API(s) that handles cross-cutting concerns so individual services don't have to:
- Routing requests to the right service
- Authentication & rate limiting in one place
- Request/response transformation, aggregation
- Logging, metrics, caching

💡 Especially valuable with microservices - clients hit one gateway instead of juggling many service URLs. Examples: Kong, AWS API Gateway, Apigee, NGINX.

### Webhooks (APIs in reverse)
Instead of you *polling* someone's API asking "anything new?", they **call your** URL when an event happens ("payment succeeded"). 💡 Efficient and real-time - the provider pushes to you. You expose an endpoint, register its URL and verify incoming calls are authentic (signatures). This is how Stripe, GitHub, etc. notify your app.

### Monitoring & analytics
Track usage, latency, error rates and per-consumer volume (file 09). You can't manage what you can't see.

---

## Part E - API documentation & the OpenAPI standard

An API nobody understands is useless. **Documentation** describes every endpoint: path, method, parameters, request/response shapes, errors, auth.

- **OpenAPI Specification (formerly Swagger)** - a standard, machine-readable format (YAML/JSON) that describes your whole REST API. From it you can **auto-generate** interactive docs, client SDKs and even server stubs.
- **Swagger UI** - renders an OpenAPI spec as interactive, try-it-in-the-browser docs.

💡 **Why it's worth it:** a single source of truth for your API that stays in sync, generates docs and client code and lets consumers explore without reading your source. Treat the spec as part of the contract.

---

## Part F - Tools of the trade

### Postman
The most popular tool for **building, testing and exploring** APIs. You craft requests (method, URL, headers, body, auth), send them, and inspect responses - without writing a frontend.
- **Collections** - save and organize groups of requests
- **Environments** - variables (base URL, tokens) swappable between dev/staging/prod
- **Tests** - scripts that assert on responses (status, fields) → basis for automated API testing
- **Automation/CI** - run collections in pipelines (via Newman) to test APIs on every change
- **Mock servers & docs** - fake an API before it's built; generate documentation

📌 During development you'll live in Postman (or **Insomnia**, a lighter alternative, or **Thunder Client** inside VS Code, or plain **`curl`** in the terminal). Learning to test endpoints independently of any UI is a core backend skill.

### Other API tooling
- **Insomnia / Thunder Client / Hoppscotch** - Postman alternatives
- **curl / HTTPie** - command-line request tools
- **Swagger UI / Redoc** - render API docs from OpenAPI
- **Newman** - run Postman collections in CI

---

## Key takeaways

- An API is a **contract** - consistency, correct status codes and stability are everything.
- **REST** is your default; **GraphQL** for complex client needs; **gRPC** for internal service-to-service.
- Design with **noun resources, correct HTTP methods/status codes, consistent response shapes, pagination and boundary validation.**
- **Version** to evolve without breaking; additive changes are safe, removals aren't.
- Management adds **auth, rate limiting, gateways, webhooks, monitoring**.
- **Document** with OpenAPI/Swagger; **test** with Postman & friends - independent of any frontend.

---

## Where this shows up in the build

| Idea here | Where it becomes real |
|---|---|
| Methods, status codes, resource naming | [HTTP Anatomy](../4%20Express%20Fundamentals/0%20HTTP%20Anatomy.md) |
| Consistent response and error shapes | [Consistent Response and Error Envelope](../7%20API%20Polish/0%20Consistent%20Response%20and%20Error%20Envelope.md) |
| Pagination, filtering, sorting | [Pagination Filtering and Sorting at the API Layer](../7%20API%20Polish/1%20Pagination%20Filtering%20and%20Sorting%20at%20the%20API%20Layer.md) |
| Validation at the boundary | [Validation with Zod](../6%20Auth%20Validation%20and%20Security/0%20Validation%20with%20Zod.md) |
| Rate limiting | [Rate Limiting and Security Basics](../6%20Auth%20Validation%20and%20Security/7%20Rate%20Limiting%20and%20Security%20Basics.md) |
| REST compared to GraphQL and gRPC | [GraphQL](../10%20Microservices%20and%20Distributed%20Systems/2%20GraphQL.md), [gRPC](../10%20Microservices%20and%20Distributed%20Systems/4%20gRPC.md) |

➡️ Next: [`07-security.md`](07-security.md) - because a working API on the internet is an attacked API.
