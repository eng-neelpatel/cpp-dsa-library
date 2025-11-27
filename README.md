# C++ Data Structures & Algorithms Library

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg)

A comprehensive, modern C++ library implementing essential data structures and algorithms. Built with C++17 features including templates, iterators, move semantics, and smart design patterns.

## Features

- **Linked List** - Singly linked list with iterator support
- **Binary Search Tree** - BST with multiple traversal algorithms
- **Sorting Algorithms** - 6 different sorting implementations
- **Modern C++17** - Uses latest language features
- **Header-only** - Easy to integrate into any project
- **Well Documented** - Comprehensive code documentation

## Project Structure

```
cpp-dsa-library/
|-- include/
|   |-- dsa/
|       |-- LinkedList.hpp
|       |-- BinarySearchTree.hpp
|       |-- Sorting.hpp
|-- examples/
|   |-- main.cpp
|-- LICENSE
|-- README.md
```

## Quick Start

### Installation

This is a header-only library. Simply copy the `include/dsa` folder to your project or add to include path.

### Basic Usage

```cpp
#include "dsa/LinkedList.hpp"
#include "dsa/BinarySearchTree.hpp"
#include "dsa/Sorting.hpp"

int main() {
    // Linked List
    dsa::LinkedList<int> list = {1, 2, 3, 4, 5};
    list.push_back(6);
    list.reverse();
    
    // Binary Search Tree
    dsa::BinarySearchTree<int> bst = {50, 30, 70, 20, 40};
    auto sorted = bst.inorderTraversal();
    
    // Sorting
    std::vector<int> arr = {64, 34, 25, 12, 22, 11};
    dsa::sort::quickSort(arr);
    
    return 0;
}
```

### Compilation

```bash
g++ -std=c++17 -I./include examples/main.cpp -o demo
./demo
```

## Data Structures

### LinkedList

| Operation | Time Complexity |
|-----------|----------------|
| push_front | O(1) |
| push_back | O(1) |
| pop_front | O(1) |
| pop_back | O(n) |
| insert | O(n) |
| erase | O(n) |
| search | O(n) |
| reverse | O(n) |

### BinarySearchTree

| Operation | Average | Worst |
|-----------|---------|-------|
| insert | O(log n) | O(n) |
| search | O(log n) | O(n) |
| delete | O(log n) | O(n) |
| traversal | O(n) | O(n) |

### Sorting Algorithms

| Algorithm | Best | Average | Worst | Space |
|-----------|------|---------|-------|-------|
| Bubble Sort | O(n) | O(n^2) | O(n^2) | O(1) |
| Selection Sort | O(n^2) | O(n^2) | O(n^2) | O(1) |
| Insertion Sort | O(n) | O(n^2) | O(n^2) | O(1) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick Sort | O(n log n) | O(n log n) | O(n^2) | O(log n) |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) | O(1) |

## Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- No external dependencies

## Author

**Neel Patel**
- GitHub: [@eng-neelpatel](https://github.com/eng-neelpatel)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

---

If you find this library useful, please consider giving it a star!
