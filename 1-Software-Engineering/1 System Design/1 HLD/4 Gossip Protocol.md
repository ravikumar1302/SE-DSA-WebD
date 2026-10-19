# Gossip Protocol

- A peer-to-peer communication protocol where nodes randomly talk to a few other nodes to spread information — like rumor spreading
- Used in large distributed systems for state dissemination and failure detection

### Basic Idea

Each node:

- Periodically selects a few random peers
- Shares its state (heartbeat, metadata, membership info)
- Peers merge and propagate further
- Spreads in O(log N) rounds.

### Core Use Cases

- Cluster membership
- Failure detection
- Configuration updates
- Distributed databases

- Used in systems like:
    - Apache Cassandra
    - Amazon DynamoDB
    - HashiCorp (Serf/Consul)

### How Failure Detection Works

- Each node sends periodic heartbeats
- If heartbeat not received → mark as suspected
- If still no response → mark as dead
- Status spreads via gossip

### Types of Gossip

- Push – Node sends updates
- Pull – Node requests updates
- Push-Pull – Most common (efficient & fast convergence)

### Why It Scales

- No central coordinator
- Low per-node bandwidth
- Eventually consistent
- Fault tolerant
- Each node only talks to a few peers → scales to thousands of nodes.

### Trade-offs

| Pros                   | Cons                      |
| ---------------------- | ------------------------- |
| Highly scalable        | Eventually consistent     |
| Fault tolerant         | Temporary inconsistencies |
| Simple & decentralized | Network overhead          |
