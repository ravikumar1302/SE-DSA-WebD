# Bloom Filters

- A space-efficient probabilistic data structure used to test whether an element is in a set.
    - ✅ If it says NOT present → definitely not present
    - ⚠️ If it says present → might be present (false positive possible)
- No false negatives.

### How It Works

1. Start with a bit array of size m (all 0s)
2. Use k hash functions
3. For each item:
    - Hash it k times
    - Set corresponding bits to 1
4. Lookup:
    - Hash the item k times
    - If any bit = 0 → NOT present
    - If all bits = 1 → Probably present

### Why Use It?

- Extremely memory efficient
- O(1) insert and lookup
- Great for large-scale systems

### Where Used in Real Systems

- Web crawlers (avoid re-crawling URLs)
- Databases (avoid disk lookups)
- Caching systems (check cache existence)
- Distributed systems (membership checks)
- Used by large-scale systems like Google and Apache Cassandra to reduce expensive disk reads.

### Trade-offs

| Pros            | Cons                         |
| --------------- | ---------------------------- |
| Very low memory | False positives              |
| Fast            | Cannot delete easily         |
| Simple          | Size must be planned upfront |

### When to Use

Use Bloom Filter when:

1. Dataset is huge
2. Memory is limited
3. False positives are acceptable
4. False negatives are NOT acceptable
