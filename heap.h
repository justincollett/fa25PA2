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
        if (size >= 64)
        {
            return; // Full heap
        }
        data[size] = idx; // Insert index at end of heap
        size++;
        upheap(size - 1, weightArr); // Moves new element up
        // TODO: insert index at end of heap, restore order using upheap()
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        while (pos > 0) // Continues loop while pos is not index 0 (the root)
        {
            int parentPos = (pos - 1) / 2; // Parent index
            if (weightArr[data[pos]] >= weightArr[data[parentPos]]) // Compare weights using indices from data array
            {
                break;
            }
            swap(weightArr[pos], weightArr[parentPos]);

        }
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif