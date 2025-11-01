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
    }

    int pop(int weightArr[]) {
        if (size == 0)
        {
            return -1; // placeholder for empty heap
        }
        int smallest = data[0]; // Smallest index is the root
        data[0] = data[size - 1]; // Replacing root with last element
        size--;
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
                swap(data[pos], data[parentPos]);
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
            int leftChild = 2 * pos + 1;
            int rightChild = 2 * pos + 2;
            int smallest = leftChild;

            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[leftChild]])
                {
                    smallest = data[rightChild];
                }
            if (weightArr[data[pos]] <= weightArr[data[smallest]])
            {
                break;
            }
            swap(data[pos], data[smallest]);
            pos = smallest; // Moving down the tree
        }
    }
};

#endif