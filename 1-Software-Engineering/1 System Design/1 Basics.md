# System Design : Basics

<br><img src="../Images/System_Design.png" alt="System Design" width="60%" style="display: block; margin: auto;"><br>

## 1. Horizontal Scaling (Scale Out)

    a) Definition: Adding more machines/instances to handle increased load.
    b) Key Points:
        - ➕ Add more servers to distribute traffic
        - ➕ Better fault tolerance (if one fails, others continue)
        - ➕ Good for distributed systems & microservices
        - ➕ Practically unlimited scaling
        - ➖ Requires load balancer (e.g., NGINX)
        - ➖ More complex system design (data consistency, networking)
    c) Example: Adding more app servers behind a load balancer.

## 2 Vertical Scaling (Scale Up)

    a) Definition: Increasing resources (CPU, RAM, storage) of a single machine.
    b) Key Points:
        - ➕ Simple to implement
        - ➕ No major architecture changes
        - ➕ Easier data consistency
        - ➖ Hardware limit exists
        - ➖ Single point of failure
        - ➖ Downtime often required for upgrades
    c) Example: Upgrading a database server from 8GB RAM to 64GB RAM.

## Quick Comparison

| Feature                       | Horizontal       | Vertical                 |
| ----------------------------- | ---------------- | ------------------------ |
| Scaling Method                | Add machines     | Add power to one machine |
| Fault Tolerance               | High             | Low                      |
| Limit                         | Almost unlimited | Hardware limit           |
| Complexity                    | High             | Low                      |
| Cost Efficiency (large scale) | Better           | Expensive at high scale  |

## 💡 Rule of Thumb

    a) Start with vertical scaling (early stage systems)
    b) Move to horizontal scaling for high-traffic, large-scale systems
