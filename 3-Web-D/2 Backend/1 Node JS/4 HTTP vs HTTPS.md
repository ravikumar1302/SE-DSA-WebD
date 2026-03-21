# HTTP vs HTTPS

## HTTP (HyperText Transfer Protocol)

- Data sent in **plain text** (not secure)
- Uses port **80**
- In Node.js: use `http` module

    ```
    const http = require("http");
    ```

## HTTPS (HTTP Secure)

- Data is **encrypted (SSL/TLS)**
- Uses port **443**
- Requires **SSL/TLS certificate**
- In Node.js: use `https` module

    ```
    const https = require("https");
    ```

## SSL Certificate (important point)

- Issued by a **Certificate Authority (CA)**
- Contains **public key + server identity**
- Enables **encryption & trust**
- Needed to create HTTPS server in Node.js:

    ```
    const options = {
        key: fs.readFileSync("key.pem"),
        cert: fs.readFileSync("cert.pem"),
    };
    ```

## Key Difference

- HTTP = ❌ no encryption
- HTTPS = ✅ encrypted + uses SSL certificate

## Best Practice

- Always use **HTTPS** in production 🔒
