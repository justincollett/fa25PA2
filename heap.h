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
        size++; // Increase size
        upheap(size - 1, weightArr); // Moves new element up
    }

    int pop(int weightArr[]) {
        if (size == 0) // Empty heap
        {
            return -1;
        }
        int smallest = data[0]; // Smallest index is at the root
        data[0] = data[size - 1]; // Replacing root with last element
        size--; // Decrease size
        if (size > 1) // Downheap when there's at least 2 nodes for comparison
        {
            downheap(0, weightArr);
        }
        return smallest;
    }

    void upheap(int pos, int weightArr[]) {
        while (pos > 0) // Continues loop while pos is not index 0 (the root)
        {
            int parentPos = (pos - 1) / 2; // Parent index
            if (weightArr[data[pos]] < weightArr[data[parentPos]]) // Compare weights using indices from data array
            {
                swap(data[pos], data[parentPos]); // Swap indices of weightArr
                pos = parentPos; // Move up to position of parent
            }
            else
            {
                break; // If weight of child is not smaller, heap condition is satisfied
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        while (2 * pos + 1 < size) // Existence of a left child
        {
            int leftChild = 2 * pos + 1; // Position of left child
            int rightChild = 2 * pos + 2; // Position of right child
            int smallest = leftChild; // Assume that left child is smallest

            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[leftChild]]) // Check if right child 1) exists and 2) if smaller than left child
                {
                    smallest = rightChild; // Assign rightChild as smallest
                }
            if (weightArr[data[pos]] < weightArr[data[smallest]]) // Heap condition is satisfied
            {
                break;
            }
            swap(data[pos], data[smallest]); // Swap
            pos = smallest; // Moving down the tree
        }
    }
};

#endif