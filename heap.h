//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        data[size] = idx; // Insert index at end of heap
        size++;
        upheap(size - 1, weightArr); // Moves new element up
        // TODO: insert index at end of heap, restore order using upheap()
    }

    int pop(int weightArr[]) {
        if (size == 0)
        {
            return -1; // placeholder for empty heap
        }
        int min_idx = data[0]; // Smallest index is the root
        data[0] = data[size - 1]; // Replacing root with last element
        size--;
        downheap(0, weightArr);
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()

    }

    void upheap(int pos, int weightArr[]) {
        while (pos > 0) // Continues loop while pos is not index 0 (the root)
        {
            int parentPos = (pos - 1) / 2; // Parent index
            if (weightArr[data[pos]] < weightArr[data[parentPos]]) // Compare weights using indices from data array
            {
                swap(data[pos], data[parentPos]);
                pos = parentPos; // Move up to position of parent
            }
            break; // If weight of child is not smaller, heap condition is satisfied
        }
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[]) {
        int smallest = pos; // Assuming current node is the smallest
        int leftChild = 2 * pos + 1;
        int rightChild = 2 * pos + 2;

        // Check if there is a left/right Child and if so, if its weight is smaller than current smallest
        if (leftChild < size && weightArr[data[leftChild]] < weightArr[data[smallest]])
        {
            smallest = leftChild;
        }
        if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[smallest]])
        {
            smallest = rightChild;
        }

        if (smallest != pos) {
            swap(data[pos], data[smallest]);
            pos = smallest;
            downheap(pos, weightArr);
        }
        // TODO: swap parent downward while larger than any child
    }
};

#endif