#  Chad CS2010Lab5

# Project 1: Template-based Vector Operations

## Overview
This C++ program demonstrates template-based implementations of various vector and element operations. The program allows for flexible manipulation of vector containers (`VEC<T>`) with elements of any data type (`ELEM<T>`) by using templates for common operations like `map`, `filter`, `reduce`, `zip`, and more. It also showcases the use of functional programming techniques with actions and predicates applied to vectors.

## Features
The program includes the following template-based functions:

- **`printElem`**: Prints elements of a vector, enclosed in parentheses for vectors of size greater than one.
- **`initVec`**: Initializes a vector with a list of values.
- **`printVec`**: Prints a 2D vector with elements in rows and columns.
- **`generate`**: Generates a vector based on a function applied to an integer sequence.
- **`zip`**: Combines two vectors element-wise.
- **`filter`**: Filters elements in the vector based on a predicate function.
- **`map`**: Applies a function to each element in the vector.
- **`reduce`**: Reduces the vector to a single value based on a binary operation.

## Functions and Usage

### Utility Types and Function Templates
The program defines several type aliases to simplify usage:

- `ELEM<T>`: Represents a single-dimensional vector of type `T`.
- `VEC<T>`: Represents a 2D vector (vector of `ELEM<T>`).
- `action_t`, `pred_t`, `map_t`: Function pointers used to pass functions for transformations, predicates, and reductions.

### Example Functions
- `f(int x)`: Squares an integer.
- `g(int x)`: Returns `true` if `x > 0`.
- `h(int x)`: Returns `1` if `x > 0`, otherwise `0`.
- `k(T i, T j)`: Adds two elements.

### Main Execution
The `main` function demonstrates the program’s capabilities:
1. Initializes and prints vectors `v` and `w`.
2. Zips `v` and `w`, then zips the result with itself.
3. Generates a vector of squares using `f`.
4. Filters vector `w` to include only positive values with `g`.
5. Maps vector `w` to binary values (1 or 0) using `h`.
6. Reduces the mapped vector to a single integer with `k`.
7. Demonstrates string and character vector operations for variety.

## Example Output
The program provides example outputs for each operation, showing the step-by-step transformation of the vectors.

## How to Run
To compile and run the program:
```bash
g++ -o Prj1 Prj1.cpp
./Prj1
```

## Requirements
- C++11 or later (for type aliases and lambda support).
