# Kubernetes

📌 Lighter reference notes, matching Phase 7's "know it exists" philosophy.

## What problem it solves

Once a system has many containers (maybe several microservices, each with multiple running copies for reliability), someone or something has to decide: which physical machine runs which container, what happens when one crashes, how traffic reaches the right one, how to add more copies under load. Doing this by hand does not scale past a small number of containers.

Kubernetes (often shortened to "K8s") is a system that manages all of this automatically, given a description of what you want running.

```
You describe:  "run 3 copies of the submissions service, restart any that crash,
                give them a shared internal address, scale to 6 copies if CPU load is high"
      |
      v
Kubernetes handles: placing containers on machines, restarting failures,
                     load balancing between copies, scaling up/down automatically
```

## Why Railway does not need this, for AlgoRift

Railway (the Phase 5 deploy target) is a managed platform that already handles "run my container, restart it if it crashes, give it a public URL" for you, without you ever touching Kubernetes directly. Kubernetes becomes relevant specifically when you are running many services, need to precisely control how they are placed and scaled or a managed platform's built-in behavior is not flexible enough for your specific needs.

| | Railway-style managed platform | Kubernetes |
|---|---|---|
| Setup effort | Very low, mostly automatic | High, real learning curve |
| What it's good for | A small number of services (often just one) | Coordinating many services and containers together |
| Who typically uses it directly | Individual developers, small teams, learning projects | Larger engineering organizations running many microservices |
| AlgoRift's actual need for it | None, at any point on the roadmap | Would only appear if AlgoRift were split into many microservices (previous file) AND outgrew a managed platform's limits |

## The core concepts, briefly

```
Pod        - the smallest deployable unit, usually one container (sometimes a small group)
Deployment - describes how many copies (replicas) of a Pod should be running
Service    - a stable internal address that routes to whichever Pod copies are currently healthy
Cluster    - the whole set of machines Kubernetes is managing together
```

```
Deployment: "3 replicas of the submissions Pod"
      |
      v
  Pod   Pod   Pod      <- Kubernetes keeps exactly 3 running, replacing any that crash
   |     |     |
   └─────┴─────┘
       Service          <- a stable address, load-balances across the 3 Pods automatically
```

## A minimal shape (for recognition, not for building)

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: submissions-service
spec:
  replicas: 3
  template:
    spec:
      containers:
        - name: submissions
          image: your-registry/submissions:latest
          ports:
            - containerPort: 3000
```

This describes "run 3 copies of this container image, on port 3000 each", Kubernetes takes it from there, deciding placement, handling restarts and exposing it internally.

## When it would actually become relevant to you

Not while AlgoRift stays a monolith on Railway, at any point on the roadmap. It would become a real question only if all of the following became true together: AlgoRift genuinely split into several independently deployed services, the number of services grew large enough that manual coordination became painful and a managed platform's own scaling/orchestration features stopped being flexible enough.

## Key takeaways

- Kubernetes automates running, scaling and healing many containers across many machines, a coordination problem that only exists once you have many containers to coordinate.
- A managed platform (Railway) already solves "run my container reliably" for a single app or a small number of services, without needing Kubernetes at all.
- Pods, Deployments and Services are the core building blocks, worth recognizing the shape even without deploying anything on it.
- For AlgoRift specifically, this stays a "know it exists" concept unless the project genuinely grows into many independently scaled services first.
