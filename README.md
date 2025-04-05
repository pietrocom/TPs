# CI1001 - Programming 1 (UFPR)

A collection of first practical assignments (TP2-TP5) implementing abstract data types (ADTs) in C, focusing on memory management, pointers, and good programming practices.

## 📋 Projects Overview

| TP | Topic                          | Key Concepts                          |
|----|--------------------------------|---------------------------------------|
| 1  | Rational Numbers TAD           | Structs, Makefiles, Basic Ops         |
| 2  | Modified Rational TAD          | Pass-by-reference, Error handling     |
| 3  | Dynamic Rational Numbers       | Memory allocation, Valgrind checks    |
| 4  | Linked List TAD                | Pointer manipulation, List operations |
| 5  | Generic Priority Queue (FPrio) | Void pointers, Generic types          |

## 🛠 Technical Details

- **Language**: C (C90 standard)
- **Tools**: 
  - `make` for compilation
  - `Valgrind` for memory checks
  - `diff` for output verification
- **Key Requirements**:
  - Strict compilation flags (`-Wall -Werror -Wextra`)
  - No memory leaks
  - Adherence to TAD principles
  - Clean code style

## 📂 Repository Structure
/TP2/ # Rational numbers (reference)
/TP3/ # Rational numbers (dynamic)
/TP4/ # Linked list
/TP5/ # Priority queue
├── fprio.h # Header (DO NOT MODIFY)
├── fprio.c # Implementation
├── teste-fprio.c # Test cases
└── makefile

## 🚀 How to Use

1. Navigate to any TP directory
2. Compile: `make`
3. Run tests: `./testa.sh [1|2]` (where applicable)
4. Check memory: `valgrind ./tpX`

## ✅ Key Learning Outcomes

- Memory management in C
- ADT implementation patterns
- Debugging with Valgrind
- Generic programming techniques
- Good coding practices

Developed as part of UFPR's Computer Science curriculum.
