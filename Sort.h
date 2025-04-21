#ifndef SORT_H
#define SORT_H

#include <vector>
#include <functional>
using namespace std;

// Generic insertion sort
template <typename T>
void insertionSort(vector<T>& data, function<bool(const T&, const T&)> comp) {
    for (size_t i = 1; i < data.size(); ++i) {
        T key = data[i];
        int j = i - 1;
        while (j >= 0 && comp(key, data[j])) {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = key;
    }
}

// Merge sort

// Merge helper
template <typename T>
void merge(vector<T>& data, int left, int mid, int right, function<bool(const T&, const T&)> comp) {
    vector<T> leftVec(data.begin() + left, data.begin() + mid + 1);
    vector<T> rightVec(data.begin() + mid + 1, data.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;

    while (i < leftVec.size() && j < rightVec.size()) {
        if (comp(leftVec[i], rightVec[j])) {
            data[k++] = leftVec[i++];
        } else {
            data[k++] = rightVec[j++];
        }
    }

    while (i < leftVec.size()) {
        data[k++] = leftVec[i++];
    }
    while (j < rightVec.size()) {
        data[k++] = rightVec[j++];
    }
}

// Recursive merge sort
template <typename T>
void mergeSort(vector<T>& data, int left, int right, function<bool(const T&, const T&)> comp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid, comp);
        mergeSort(data, mid + 1, right, comp);
        merge(data, left, mid, right, comp);
    }
}

template <typename T>
void mergeSort(vector<T>& data, function<bool(const T&, const T&)> comp) {
    if (!data.empty()) {
        mergeSort(data, 0, data.size() - 1, comp);
    }
}

#endif