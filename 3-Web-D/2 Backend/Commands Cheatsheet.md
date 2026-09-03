# Commands Cheatsheet

Every command used across the backend phases, in one place. Explanations live in the phase notes, this file is for looking things up while coding.

## Project setup

```bash
npm init -y                                  # create package.json
npm install -D typescript tsx @types/node    # TypeScript + dev runner + Node types
npx tsc --init                               # create tsconfig.json
npm install express dotenv                   # Express + env file loader
npm install -D @types/express                # Express type definitions
```

## npm scripts

```json
{
  "scripts": {
    "dev": "tsx watch src/index.ts",
    "build": "tsc",
    "start": "node dist/index.js",
    "postinstall": "prisma generate"
  }
}
```

```bash
npm run dev      # development, auto-reloads on save
npm run build    # compile src/*.ts into dist/*.js, run before deploying
npm start        # run the compiled app, this is what production uses
```

## TypeScript

```bash
npx tsc                    # compile once, using tsconfig.json
npx tsc --noEmit           # type-check only, no output files, useful in CI
npx tsc --watch            # recompile on every save
npx tsx src/index.ts       # run a .ts file directly, no build step
```

## Prisma

```bash
npm install -D prisma                    # CLI, dev dependency
npm install @prisma/client               # the client your app imports
npx prisma init                          # create prisma/schema.prisma and .env entry

npx prisma migrate dev --name <name>     # DEVELOPMENT: create + apply a migration, regenerate client
npx prisma migrate deploy                # PRODUCTION: apply existing migrations only
npx prisma generate                      # regenerate the client after pulling schema changes
npx prisma studio                        # open a visual data browser in the browser
npx prisma db push                       # push schema without a migration file, prototyping only
npx prisma migrate status                # show which migrations have and have not been applied
```

⚠️ `migrate dev` never runs against production. `migrate deploy` is the production command.

## Testing endpoints with curl

```bash
# GET
curl http://localhost:3000/problems

# GET with query params (quote the URL when it has & in it)
curl "http://localhost:3000/problems?difficulty=easy&page=2&limit=10"

# POST with a JSON body
curl -X POST http://localhost:3000/problems \
  -H "Content-Type: application/json" \
  -d '{"title":"Two Sum","description":"...","difficulty":"easy"}'

# PUT / PATCH
curl -X PUT http://localhost:3000/problems/1 \
  -H "Content-Type: application/json" \
  -d '{"difficulty":"medium"}'

# DELETE
curl -X DELETE http://localhost:3000/problems/1

# authenticated request
curl http://localhost:3000/submissions \
  -H "Authorization: Bearer <token>"

# show response headers and status code
curl -i http://localhost:3000/problems

# show only the status code
curl -o /dev/null -s -w "%{http_code}\n" http://localhost:3000/problems
```

## Auth and security packages

```bash
npm install zod                                   # runtime validation, infers TS types
npm install bcrypt && npm install -D @types/bcrypt        # password hashing
npm install jsonwebtoken && npm install -D @types/jsonwebtoken   # JWT
npm install cors && npm install -D @types/cors            # CORS headers
npm install express-rate-limit                     # rate limiting
```

## Environment variables

```bash
# .env, never committed
PORT=3000
DATABASE_URL="postgresql://user:password@host.neon.tech/db?sslmode=require"
JWT_SECRET=a-long-random-string
```

```bash
node -e "console.log(require('crypto').randomBytes(48).toString('hex'))"   # generate a strong secret
```

```
# .gitignore, confirm these before the first commit
node_modules
dist
.env
```

## Git

```bash
git status                       # what is staged and untracked, check before committing
git add .
git commit -m "message"
git push -u origin main
git log --oneline -10            # recent commits, compact
```

## Deploy (Railway)

```bash
npm i -g @railway/cli            # optional CLI
railway login
railway link                     # connect the local folder to an existing project
railway run npx prisma migrate deploy    # run a command using the project's env vars
railway logs                     # stream production logs
```

Build command: `npm run build`. Start command: `npm start`. Environment variables are set in the Railway dashboard, never in a committed file.

## Advanced topics

```bash
npm install ioredis              # Redis client, for caching
npm install bullmq               # background job queue
npm install multer @aws-sdk/client-s3    # file uploads to object storage
npm install socket.io            # WebSockets
npm install -D vitest supertest  # testing
```

```bash
docker build -t algorift-backend .                       # build an image
docker run -p 3000:3000 --env-file .env algorift-backend # run a container locally
docker-compose up                                        # run app plus local services together
```

## Quick reference: which command in which situation

| Situation | Command |
|---|---|
| Starting work for the day | `npm run dev` |
| Changed `schema.prisma` | `npx prisma migrate dev --name <what changed>` |
| Pulled someone else's schema change | `npx prisma generate` |
| Want to look at the data | `npx prisma studio` |
| About to deploy | `npm run build`, confirm it passes |
| New migrations exist and production is behind | `npx prisma migrate deploy` |
| Production is broken | `railway logs` |
