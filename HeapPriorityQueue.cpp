#include "HeapPriorityQueue.h"
#include <iostream>

// Constructor: Initialize size to 0
HeapPriorityQueue::HeapPriorityQueue() : size(0) {}

// Destructor: No dynamic memory, so no cleanup needed
HeapPriorityQueue::~HeapPriorityQueue() {}

// Copy Constructor: Copy heap elements and size
HeapPriorityQueue::HeapPriorityQueue(const HeapPriorityQueue& other) {
    size = other.size;
    for (int i = 0; i < size; ++i) {
        heap[i] = other.heap[i];
    }
}

// Copy Assignment Operator: Assign heap elements and size
HeapPriorityQueue& HeapPriorityQueue::operator=(const HeapPriorityQueue& other) {
    if (this != &other) {
        size = other.size;
        for (int i = 0; i < size; ++i) {
            heap[i] = other.heap[i];
        }
    }
    return *this;
}

// Enqueue: Insert new PrinterJob(str, priority) while maintaining heap order using percolateUp
void HeapPriorityQueue::enqueue(const string& str, int priority) {
    if (size >= MAX_SIZE) {
        cout << "Heap is full. Cannot enqueue more jobs.\n";
        return;
    }

    // Insert the new job at the end of the heap
    heap[size] = PrinterJob(str, priority);
    percolateUp(size);
    size++;
}

// Print and remove PrinterJobs from the heap in priority order using percolateDown
void HeapPriorityQueue::printJobs() {
    if (size == 0) {
        cout << "No jobs in the queue.\n";
        return;
    }

    cout << "Printing jobs in priority order:\n";
    while (size > 0) {
        // Print the job with the highest priority (root of the heap)
        cout << heap[0].printString << " (Priority: " << heap[0].priority << ")\n";

        // Move the last element to the root and reduce the size
        heap[0] = heap[size - 1];
        size--;

        // Restore heap order
        percolateDown(0);
    }
}

// PercolateUp: Maintain heap order when inserting a new PrinterJob
void HeapPriorityQueue::percolateUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap[index] < heap[parentIndex]) {
            // Swap with parent if the current node has higher priority
            swap(heap[index], heap[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

// PercolateDown: Maintain heap order when removing a PrinterJob
void HeapPriorityQueue::percolateDown(int index) {
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        // Find the smallest among the current node and its children
        if (leftChild < size && heap[leftChild] < heap[smallest]) {
            smallest = leftChild;
        }
        if (rightChild < size && heap[rightChild] < heap[smallest]) {
            smallest = rightChild;
        }

        // If the smallest is not the current node, swap and continue
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}