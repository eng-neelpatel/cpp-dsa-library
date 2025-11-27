/**
 * @file main.cpp
 * @brief Demo application showcasing the C++ DSA Library
 * @author Neel Patel
 * 
 * Compile with: g++ -std=c++17 -I../include main.cpp -o demo
 */

#include <iostream>
#include <vector>
#include "dsa/LinkedList.hpp"
#include "dsa/BinarySearchTree.hpp"
#include "dsa/Sorting.hpp"

void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "  " << title << "\n";
    std::cout << std::string(50, '=') << "\n\n";
}

void demoLinkedList() {
    printSeparator("LINKED LIST DEMO");
    
    // Create list with initializer list
    dsa::LinkedList<int> list = {10, 20, 30, 40, 50};
    
    std::cout << "Initial list: ";
    list.print();
    
    // Add elements
    list.push_front(5);
    list.push_back(60);
    std::cout << "After push_front(5) and push_back(60): ";
    list.print();
    
    // Insert at position
    list.insert(3, 25);
    std::cout << "After insert(3, 25): ";
    list.print();
    
    // Access elements
    std::cout << "\nFront: " << list.front() << std::endl;
    std::cout << "Back: " << list.back() << std::endl;
    std::cout << "At index 3: " << list.at(3) << std::endl;
    std::cout << "Size: " << list.size() << std::endl;
    
    // Iterator demo
    std::cout << "\nIterating with range-based for: ";
    for (const auto& item : list) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // Reverse
    list.reverse();
    std::cout << "\nAfter reverse: ";
    list.print();
    
    // Contains
    std::cout << "\nContains 25? " << (list.contains(25) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 100? " << (list.contains(100) ? "Yes" : "No") << std::endl;
}

void demoBST() {
    printSeparator("BINARY SEARCH TREE DEMO");
    
    dsa::BinarySearchTree<int> bst = {50, 30, 70, 20, 40, 60, 80};
    
    std::cout << "BST created with: {50, 30, 70, 20, 40, 60, 80}\n";
    bst.print();
    
    std::cout << "\nTree properties:\n";
    std::cout << "  Size: " << bst.size() << std::endl;
    std::cout << "  Height: " << bst.height() << std::endl;
    std::cout << "  Is valid BST? " << (bst.isValid() ? "Yes" : "No") << std::endl;
    
    if (auto min = bst.minimum()) {
        std::cout << "  Minimum: " << *min << std::endl;
    }
    if (auto max = bst.maximum()) {
        std::cout << "  Maximum: " << *max << std::endl;
    }
    
    // Traversals
    std::cout << "\nTraversals:\n";
    
    std::cout << "  Inorder: ";
    for (auto val : bst.inorderTraversal()) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "  Preorder: ";
    for (auto val : bst.preorderTraversal()) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "  Postorder: ";
    for (auto val : bst.postorderTraversal()) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "  Level-order: ";
    for (auto val : bst.levelOrderTraversal()) std::cout << val << " ";
    std::cout << std::endl;
    
    // Search
    std::cout << "\nContains 40? " << (bst.contains(40) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 55? " << (bst.contains(55) ? "Yes" : "No") << std::endl;
    
    // Remove
    bst.remove(30);
    std::cout << "\nAfter removing 30: ";
    bst.print();
}

void demoSorting() {
    printSeparator("SORTING ALGORITHMS DEMO");
    
    std::vector<int> original = {64, 34, 25, 12, 22, 11, 90, 45};
    
    auto printVector = [](const std::string& label, const std::vector<int>& v) {
        std::cout << label << ": ";
        for (int x : v) std::cout << x << " ";
        std::cout << std::endl;
    };
    
    printVector("Original array", original);
    std::cout << std::endl;
    
    // Bubble Sort
    auto arr = original;
    dsa::sort::bubbleSort(arr);
    printVector("Bubble Sort", arr);
    
    // Selection Sort
    arr = original;
    dsa::sort::selectionSort(arr);
    printVector("Selection Sort", arr);
    
    // Insertion Sort
    arr = original;
    dsa::sort::insertionSort(arr);
    printVector("Insertion Sort", arr);
    
    // Merge Sort
    arr = original;
    dsa::sort::mergeSort(arr);
    printVector("Merge Sort", arr);
    
    // Quick Sort
    arr = original;
    dsa::sort::quickSort(arr);
    printVector("Quick Sort", arr);
    
    // Heap Sort
    arr = original;
    dsa::sort::heapSort(arr);
    printVector("Heap Sort", arr);
    
    // Descending order with custom comparator
    arr = original;
    dsa::sort::quickSort(arr, std::greater<int>());
    printVector("\nQuick Sort (descending)", arr);
    
    // Verify sorted
    std::cout << "\nIs ascending sorted? " 
              << (dsa::sort::isSorted(arr, std::greater<int>()) ? "Yes" : "No") << std::endl;
}

int main() {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════════╗\n";
    std::cout << "  ║   C++ DSA Library - Demo Application    ║\n";
    std::cout << "  ║         by Neel Patel                   ║\n";
    std::cout << "  ╚══════════════════════════════════════════╝\n";
    
    demoLinkedList();
    demoBST();
    demoSorting();
    
    printSeparator("DEMO COMPLETE");
    std::cout << "Thank you for using the C++ DSA Library!\n\n";
    
    return 0;
}
