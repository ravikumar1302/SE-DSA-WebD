# WebSockets and Realtime

📌 Lighter reference notes, matching Phase 6's "add only when needed" philosophy.

## The limitation of normal HTTP

Every HTTP request/response pair covered so far (Phase 1 onward) follows one pattern: the client asks, the server answers, the connection then closes. The server can never initiate contact, it can only ever reply to something the client asked first.

```
Normal HTTP:
Client: "any update?"  -> Server: "no"
Client: "any update?"  -> Server: "no"      <- repeated polling, wasteful
Client: "any update?"  -> Server: "yes, accepted!"
```

This is exactly the polling situation named at the end of [Background Jobs and Queues](1%20Background%20Jobs%20and%20Queues.md), checking a submission's status by asking repeatedly.

## What a WebSocket is

A WebSocket is a different kind of connection: after an initial handshake (which does start as a normal HTTP request), it stays open, and either side, client or server, can send a message to the other at any time, without the client needing to ask first.

```
Normal HTTP:  request -> response -> connection closes, repeat every time
WebSocket:    one handshake -> connection stays open -> either side sends messages, anytime
```

```
Client                              Server
  |----- connect (handshake) ------> |
  | <---- connection open ---------- |
  |                                   |
  |          (later, no request needed)
  | <---- "submission 42: accepted" -|   <- server pushes this on its own
```

## When to reach for it

Live submission status updates (named directly in the roadmap) is the natural AlgoRift example: instead of the client repeatedly polling `GET /submissions/42`, the server pushes "accepted" the moment the background worker finishes, immediately, with no wasted requests in between.

Other common cases: chat applications, live notifications, collaborative editing (seeing someone else's cursor move in real time), live dashboards.

| | Polling | WebSockets |
|---|---|---|
| Who initiates each update | The client, by asking again | The server, the moment something changes |
| Delay before the client sees an update | Up to one polling interval | Near instant |
| Requests when nothing changed | Wasted, still sent and answered | None, no message unless there is something to send |
| Setup complexity | Simple, plain HTTP | An extra connection type and server setup |
| Good fit | Occasional or non-urgent updates | Frequent or time-sensitive updates |

📌 If "checking every few seconds is good enough" genuinely describes your use case, plain polling is simpler and often the right call. Reach for WebSockets specifically when near-instant updates actually matter to the user experience.

## A minimal shape with Socket.IO

```bash
npm install socket.io
```

```ts
import { Server } from "socket.io";
import http from "http";

const server = http.createServer(app); // wraps your existing Express app
const io = new Server(server, { cors: { origin: allowedOrigins } });

io.on("connection", (socket) => {
  console.log("A client connected:", socket.id);

  socket.on("disconnect", () => {
    console.log("Client disconnected:", socket.id);
  });
});

server.listen(PORT); // note: server.listen, not app.listen, now that Socket.IO wraps it
```

## Pushing an update from the background worker

```ts
// inside the submission worker, once the job finishes
io.to(`user-${userId}`).emit("submission-updated", { submissionId, status: "accepted" });
```

```ts
// when a client connects, join a "room" scoped to their own user id
socket.on("join", (userId: number) => {
  socket.join(`user-${userId}`);
});
```

"Rooms" let you push a message to exactly the right connected client (or group of clients), rather than broadcasting every update to everyone connected.

## On the Next.js frontend side

```ts
import { io } from "socket.io-client";

const socket = io(process.env.NEXT_PUBLIC_API_URL!);
socket.emit("join", userId);
socket.on("submission-updated", (data) => {
  // update UI immediately, no polling needed
});
```

## Key takeaways

- A WebSocket connection stays open after its initial handshake, letting the server push messages to the client without the client asking first, unlike normal request/response HTTP.
- Live submission status is the roadmap's own named use case, replacing repeated polling with an instant push the moment a background job finishes.
- Reach for this when near-instant updates genuinely matter to the experience, plain polling is simpler and often good enough otherwise.
