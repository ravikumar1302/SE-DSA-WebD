# Network Tab Debugging

Whenever a page looks "broken" but no console error appears, the problem is often a request, not the JavaScript. The Network tab shows every request the page made, and everything about each one.

## What each column means

| Column | Shows |
|---|---|
| Name | The request URL (or file) |
| Status | The HTTP status code, see below |
| Type | What kind of request (`fetch`, `xhr`, `doc`, `img`, `script`) |
| Size | How much data came back |
| Time | How long the request took |

Clicking any row opens details with several tabs: Headers (request and response headers, query params), Payload (what was actually sent, for POST/PUT), Response (the raw body that came back), Timing (a breakdown of where time went).

## Reading status codes fast

| Range | Meaning | Common cause when things break |
|---|---|---|
| 2xx | Success | Rarely the problem, but check the body still matches what the frontend expects |
| 3xx | Redirect | Usually fine, but an unexpected redirect can silently change the URL a request lands on |
| 4xx | Client error | Bad request data, missing auth token, wrong URL, resource does not exist |
| 5xx | Server error | The backend crashed or threw an unhandled error, check server logs, not the frontend |

📌 A 4xx means "this request itself is wrong," fixing it usually means fixing what the frontend sent. A 5xx means "the server broke while handling this," the frontend is often innocent, the fix is on the backend.

## Filtering the noise

A real page fires dozens of requests, images, fonts, analytics, tracking pixels. Use the filter bar to narrow down:

- Click "Fetch/XHR" to see only actual API calls, hiding images and static assets.
- Type part of a URL in the filter box to find one specific endpoint.
- The "Status" column can be sorted to spot failed (4xx/5xx) requests instantly among a long list.

## Preserve log, across page navigations

By default, the Network tab clears every time the page navigates or reloads. Checking "Preserve log" keeps the history, essential when a bug involves a redirect or a full page reload, otherwise the exact request that caused it disappears the moment the page changes.

## Throttling, testing on a slow connection

The Network tab has a dropdown (usually says "No throttling") that can simulate Slow 3G, Fast 3G and other speeds. A layout that looks fine on a fast office connection can reveal loading-state bugs, race conditions or a jarring layout shift once actually slow, this is the fastest way to catch those without a real slow device.

## Spotting a CORS error

A CORS failure looks specific: the request shows in the Network tab (sometimes as "failed" or with a status but a red label), and the Console shows a message like:

```
Access to fetch at 'https://api.example.com/data' from origin 'http://localhost:3000'
has been blocked by CORS policy: No 'Access-Control-Allow-Origin' header is present
```

This means the browser received a response but refused to hand it to the JavaScript, because the server did not explicitly allow this origin. It is a server-side configuration problem (the backend needs to allow the frontend's origin), not something fixable from the frontend code. The matching backend-side explanation lives in [CORS](../../2%20Backend/6%20Auth%20Validation%20and%20Security/6%20CORS.md).

## Key takeaways

- The Network tab shows every request, its status, headers, payload and response, the first place to check when a page looks broken with no console error.
- 4xx means the request was wrong, fix the frontend, 5xx means the server broke, fix the backend.
- "Preserve log" keeps request history across navigations and reloads, off by default.
- A CORS error is a server-side configuration issue, the browser is correctly refusing to hand the response to your code.
