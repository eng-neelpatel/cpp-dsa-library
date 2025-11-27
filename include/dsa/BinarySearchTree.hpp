#pragma once

/**
 * @file BinarySearchTree.hpp
 * @brief A comprehensive Binary Search Tree implementation in C++17
 * @author Neel Patel
 * @version 1.0.0
 * 
 * Features:
 * - Balanced BST operations
 * - Traversals (inorder, preorder, postorder, level-order)
 * - Search, insert, delete operations
 * - Height, size, and validation
 */

#include <iostream>
#include <queue>
#include <functional>
#include <optional>
#include <vector>
#include <algorithm>

namespace dsa {

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        
        explicit Node(const T& value) 
            : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root_;
    size_t size_;
    
    // Helper functions
    Node* insert(Node* node, const T& value) {
        if (!node) {
            ++size_;
            return new Node(value);
        }
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        return node;
    }
    
    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }
    
    Node* findMax(Node* node) const {
        while (node && node->right) node = node->right;
        return node;
    }
    
    Node* remove(Node* node, const T& value) {
        if (!node) return nullptr;
        
        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            // Node found
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                --size_;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                --size_;
                return temp;
            }
            // Two children: get inorder successor
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }
    
    bool search(Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }
    
    int height(Node* node) const {
        if (!node) return -1;
        return 1 + std::max(height(node->left), height(node->right));
    }
    
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    
    bool isValidBST(Node* node, const T* minVal, const T* maxVal) const {
        if (!node) return true;
        if ((minVal && node->data <= *minVal) || 
            (maxVal && node->data >= *maxVal))
            return false;
        return isValidBST(node->left, minVal, &node->data) &&
               isValidBST(node->right, &node->data, maxVal);
    }
    
    // Traversal helpers
    void inorder(Node* node, std::vector<T>& result) const {
        if (node) {
            inorder(node->left, result);
            result.push_back(node->data);
            inorder(node->right, result);
        }
    }
    
    void preorder(Node* node, std::vector<T>& result) const {
        if (node) {
            result.push_back(node->data);
            preorder(node->left, result);
            preorder(node->right, result);
        }
    }
    
    void postorder(Node* node, std::vector<T>& result) const {
        if (node) {
            postorder(node->left, result);
            postorder(node->right, result);
            result.push_back(node->data);
        }
    }

public:
    BinarySearchTree() : root_(nullptr), size_(0) {}
    
    BinarySearchTree(std::initializer_list<T> init) : BinarySearchTree() {
        for (const auto& item : init) insert(item);
    }
    
    ~BinarySearchTree() { clear(); }
    
    // Capacity
    [[nodiscard]] bool empty() const { return size_ == 0; }
    [[nodiscard]] size_t size() const { return size_; }
    [[nodiscard]] int height() const { return height(root_); }
    
    // Modifiers
    void insert(const T& value) { root_ = insert(root_, value); }
    void remove(const T& value) { root_ = remove(root_, value); }
    void clear() { clear(root_); root_ = nullptr; size_ = 0; }
    
    // Lookup
    [[nodiscard]] bool contains(const T& value) const {
        return search(root_, value);
    }
    
    [[nodiscard]] std::optional<T> minimum() const {
        Node* min = findMin(root_);
        return min ? std::optional<T>(min->data) : std::nullopt;
    }
    
    [[nodiscard]] std::optional<T> maximum() const {
        Node* max = findMax(root_);
        return max ? std::optional<T>(max->data) : std::nullopt;
    }
    
    // Traversals
    [[nodiscard]] std::vector<T> inorderTraversal() const {
        std::vector<T> result;
        inorder(root_, result);
        return result;
    }
    
    [[nodiscard]] std::vector<T> preorderTraversal() const {
        std::vector<T> result;
        preorder(root_, result);
        return result;
    }
    
    [[nodiscard]] std::vector<T> postorderTraversal() const {
        std::vector<T> result;
        postorder(root_, result);
        return result;
    }
    
    [[nodiscard]] std::vector<T> levelOrderTraversal() const {
        std::vector<T> result;
        if (!root_) return result;
        
        std::queue<Node*> q;
        q.push(root_);
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            result.push_back(current->data);
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        return result;
    }
    
    // Validation
    [[nodiscard]] bool isValid() const {
        return isValidBST(root_, nullptr, nullptr);
    }
    
    // Print tree structure
    void print() const {
        auto traversal = inorderTraversal();
        std::cout << "BST (inorder): [";
        for (size_t i = 0; i < traversal.size(); ++i) {
            std::cout << traversal[i];
            if (i < traversal.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

} // namespace dsa
