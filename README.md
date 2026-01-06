# Staque (C++)

A small C++ implementation of a **Staque** (a stack/queue-style container) built on a **doubly linked list**.

This repo focuses on:
- pointer-based list operations
- correct copy behavior (copy constructor / assignment)
- basic usage tests via `main.cpp`

## What’s inside
- `staque.h` / `staque.cpp`: the Staque implementation
- `main.cpp`: simple driver/tests (example usage)

## Build & Run

### with g++
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp staque.cpp -o staque
./staque

Note:
This project was done as part of a university course. Because these are very common assignments, I had to prioritize writing an original solution that wouldn’t trigger plagiarism checks, rather than fully optimizing style or structure.