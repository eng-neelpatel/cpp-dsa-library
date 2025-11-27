#pragma once

/**
 * @file Sorting.hpp
 * @brief Comprehensive sorting algorithms collection in C++17
 * @author Neel Patel
 * @version 1.0.0
 * 
 * Includes: Bubble, Selection, Insertion, Merge, Quick, Heap Sort
 * All algorithms support custom comparators
 */

#include <vector>
#include <functional>
#include <algorithm>
#include <utility>

namespace dsa {
namespace sort {

// Bubble Sort - O(n^2)
template <typename T, typename Compare = std::less<T>>
void bubbleSort(std::vector<T>& arr, Compare comp = Compare()) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (comp(arr[j + 1], arr[j])) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Optimization
    }
}

// Selection Sort - O(n^2)
template <typename T, typename Compare = std::less<T>>
void selectionSort(std::vector<T>& arr, Compare comp = Compare()) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (comp(arr[j], arr[minIdx])) minIdx = j;
        }
        if (minIdx != i) std::swap(arr[i], arr[minIdx]);
    }
}

// Insertion Sort - O(n^2), good for small/nearly sorted arrays
template <typename T, typename Compare = std::less<T>>
void insertionSort(std::vector<T>& arr, Compare comp = Compare()) {
    for (size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && comp(key, arr[j])) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort - O(n log n)
namespace detail {
    template <typename T, typename Compare>
    void merge(std::vector<T>& arr, int left, int mid, int right, Compare comp) {
        std::vector<T> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        
        while (i <= mid && j <= right) {
            temp[k++] = comp(arr[i], arr[j]) ? arr[i++] : arr[j++];
        }
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];
        
        for (int p = 0; p < k; ++p) arr[left + p] = temp[p];
    }
    
    template <typename T, typename Compare>
    void mergeSort(std::vector<T>& arr, int left, int right, Compare comp) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, comp);
            mergeSort(arr, mid + 1, right, comp);
            merge(arr, left, mid, right, comp);
        }
    }
}

template <typename T, typename Compare = std::less<T>>
void mergeSort(std::vector<T>& arr, Compare comp = Compare()) {
    if (arr.size() > 1) {
        detail::mergeSort(arr, 0, static_cast<int>(arr.size()) - 1, comp);
    }
}

// Quick Sort - O(n log n) average, O(n^2) worst
namespace detail {
    template <typename T, typename Compare>
    int partition(std::vector<T>& arr, int low, int high, Compare comp) {
        T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (comp(arr[j], pivot)) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    
    template <typename T, typename Compare>
    void quickSort(std::vector<T>& arr, int low, int high, Compare comp) {
        if (low < high) {
            int pi = partition(arr, low, high, comp);
            quickSort(arr, low, pi - 1, comp);
            quickSort(arr, pi + 1, high, comp);
        }
    }
}

template <typename T, typename Compare = std::less<T>>
void quickSort(std::vector<T>& arr, Compare comp = Compare()) {
    if (arr.size() > 1) {
        detail::quickSort(arr, 0, static_cast<int>(arr.size()) - 1, comp);
    }
}

// Heap Sort - O(n log n)
namespace detail {
    template <typename T, typename Compare>
    void heapify(std::vector<T>& arr, int n, int i, Compare comp) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && comp(arr[largest], arr[left])) largest = left;
        if (right < n && comp(arr[largest], arr[right])) largest = right;
        
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest, comp);
        }
    }
}

template <typename T, typename Compare = std::less<T>>
void heapSort(std::vector<T>& arr, Compare comp = Compare()) {
    int n = static_cast<int>(arr.size());
    
    // Build heap
    for (int i = n / 2 - 1; i >= 0; --i) {
        detail::heapify(arr, n, i, comp);
    }
    
    // Extract elements
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        detail::heapify(arr, i, 0, comp);
    }
}

// Utility: Check if array is sorted
template <typename T, typename Compare = std::less<T>>
bool isSorted(const std::vector<T>& arr, Compare comp = Compare()) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (comp(arr[i], arr[i - 1])) return false;
    }
    return true;
}

} // namespace sort
} // namespace dsa
