# Docker

📌 Lighter reference notes. [`09-cicd-devops.md`](../0%20Concepts/09-cicd-devops.md) covers the "works on my machine" problem and containers conceptually, this file is the minimal practical version for this stack.

## Why you have not needed Docker yet

Railway (Phase 5) builds and runs your app directly from your GitHub repo, detecting it is a Node project automatically. Neon hosts Postgres separately. Nothing in your setup so far required you to package your own environment, the hosting platforms already handled that for you.

## What a container actually is

A container packages your app together with everything it needs to run (Node version, OS-level dependencies, environment setup) into one predictable, portable unit. It runs the same way on your machine, a teammate's machine or a production server, since the container carries its own environment instead of depending on whatever happens to already be installed on the host.

```
Without Docker: "works on my machine" (different Node version, missing system library, etc.)
With Docker:    the exact same container runs identically, anywhere Docker itself is installed
```

## A minimal `Dockerfile` for this project

```dockerfile
FROM node:20-alpine

WORKDIR /app

COPY package*.json ./
RUN npm install

COPY . .
RUN npx prisma generate
RUN npm run build

CMD ["npm", "start"]
```

| Line | What it does |
|---|---|
| `FROM node:20-alpine` | Start from a small, official Node 20 base image |
| `WORKDIR /app` | Set the working directory inside the container |
| `COPY package*.json ./` then `RUN npm install` | Install dependencies (done before copying the rest of the code, so Docker can reuse this step if only your code changes, not your dependencies) |
| `COPY . .` | Copy the rest of your source code in |
| `RUN npx prisma generate` | Regenerate Prisma Client inside the container |
| `RUN npm run build` | Compile TypeScript, matching [Preparing for Production](../8%20Deploy/1%20Preparing%20for%20Production.md) |
| `CMD ["npm", "start"]` | What runs when the container starts |

## Building and running it locally

```bash
docker build -t algorift-backend .
docker run -p 3000:3000 --env-file .env algorift-backend
```

`docker build` creates the image (the packaged, reusable blueprint). `docker run` starts an actual running container from it, `-p 3000:3000` maps the container's port to your machine's port, `--env-file .env` passes your environment variables in.

## When you would actually reach for this

- Deploying to a platform that expects a container directly, rather than detecting your project type automatically (some VPS setups, some enterprise environments).
- Running Postgres, Redis and your app together locally with one command (`docker-compose`), instead of juggling separately hosted dev services.
- A team environment where "works on my machine" has genuinely caused a real problem, matching containers' whole reason for existing.

## `docker-compose`, a preview

For running multiple services together locally (your app plus a local Postgres and Redis, for example), `docker-compose.yml` describes them all in one file, started together with one command.

```yaml
services:
  app:
    build: .
    ports: ["3000:3000"]
    env_file: .env
  postgres:
    image: postgres:16
    environment:
      POSTGRES_PASSWORD: devpassword
```

```bash
docker-compose up
```

📌 Not needed while using Neon and Railway, since both are already hosted for you. Worth knowing this exists for the day you (or a team) want a fully local, self-contained development environment.

## Key takeaways

- A container packages your app with its exact runtime environment, solving "works on my machine" by making the environment itself part of what ships.
- Railway and Neon already solve the hosting/environment problem for this project, Docker becomes relevant when you need to package the environment yourself, for a different platform or a fully local multi-service setup.
- `docker-compose` runs multiple services (your app, a local Postgres, a local Redis) together with one command, useful for local development independent of any hosted service.
