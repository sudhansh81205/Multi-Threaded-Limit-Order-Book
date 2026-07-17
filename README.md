# Multi-Threaded Limit Order Book

A high-performance C++17 multi-threaded Limit Order Book and Matching Engine implementing price-time priority using a producer-consumer architecture.

## Features

- Multi-threaded producer-consumer architecture
- Thread-safe order queue
- Price-time priority matching
- Buy and Sell order books
- Partial order execution
- Order cancellation
- Order modification
- Trade history
- Persistent trade logging
- FIFO matching within each price level

## Technologies

- C++17
- STL
- std::thread
- std::mutex
- std::condition_variable
- std::atomic

## Project Structure

```
include/
src/
README.md
LICENSE
```

## Matching Logic

The matching engine continuously checks:

Best Buy Price ≥ Best Sell Price

If true:

- Execute trade
- Reduce quantities
- Remove completed orders
- Store trade history
- Log trade to file

## Threading Model

Producer Thread(s)
↓

Thread Safe Queue

↓

Consumer Thread

↓

Matching Engine

↓

Order Book

## Data Structures

| Component | Data Structure |
|------------|----------------|
| Buy Book | map<int, deque<Order>, greater<int>> |
| Sell Book | map<int, deque<Order>> |
| Order Lookup | unordered_map |
| Incoming Orders | ThreadSafeQueue |
| Trade History | vector<Trade> |

## Future Improvements

- Multiple producer threads
- Market Orders
- Stop Orders
- Iceberg Orders
- Order persistence
- REST API
- Benchmarking
- Lock-free queues

## Build

Requires:

- C++17
- GCC 11+ / MSVC 2022 / Clang

```
g++ -std=c++17 *.cpp -pthread
```

## Author

Sudhansh Khandelwal
