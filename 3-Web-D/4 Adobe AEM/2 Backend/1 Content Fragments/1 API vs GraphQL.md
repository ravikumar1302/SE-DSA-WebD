# API vs GraphQL

<br><img src="../../Images/CF_API_vs_GraphQL.png" alt="Content Fragment API vs GraphQL" width="40%" style="display: block; margin: auto;"><br>

✅ Preferred Approach
| Scenario | Recommendation |
| -------------------------------------- | ----------------------------- |
| AEM traditional site (HTL/Sling) | API (URL-based) |
| Headless or omnichannel delivery | GraphQL (schema-based) ✅ |
| Building a decoupled SPA | GraphQL ✅ |
| Need flexible, frontend-driven queries | GraphQL ✅ |
| Need tight control from backend | API (custom servlet/JSON) |

1. **API (URL-Based)**

    - Example: http://localhost:4502/content/wknd/us/en.myServlet.json
    - This approach typically uses custom servlets or Sling Models exposed via JSON. It’s straightforward and works well for traditional or hybrid AEM sites.

    ✅ Pros:

    - Simple to implement
    - Direct URL access
    - Good for server-side rendering or internal services

    ❌ Cons:

    - Tightly coupled to content paths
    - Over-fetching/under-fetching issues
    - Less flexible for headless delivery
    - No built-in schema validation

2. **GraphQL (Schema-Based Query)**

    - Example:

    ```
        {
    faqList {
        items {
        question
        answer {
            plaintext
        }
        }
    }
    }
    ```

    - This uses AEM's GraphQL Content Services, which are model-based and designed for headless content delivery.

    ✅ Pros:

    - Ideal for headless (mobile apps, React, Vue, etc.)
    - Only fetch the fields you need (efficient)
    - Strongly typed schema (auto-generated from models)
    - Easy filtering, pagination, relationships
    - Works seamlessly with Content Fragments

    ❌ Cons:

    - Requires GraphQL setup (models, endpoints)
    - Learning curve for teams unfamiliar with GraphQL
    - Needs persisted queries for security in production

3.
