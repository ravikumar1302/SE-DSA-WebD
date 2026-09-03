# gRPC

📌 Lighter reference notes, matching Phase 7's "know it exists" philosophy. [`06-apis.md`](../0%20Concepts/06-apis.md) covers this alongside REST and GraphQL conceptually, this file walks through a direct comparison against a REST + Zod route you already built.

## What gRPC is

A protocol for calling functions on a remote service as if they were local functions, using a compact binary format instead of JSON text, and a strict, pre-defined contract (a `.proto` file) both sides must agree on ahead of time.

```
REST:  client sends JSON text over HTTP, server parses it, both sides trust the shape loosely
gRPC:  client calls a typed function, data is encoded in a compact binary format (Protocol Buffers),
       both sides generated their code from the exact same contract file
```

## Comparing to a route you already built

The Phase 3 login route, in REST:

```ts
// Zod schema, the contract, checked at runtime
const LoginSchema = z.object({ email: z.string().email(), password: z.string() });

app.post("/auth/login", validateBody(LoginSchema), authController.login);
```

The same idea in gRPC's contract-first style, a `.proto` file:

```protobuf
service AuthService {
  rpc Login (LoginRequest) returns (LoginResponse);
}

message LoginRequest {
  string email = 1;
  string password = 2;
}

message LoginResponse {
  string token = 1;
}
```

From this `.proto` file, gRPC tooling generates real client and server code in whichever language each side uses, both sides get compile-time correctness, not the runtime validation Zod provides for REST.

## REST + Zod vs gRPC

| | REST + Zod (what you built) | gRPC |
|---|---|---|
| Contract definition | A Zod schema, checked at runtime | A `.proto` file, code generated for both sides |
| Data format | JSON text, human-readable | Protocol Buffers, compact binary, not human-readable |
| Performance | Good, fine for almost all API needs | Faster, meaningfully so at very high call volumes |
| Browser support | Native, `fetch` just works | Not directly usable from a browser without an extra proxy layer |
| Best fit | Public APIs, anything a browser calls directly | Service-to-service calls, inside your own infrastructure |
| Debuggability | Easy, read the JSON directly (`curl`, Postman) | Harder, binary format needs specific tooling to inspect |

⚠️ Because gRPC is not natively callable from a browser, it is not a REST replacement for anything your Next.js frontend calls directly, gRPC's real use case is calls between your own backend services, not a public-facing API.

## Where gRPC would fit, if AlgoRift ever became several services

If AlgoRift split into microservices (first file in this folder), and the `submissions` service needed to check something with the `auth` service on every request (verifying a token, say), that internal, high-frequency, service-to-service call is exactly gRPC's sweet spot, fast, typed, low overhead. The public-facing API your Next.js frontend calls would very likely stay REST regardless, since browsers cannot call gRPC directly.

```
Next.js frontend  --REST-->  API gateway / public service  --gRPC-->  internal services
                              (what a browser can call)      (fast, internal-only calls)
```

## When this would actually become relevant to AlgoRift

Only once genuinely split into multiple internal services (Phase 7's first topic) with real, frequent service-to-service calls where REST's JSON overhead measurably mattered. Nothing on your actual roadmap reaches that point, your entire API surface stays REST throughout.

## Key takeaways

- gRPC replaces JSON-over-HTTP with a compact binary format and a strict, code-generated contract, trading human-readability and browser support for speed and stronger cross-language type guarantees.
- It is not a replacement for your REST API's public surface, browsers cannot call it directly, its real fit is service-to-service calls inside your own infrastructure.
- Zod (what you actually use) and a `.proto` file solve a related problem, defining and enforcing a contract, at different points: Zod checks at runtime, gRPC's contract is baked into generated code on both sides.
- Relevant only once AlgoRift genuinely becomes several internal services calling each other frequently, not for anything the roadmap actually builds.
