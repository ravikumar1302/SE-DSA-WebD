# Practice: Microservices and Distributed Systems

Nothing here is code to add to the project. These are reasoning exercises, because the skill worth having at this level is judging when an architecture is warranted, not implementing one prematurely.

---

### 1. Name your current architecture

Describe the app as built, in architectural terms, in two sentences.

**Done when**: you use the word monolith without treating it as a criticism.

---

### 2. Draw the split

Sketch the app divided into auth, problems and submissions services. Mark what data each owns.

**Done when**: you can point at one piece of data two services both need, which is where the real difficulty lives.

---

### 3. Trace one broken request

In that sketch, the auth service is down. Trace what happens to a request creating a submission.

**Done when**: you can describe the failure in the monolith version too, and say which is easier to debug.

---

### 4. Find the transaction problem

In the split version, a single action must update two services' databases and one fails halfway.

**Done when**: you can explain why one database transaction no longer solves this, and name what teams do instead.

---

### 5. Write the trigger conditions

List the specific, observable symptoms that would justify splitting this app.

**Done when**: every item is a symptom you could measure, not a milestone like "when it gets big."

---

### 6. Translate one endpoint to GraphQL

Take a real route and write the equivalent query and the shape it returns.

**Done when**: you can name one thing that got better and one that got worse.

---

### 7. Decide about caching and GraphQL

Given the same endpoint, explain how HTTP caching changes between REST and GraphQL.

**Done when**: you can state why a single POST endpoint complicates what URLs made easy.

---

### 8. Design one event

Define the event a submission being accepted would publish, and list every service that would react to it.

**Done when**: the publisher's code does not mention any subscriber by name.

---

### 9. Compare the queue you know to a broker

Write out what the existing job queue cannot do that Kafka can.

**Done when**: you can name a concrete scenario where replaying past events actually matters.

---

### 10. Read a contract in another format

Find a real `.proto` file online and map it to the equivalent Express route plus Zod schema.

**Done when**: you can identify where each performs its check, at build time versus at runtime.

---

## Stretch

Pick a company engineering blog post about a migration to microservices. Identify the actual problem they had before the migration. It is almost always organizational rather than technical, and noticing that is the whole lesson of this phase.
