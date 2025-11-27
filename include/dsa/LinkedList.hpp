#pragma once

/**
 * @file LinkedList.hpp
 * @brief A comprehensive Singly Linked List implementation in C++17
 * @author Neel Patel
 * @version 1.0.0
 * @date 2025
 * 
 * Features:
 * - Template-based for any data type
 * - Iterator support for range-based for loops
 * - Exception handling
 * - Move semantics
 * - Copy semantics
 */

#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <functional>
#include <memory>

namespace dsa {

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        
        explicit Node(const T& value) : data(value), next(nullptr) {}
        explicit Node(T&& value) : data(std::move(value)), next(nullptr) {}
    };
    
    Node* head_;
    Node* tail_;
    size_t size_;

public:
    // Iterator class for range-based for loops
    class Iterator {
    private:
        Node* current_;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        explicit Iterator(Node* node) : current_(node) {}
        
        reference operator*() const { return current_->data; }
        pointer operator->() { return &(current_->data); }
        
        Iterator& operator++() {
            current_ = current_->next;
            return *this;
        }
        
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.current_ == b.current_;
        }
        
        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.current_ != b.current_;
        }
    };
    
    // Constructors & Destructor
    LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
    
    LinkedList(std::initializer_list<T> init) : LinkedList() {
        for (const auto& item : init) {
            push_back(item);
        }
    }
    
    // Copy constructor
    LinkedList(const LinkedList& other) : LinkedList() {
        for (Node* curr = other.head_; curr; curr = curr->next) {
            push_back(curr->data);
        }
    }
    
    // Move constructor
    LinkedList(LinkedList&& other) noexcept 
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }
    
    // Copy assignment
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            for (Node* curr = other.head_; curr; curr = curr->next) {
                push_back(curr->data);
            }
        }
        return *this;
    }
    
    // Move assignment
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    
    ~LinkedList() { clear(); }
    
    // Iterators
    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }
    
    // Capacity
    [[nodiscard]] bool empty() const { return size_ == 0; }
    [[nodiscard]] size_t size() const { return size_; }
    
    // Element access
    T& front() {
        if (empty()) throw std::out_of_range("List is empty");
        return head_->data;
    }
    
    T& back() {
        if (empty()) throw std::out_of_range("List is empty");
        return tail_->data;
    }
    
    T& at(size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of bounds");
        Node* curr = head_;
        for (size_t i = 0; i < index; ++i) curr = curr->next;
        return curr->data;
    }
    
    // Modifiers
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head_;
        head_ = newNode;
        if (!tail_) tail_ = head_;
        ++size_;
    }
    
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail_) {
            tail_->next = newNode;
            tail_ = newNode;
        } else {
            head_ = tail_ = newNode;
        }
        ++size_;
    }
    
    void pop_front() {
        if (empty()) throw std::out_of_range("List is empty");
        Node* temp = head_;
        head_ = head_->next;
        delete temp;
        --size_;
        if (empty()) tail_ = nullptr;
    }
    
    void pop_back() {
        if (empty()) throw std::out_of_range("List is empty");
        if (size_ == 1) {
            delete head_;
            head_ = tail_ = nullptr;
        } else {
            Node* curr = head_;
            while (curr->next != tail_) curr = curr->next;
            delete tail_;
            tail_ = curr;
            tail_->next = nullptr;
        }
        --size_;
    }
    
    void insert(size_t index, const T& value) {
        if (index > size_) throw std::out_of_range("Index out of bounds");
        if (index == 0) { push_front(value); return; }
        if (index == size_) { push_back(value); return; }
        
        Node* curr = head_;
        for (size_t i = 0; i < index - 1; ++i) curr = curr->next;
        Node* newNode = new Node(value);
        newNode->next = curr->next;
        curr->next = newNode;
        ++size_;
    }
    
    void erase(size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of bounds");
        if (index == 0) { pop_front(); return; }
        
        Node* curr = head_;
        for (size_t i = 0; i < index - 1; ++i) curr = curr->next;
        Node* toDelete = curr->next;
        curr->next = toDelete->next;
        if (toDelete == tail_) tail_ = curr;
        delete toDelete;
        --size_;
    }
    
    void clear() {
        while (!empty()) pop_front();
    }
    
    // Algorithms
    void reverse() {
        Node *prev = nullptr, *curr = head_, *next = nullptr;
        tail_ = head_;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head_ = prev;
    }
    
    [[nodiscard]] bool contains(const T& value) const {
        for (Node* curr = head_; curr; curr = curr->next) {
            if (curr->data == value) return true;
        }
        return false;
    }
    
    template<typename Predicate>
    Node* find_if(Predicate pred) {
        for (Node* curr = head_; curr; curr = curr->next) {
            if (pred(curr->data)) return curr;
        }
        return nullptr;
    }
    
    // Utility
    void print() const {
        std::cout << "[";
        for (Node* curr = head_; curr; curr = curr->next) {
            std::cout << curr->data;
            if (curr->next) std::cout << " -> ";
        }
        std::cout << "]" << std::endl;
    }
};

} // namespace dsa
