# CORS

## The problem CORS solves

Browsers enforce a security rule called the **same-origin policy**: a webpage loaded from one origin (domain + protocol + port) cannot, by default, make requests to a different origin using JavaScript running in the browser.

```
Frontend running at:  http://localhost:3001  (Next.js dev server)
Backend running at:   http://localhost:3000  (Express API)

Different port -> different origin -> blocked by default
```

Without any configuration, a `fetch()` call from your Next.js app to your Express API fails, not because the server rejected it, but because the browser itself refuses to hand the response back to your frontend JavaScript.

## What "origin" actually means

An origin is the exact combination of protocol, domain and port.

| URL A | URL B | Same origin? |
|---|---|---|
| `http://localhost:3000` | `http://localhost:3001` | No, different port |
| `http://localhost:3000` | `https://localhost:3000` | No, different protocol |
| `https://algorift.com` | `https://api.algorift.com` | No, different subdomain |
| `https://algorift.com/page1` | `https://algorift.com/page2` | Yes, same origin, path does not matter |

## CORS: Cross-Origin Resource Sharing

CORS is a mechanism where the **server** explicitly tells the browser which other origins are allowed to receive its responses, through response headers. The browser reads these headers and decides whether to let your frontend's JavaScript access the response.

```
Browser              Express Server
  |---- request from http://localhost:3001 --->  |
  |                                                |  checks: is this origin allowed?
  |  <---- response with                          |
  |        Access-Control-Allow-Origin header -----|
  |                                                |
  browser checks the header, allows or blocks
  the frontend JS from reading the response
```

⚠️ CORS is enforced by the browser, not the server. A tool like `curl` or Postman ignores CORS entirely, since there is no browser same-origin policy to enforce. This is why "it works in Postman" does not mean "it works from my frontend", they are genuinely different situations.

## Setting up CORS in Express

```bash
npm install cors
npm install -D @types/cors
```

```ts
import cors from "cors";

app.use(cors({
  origin: "http://localhost:3001",   // only this origin is allowed
  credentials: true,                  // allow cookies/auth headers to be sent
}));
```

## CORS options explained

| Option | Meaning |
|---|---|
| `origin` | Which origin(s) may access this API. A string, an array of strings or a function for dynamic logic |
| `credentials` | Whether cookies and the `Authorization` header are allowed across origins |
| `methods` | Which HTTP methods are allowed (defaults to a sensible common set) |

## Doing it properly, not just "allow everything"

```ts
// WRONG for a real app, allows literally any website to call your API
app.use(cors({ origin: "*" }));
```

⚠️ **Pitfall**: `origin: "*"` (allow any origin) defeats the purpose of CORS as a security boundary. Any website on the internet could then make authenticated requests to your API from a user's browser. This is explicitly called out in the roadmap as "CORS done properly", meaning a specific, intentional origin list, not a wildcard.

```ts
const allowedOrigins = [
  "http://localhost:3001",         // local Next.js dev
  "https://algorift.vercel.app",   // deployed frontend
];

app.use(cors({
  origin: (origin, callback) => {
    if (!origin || allowedOrigins.includes(origin)) {
      callback(null, true);
    } else {
      callback(new Error("Not allowed by CORS"));
    }
  },
  credentials: true,
}));
```

The `!origin` check allows requests with no origin header at all (server-to-server calls, some mobile clients, `curl`), a normal and expected case, since CORS only exists to restrict browser-originated requests.

## Preflight requests, briefly

For certain requests (custom headers like `Authorization`, methods beyond simple `GET`/`POST`), the browser first sends an automatic `OPTIONS` request, called a **preflight**, asking "would this actual request be allowed?" before sending the real one.

```
Browser              Server
  |--- OPTIONS (preflight) --->  |
  | <--- allowed headers/methods -|
  |
  |--- actual POST request ----> |   (only sent if preflight succeeded)
```

The `cors` middleware handles responding to preflight requests automatically, you do not need to write this logic yourself.

## Where CORS fits in your middleware pipeline

```ts
app.use(cors(corsOptions));   // early, before routes
app.use(express.json());
app.use(logger);
// ...routes
```

Registering it early ensures every route, including error responses, carries the correct CORS headers.

## Key takeaways

- CORS lets a server explicitly allow specific other origins to access its responses from browser JavaScript, it is enforced by the browser, not the server.
- `origin: "*"` allows any website to call your API from a browser, avoid it, list specific allowed origins instead.
- `credentials: true` is needed if your frontend sends cookies or relies on the `Authorization` header across origins.
- Tools like `curl`/Postman bypass CORS entirely, since it is a browser-only restriction, do not use them alone to confirm CORS is configured correctly for your actual frontend.
