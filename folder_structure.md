# Folder Structure

A high-level map of this repository. Each top-level folder is one learning area.

```
SE-DSA-WebD
├── 1-Software-Engineering
│   ├── 1 System Design            (basics: scaling, CQRS, back of envelope)
│   │   ├── 1 HLD                  (rate limiting, consistent hashing, bloom filters, gossip...)
│   │   └── 2 LLD                  (OOP, SOLID, design patterns, LLD case studies)
│   ├── 2 CS Fundamentals          (Operating Systems, Computer Networks)
│   ├── 3 Testing and Quality
│   ├── 4 Security                 (threat modelling, OWASP, crypto basics, secrets)
│   └── Images
├── 2-DSA
│   ├── 1 C++                      (theory, 20 DSA topics, contests, DSA sheets)
│   ├── 2 Python                   (theory and libraries: numpy, pandas, matplotlib...)
│   ├── 3 Java                     (Core Java)
│   └── 4 SQL                      (theory, LeetCode and HackerRank questions)
├── 3-Web-D
│   ├── 0 General                  (web basics: DNS, hosting, CMS...)
│   ├── 1 Frontend                 (HTML, CSS, Tailwind/Bootstrap, JS, React, Next.js, Debugging)
│   ├── 2 Backend                  (concepts handbook, TypeScript, Express, Postgres/Prisma, auth,
│   │                               API polish, deploy, advanced topics, microservices, debugging)
│   ├── 3 Database                 (SQL, PL/SQL)
│   ├── 4 Adobe AEM                (general, frontend, backend, learning paths)
│   ├── 5 Projects                 (mini projects, local only)
│   ├── 6 Rough or Practice area   (scratch work, local only)
│   └── Images
├── 4-DevOps-and-Cloud
│   ├── 1 Linux and Servers
│   ├── 2 Cloud
│   ├── 3 CI-CD
│   ├── 4 Containers and Orchestration
│   ├── 5 CDN and Caching
│   ├── 6 Observability
│   ├── 7 Backups and Disaster Recovery
│   └── 8 Infrastructure as Code
├── 5-AI-Engineering               (LLM APIs, prompting, RAG, agents, evals)
├── 6-Product-and-Program-Management (agile, estimation, roadmaps, specs, risk, releases, incidents)
└── 7-Other                        (electronics coding basics, local only)
```

Root files: general cheatsheets (`GIT_Workflow.md`, `Comments and Case-Sensitivity.md`, `md file methods.md`), `README.md` and this file.

## Conventions

| Convention | Meaning |
|---|---|
| Number prefix (`1 Arrays`, `2 Backend`) | Suggested reading or learning order |
| `0 Intro.md` | Starting point of a topic folder |
| `N Topic Practice` folder | Solved problems for the matching `N Topic` folder (C++ DSA) |
| `Practice.md` | Exercises at the end of a module (Backend, Debugging) |
| `Problem_Name_Source_Number.cpp` | C++ solution file, for example `Two_Sum_Leetcode_1.cpp` |
| `Images/` | Diagrams (`.webp`) used by the notes in that section |
| Local only | Folder is gitignored and does not appear on GitHub |
