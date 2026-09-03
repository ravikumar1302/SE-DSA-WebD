# HTTP vs HTTPS

Every request and response covered so far in this folder travels over HTTP. This file covers the secure variant, and why production traffic should always use it.

## HTTP

Data travels as plain text, readable by anyone who can intercept the connection (a shared Wi-Fi network, a compromised router, an ISP). Uses port 80 by default.

```
Client  ---- plain text request/response ---->  Server
              anyone on the network path can read this
```

## HTTPS

The same HTTP protocol, wrapped in encryption (TLS, formerly called SSL). Uses port 443 by default, and requires a certificate.

```
Client  ---- encrypted request/response ---->  Server
              readable only by client and server
```

## What a certificate actually does

A certificate is issued by a trusted Certificate Authority (CA) and contains the server's public key plus its verified identity. It does two things at once: enables encryption (the public key is used to set up a secure channel) and proves the server is who it claims to be (a browser warns loudly if a certificate is invalid or missing, exactly the padlock icon warning in every browser).

```
Certificate Authority (CA)
      |
      | issues a certificate for algorift.com
      v
Server presents this certificate to every connecting client
      |
      v
Browser checks: is this certificate valid and issued by a trusted CA?
      |
   yes -----> connection proceeds, encrypted, padlock shown
   no  -----> browser warns the user, blocks or flags the connection
```

## HTTP vs HTTPS

| | HTTP | HTTPS |
|---|---|---|
| Encryption | None, plain text | Yes, TLS/SSL |
| Default port | 80 | 443 |
| Certificate required | No | Yes |
| Browser trust indicator | None special | Padlock icon |
| Safe for passwords, tokens, personal data | No | Yes |

## Where this fits with what has already been built

Every deployment platform covered in the Deploy folder (Railway, and managed platforms generally) provisions HTTPS automatically for the public URL it gives an app, a certificate is issued and renewed without any manual setup. This is exactly why nothing in the Deploy notes mentions certificate files directly, the platform handles it, the same way it handles the underlying server infrastructure.

⚠️ **Where it would matter manually**: running a server directly on a VPS (mentioned in [Where Backends Run](../8%20Deploy/0%20Where%20Backends%20Run.md)) without a managed platform in front of it would mean handling certificates yourself, commonly through a free service like Let's Encrypt, a task a container platform like Railway removes entirely.

## Key takeaways

- HTTPS is HTTP plus encryption (TLS/SSL) and identity verification through a certificate, HTTP sends everything in the open.
- A certificate does two jobs together: enabling encryption and proving the server's identity to the connecting client.
- Managed deployment platforms provision and renew certificates automatically, this is why certificate setup never came up directly in the Deploy folder, it happens behind the scenes on Railway.
- Never send passwords, tokens or personal data over plain HTTP, production traffic should always be HTTPS.
