# Rate Limiting

## 1. Basics

- Rate limiting is a system design technique used to control how many requests a user, client, or service can make within a specific time window
- It protects systems from overload, abuse, and ensures fair usage
- Why It’s Needed
    - 🔒 Prevents abuse (e.g., brute force, spam)
    - ⚡ Protects servers from traffic spikes
    - 🤝 Ensures fair usage among users
    - 💰 Controls API costs

- Rate limiting is Implemented at places like : API Gateways, Load Balancers, Reverse Proxies, Application Layer, Distributed Cache (e.g., Redis)

- Key Design Considerations
    - Granularity: Per IP? Per User? Per API key?
    - Storage: In-memory vs Distributed (Redis)
    - Distributed Systems: Sync counters across instances
    - Fail Strategy: Reject (429 Too Many Requests) or Queue
    - Headers: Return rate limit info in response

- Burst in Rate Limiting : It means a sudden spike of many requests in a very short time. Instead of requests coming evenly spaced, they come all at once

## 2. Common Rate Limiting Algorithms

**Quick Comparison**:
| Algorithm | Accuracy | Memory | Burst Handling |
| --------------- | -------- | ------ | -------------- |
| Fixed Window | Medium | Low | Weak |
| Sliding Log | High | High | Strong |
| Sliding Counter | High | Medium | Strong |
| Token Bucket | High | Low | Controlled |
| Leaky Bucket | Medium | Low | No burst |

### 1. Token Bucket (Most Popular)

- Tokens refill at a constant/fixed rate
- Each request consumes one token
- If no tokens are available, the request is rejected
- Allows controlled bursts
- Advantage: Allows controlled bursts
- Advantage: Efficient and widely used

### 2. Leaky Bucket

- Requests enter a queue (bucket) (It works on Queue Algorithm of DSA)
- Requests processed at a constant/fixed rate
- Smooths traffic
- If the bucket is full, new requests are rejected
- Advantage: Smooths traffic flow
- Disadvantage: Does not allow bursts

### 3. Fixed Window Counting Algorithm

- Count requests in a fixed time window (e.g., 100 requests per minute)
- Reset the counter when the window ends
- Advantage: Simple to implement
- Disadvantage: Allows burst (sudden spike in request) at window boundaries

### 4. Sliding Window Log Algorithm

- Store the timestamp of every request
- Remove timestamps older than the time window
- Allow the request if the count is below the limit
- Advantage: Very accurate
- Disadvantage: High memory usage

### 5. Sliding Window Counting Algorithm

- Combines counts from the current and previous window proportionally
- Reduces the boundary burst issue
- Advantage: More accurate than fixed window
- Advantage: Uses less memory than sliding log
