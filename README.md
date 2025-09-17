# Mini In-Memory Database (C++)

A multi-threaded, persistent, Redis-like in-memory database implemented in C++.

## Features

- **In-memory key-value store**
- **Persistence**: Append-Only File (AOF) ensures durability
- **Networking**: TCP server, multiple clients supported
- **Multi-threaded**: Each client handled concurrently
- **Commands supported**: `SET key value`, `GET key`, `DEL key`, `EXIT`
- **Unit tested** with Catch2 framework
- **Build system**: CMake

## Getting Started

### Prerequisites

- C++17 or later
- CMake >= 3.10
- macOS/Linux

### Build & Run

```bash
mkdir build
cd build
cmake ..
make
./inmemory-db
