# AuthN vs AuthZ, Session vs Token Auth

[`07-security.md`](../0%20Concepts/07-security.md) covers this theory in more depth. This file is the practical version, aimed directly at what you build in Phase 3.

## Authentication vs Authorization

| | Authentication (AuthN) | Authorization (AuthZ) |
|---|---|---|
| Question answered | "Who are you?" | "What are you allowed to do?" |
| Happens | Once, at login | On every action, every request |
| Failure status code | `401 Unauthorized` | `403 Forbidden` |
| AlgoRift example | Logging in with email/password | Only the owner of a submission can delete it |

```
Login request  ---->  Authentication  ---->  "You are user #42"
Every later request  ---->  Authorization  ---->  "Is user #42 allowed to do THIS specific thing?"
```

Authentication happens once and establishes identity. Authorization is checked repeatedly, for every protected action, using that established identity.

## Session-based auth (stateful)

```
1. User logs in with email/password
2. Server creates a session, stores it (in memory/Redis/DB)
3. Server sends the client a session ID in a cookie
4. Every later request includes that cookie automatically
5. Server looks up the session ID, finds the matching user
```

```
Client                          Server
  |---- login ------------------> |
  |                                | creates session, stores it
  | <---- Set-Cookie: sid=abc123 -|
  |                                |
  |---- GET /profile (cookie) --> |
  |                                | looks up session "abc123" -> user #42
  | <---- profile data -----------|
```

The server must keep track of every active session somewhere (memory, Redis, a database table). This is what "stateful" means here, the server holds state about who is logged in.

## Token-based auth (stateless), JWT

```
1. User logs in with email/password
2. Server creates a signed token containing the user's identity
3. Server sends the token to the client
4. Client stores it, sends it with every later request (usually a header)
5. Server verifies the token's signature, trusts what is inside it, no lookup needed
```

```
Client                          Server
  |---- login ------------------> |
  | <---- { token: "eyJhbGci..." }|
  |                                |
  |---- GET /profile               |
  |     Authorization: Bearer eyJ..|
  |                                | verifies signature, reads user id from token
  | <---- profile data -----------|
```

The server does not store anything about active logins. Anyone holding a validly signed token is trusted, this is what "stateless" means, no server-side session state needed to check who is logged in.

## Session vs JWT, compared

| | Session-based | JWT (token-based) |
|---|---|---|
| Server stores login state | Yes | No |
| Scales across multiple servers | Needs shared session storage (Redis) | Naturally, any server can verify the token alone |
| Revoking access immediately | Easy, delete the session | Hard, the token stays valid until it expires |
| Typical storage on client | Cookie | Usually a header, sometimes a cookie |
| Common for | Traditional server-rendered web apps | APIs, especially ones used by mobile apps or separate frontends |

📌 The roadmap picks JWT, matching a Next.js frontend calling a separate Express API, exactly the architecture where token-based auth fits naturally. This is also why your Next.js API routes and this Express backend can share the same stateless auth model.

## Why JWT fits stateless, horizontally scaled backends

[`04-scalability.md`](../0%20Concepts/04-scalability.md) explains statelessness as the enabler of horizontal scaling. Session-based auth needs every server instance to reach the same shared session store. JWT needs nothing shared at all, any server with the correct signing secret can verify any valid token independently.

```
Session-based, multiple servers:            JWT, multiple servers:
Server A ---\                                Server A (verifies alone)
Server B ----> shared session store          Server B (verifies alone)
Server C ---/  (Redis, required)              Server C (verifies alone)
```

## OAuth 2.0, briefly

"Log in with Google" does not use your own password system at all. OAuth lets a user authenticate through a trusted third party (Google, GitHub), which then tells your app "this is a real, verified user, here is their email", without your app ever seeing their Google password.

```
User clicks "Log in with Google"
      |
      v
Redirected to Google, logs in there
      |
      v
Google redirects back to your app with a proof/token
      |
      v
Your app verifies that proof, creates or finds the matching user
```

📌 The roadmap treats this as a later addition, not part of Phase 3's hand-rolled auth. Understanding JWT first makes OAuth far less mysterious later, since most OAuth implementations end up issuing your own app's JWT anyway, after the third-party login succeeds.

## Key takeaways

- Authentication answers "who are you", checked once at login. Authorization answers "what can you do", checked on every protected action.
- Session-based auth is stateful (server tracks active logins), JWT is stateless (server verifies a signed token, no tracking needed).
- JWT fits an API serving a separate frontend, and scales across multiple servers naturally, without shared session storage.
- OAuth delegates identity verification to a trusted third party, it is a separate concern from choosing session vs token auth for your own system.
