# File Uploads and Object Storage

📌 Lighter reference notes, matching Phase 6's "add only when needed" philosophy.

## Why files do not belong in Postgres

Cloud storage types, covered in [`05-databases-and-storage.md`](../0%20Concepts/05-databases-and-storage.md), already named this pitfall: storing large files as binary blobs inside a relational database bloats the database, slows backups and wastes expensive, structured storage that is not built for large binary content.

```
Wrong:  Postgres stores the actual image bytes in a column
Right:  Object storage (S3-style) stores the file, Postgres stores just the URL/key pointing to it
```

## Object storage, the shape

```
User uploads avatar.png
      |
      v
Your API receives it, uploads it to object storage (e.g. S3, Cloudflare R2)
      |
      v
Object storage returns a URL (or a key you build a URL from)
      |
      v
Postgres stores just that URL, in the User row
```

```prisma
model User {
  id        Int    @id @default(autoincrement())
  email     String @unique
  avatarUrl String?   // just a link, the actual file lives in object storage
}
```

## A minimal upload flow in Express

```bash
npm install multer @aws-sdk/client-s3
```

```ts
import multer from "multer";
const upload = multer({ storage: multer.memoryStorage() });

app.post("/users/avatar", requireAuth, upload.single("avatar"), async (req, res) => {
  const file = req.file; // { buffer, mimetype, originalname, ... }
  const url = await uploadToObjectStorage(file);
  await prisma.user.update({ where: { id: req.userId }, data: { avatarUrl: url } });
  sendSuccess(res, { avatarUrl: url });
});
```

`multer` is middleware that parses `multipart/form-data` requests (the format file uploads use), the same middleware role covered in the Phase 1 middleware file, just handling a different kind of request body than `express.json()` does.

## Direct upload, a common real-world variation

For larger files, routing every byte through your own server (as above) wastes bandwidth and server time. A common pattern instead: your server generates a temporary, pre-signed URL, the client uploads directly to object storage using that URL, your server never touches the file bytes at all.

```
Client asks your API: "I want to upload a file"
      |
      v
Your API generates a pre-signed URL (proves this specific upload is authorized)
      |
      v
Client uploads the file directly to object storage, using that URL
      |
      v
Client tells your API the upload finished, your API saves the resulting URL
```

📌 Worth knowing this pattern exists, it is the more scalable real-world approach, though the simpler "route through your server" version above is a fine starting point for a learning project.

## When AlgoRift would need this

Nothing in Phases 0 to 5 requires file uploads. A user avatar, or attaching an image to a problem description, are the natural first real reasons to reach for this, exactly matching the roadmap's own examples ("avatars, attachments").

## Key takeaways

- Files belong in object storage (S3-style), never as binary blobs inside Postgres, the database only stores the resulting URL.
- `multer` parses multipart file upload requests, the same middleware pattern used everywhere else in Express, applied to a different content type.
- Pre-signed direct uploads (client uploads straight to storage) scale better than routing every file through your own server, worth knowing exists even before you need it.
