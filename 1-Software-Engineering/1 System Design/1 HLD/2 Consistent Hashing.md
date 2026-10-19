# Consistent Hashing

- **Hashing**
    - Hashing is the process of converting input data (of any size) into a fixed-size value using a mathematical function called a hash function
    - The output is called a hash value or hash code
    - Example : hash("hello") → 5d41402abc4b2a76b9719d911017c592

    - Why We Use Hashing
        - Fast Data Lookup : Used in hash tables (e.g., HashMap) for O(1) average lookup time.
        - Data Integrity : Verify if data changed (common in file verification).
        - Password Storage : Store hash instead of raw passwords for security.
        - Distributed Systems : Used in sharding & consistent hashing.

- **Consistent Hashing**
    - It is a distributed systems technique used to distribute data across multiple servers (nodes) such that adding or removing a server causes minimal data movement
    - Simply, this hashing distributes data across servers in a way that minimizes remapping when servers are added or removed

- **Pros**
    - Minimal Data Movement : When a node is added/removed, only a small portion of keys are reassigned. Great for scalable systems
    - Horizontal Scalability : You can add nodes without reshuffling the entire dataset. Used in systems like: Amazon DynamoDB, Apache Cassandra
    - Decentralized (No Central Coordinator) : Each client can independently compute where data should go
    - High Availability : If one node fails, only its keys move to the next node clockwise
    - Works Well for Distributed Caching : Common in distributed cache setups like Memcached

- **Cons**
    - Uneven Load Distribution : Without virtual nodes, some servers may handle more keys than others
    - More Complex Implementation : Compared to simple hash(key) % N, it requires: Ring management, Node tracking, Virtual node handling
    - Hotspot Risk : If certain keys are very popular, the assigned node may get overloaded
    - Rebalancing Cost Still Exists : Though minimal, adding/removing nodes still causes: Data movement, Network I/O, Temporary performance degradation

- **Trade-offs**
  | Factor | Consistent Hashing | Simple Modulo Hashing |
  | -------------- | ------------------- | --------------------- |
  | Node Addition | Minimal reshuffling | Almost full reshuffle |
  | Implementation | More complex | Very simple |
  | Load Balancing | Needs virtual nodes | Naturally uniform |
  | Scalability | High | Poor |

- **When to Use**
    - Use consistent hashing when:
        - You expect frequent node scaling
        - You need distributed caching or sharding
        - Data movement cost is high
    - Avoid when:
        - Node count is fixed
        - Simplicity is more important than elasticity

## Consistent Hashing vs Load Balancer

- Load balancers distribute traffic among servers, while consistent hashing distributes data among nodes
- Load balancers handle request routing; consistent hashing handles data placement
- Consistent Hashing distributes data across servers based on a key, ensuring minimal reshuffling when nodes are added or removed
- A Load Balancer distributes incoming traffic across servers to balance request load, without deciding where data is stored.
- In short: Consistent hashing = data placement; Load balancer = traffic routing

| Aspect          | Consistent Hashing                | Load Balancer                              |
| --------------- | --------------------------------- | ------------------------------------------ |
| Purpose         | Data placement                    | Request routing                            |
| Used In         | Distributed storage/cache         | Web/app tier                               |
| State           | Key-based deterministic mapping   | Usually dynamic routing                    |
| When Node Added | Minimal data reshuffle            | Just start sending traffic                 |
| Example         | Amazon DynamoDB, Apache Cassandra | NGINX, HAProxy, AWS Elastic Load Balancing |

## What if Hash function chagnes

- If the hash function changes, the output for the same key changes

- What Happens?
    - Old: hash_v1(key) → Node A
    - New: hash_v2(key) → Node C
- So almost all keys get remapped to different nodes

- What About Already Hashed Data?
    - It becomes misplaced under the new hash function
    - That means:
        - Lookups will fail (data not found on expected node)
        - You must rehash and migrate all existing data
        - This can cause large data movement and downtime

- Impact
    - Changing the hash function in: Apache Cassandra, Amazon DynamoDB would require major rebalancing

- How Systems Handle This
    - Avoid changing hash functions in production
    - Use versioned hashing (gradual migration)
    - Run old + new hash functions in parallel
    - Rebalance data in the background

- Key Takeaway
    - Changing the hash function effectively reshuffles the entire system — similar to changing the number of buckets in simple hashing

- That’s why hash functions are chosen very carefully and rarely changed in distributed systems
