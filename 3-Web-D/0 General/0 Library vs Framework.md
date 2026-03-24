# 📚 Library vs 🏗️ Framework

## Core Idea

- **Library = tool you call**
- **Framework = environment you work inside**

👉 In simple terms:

- **Library**
    - You control the flow
    - You decide when and how to use it
    - Acts like a toolbox of functions

- **Framework**
    - Controls the flow (**Inversion of Control**)
    - Provides structure/skeleton for your app
    - Your code fits into its system

### 🔥 Simple Memory Trick

- If it gives you **freedom** → Library
- If it gives you **rules + structure** → Framework

---

## 🔁 Control, Architecture & Structure

- **Library**
    - Full control over: Architecture, Folder structure, Lifecycle
    - No enforced rules
    - Example use: call functions when needed

- **Framework**
    - Controls: Request lifecycle. Routing, Bootstrapping, Dependency injection
    - Follows patterns (MVC, MVVM, etc.)
    - You plug into predefined hooks

## 🧩 Reality: They Work Together

👉 Modern development is hybrid:

- Framework = **collection of libraries + rules**
- You rarely use only one

---

## ⚖️ Key Differences That Matter

| Aspect         | Library                                  | Framework                                         |
| -------------- | ---------------------------------------- | ------------------------------------------------- |
| Control        | High on developer side                   | lower (framework leads)                           |
| Structure      | Optional                                 | Enforced                                          |
| Flexibility    | High/ very flexible                      | Moderate                                          |
| Setup          | Fast                                     | Slower                                            |
| Scalability    | Manual (better for custom/small systems) | Built-in patterns (better for large apps & teams) |
| Learning Curve | easy start, harder to scale              | harder start, easier scaling                      |

## 💻 Examples (Merged View)

### 🔹 Frontend

- **Libraries**
    - React → UI building
    - Redux → state
    - Axios → API calls

- **Frameworks**
    - Next.js → routing, SSR, API routes
    - Angular → full structure, Dependency Injection pattern

👉 Difference:

- React → you choose everything
- Next.js/Angular → structure is given

---

### 🔹 Backend (Node.js)

- **Libraries**
    - Mongoose → DB modeling
    - bcrypt → security

- **Frameworks**
    - Express.js → minimal, flexible
    - NestJS → structured, enterprise-ready

👉 Key idea:

- Express → feels like library (less opinionated)
- NestJS → true framework (strict architecture)

---

### 🔹 Python Ecosystem

- **Libraries**
    - NumPy
    - Pandas
    - Requests

- **Frameworks**
    - Django → full-stack
    - Flask → lightweight
    - FastAPI → async + fast

- **ML Frameworks**
    - TensorFlow
    - PyTorch

👉 These define execution flow (training, computation graphs)

---

## 🔥 Final Memory Trick

- **Freedom → Library**
- **Rules → Framework**
