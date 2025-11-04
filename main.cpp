//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    MinHeap messageHeap; // 1. Create a MinHeap object.
    for (int i = 0; i < nextFree; i++) // 2. Push all leaf node indices into the heap.
    {
        messageHeap.push(i, weightArr);
    }
    while (messageHeap.size > 1) // 3. While the heap size is greater than 1:
    {
        int leftNodeIndex = messageHeap.pop(weightArr); // Pop first-smallest node
        int rightNodeIndex = messageHeap.pop(weightArr); // Pop second-smallest node
        int parentIndex = nextFree++; // Create a new parent node with combined weight
        weightArr[parentIndex] = weightArr[leftNodeIndex] + weightArr[rightNodeIndex];

        leftArr[parentIndex] = leftNodeIndex; // Set left pointer
        rightArr[parentIndex] = rightNodeIndex; // Set right pointer

        messageHeap.push(parentIndex, weightArr); // Push new parent index back into the heap
    }
    cout << "Encoding Tree built! Total node(s) created: " << messageHeap.size << "\n"; // Test cout for myself. Total nodes should only be 1.
    return (nextFree - 1); // 4. Return the index of the last remaining node (root)
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    stack<pair<int, string>> codesStack; // Use stack<pair<int, string>> to simulate DFS traversal.

    codesStack.push({root, ""}); // Traverse starts at root with empty string, because no turns have been made yet

    // Traversal process starts
    while (!codesStack.empty())
    {
        pair<int, string> current = codesStack.top(); // Get top element from stack
        codesStack.pop(); // Pop root to start iterative traversal

        int currentNodeIndex = current.first;
        string currentCode = current.second;

        // Check if node is a leaf node. Record code when a leaf node is reached.
        if (leftArr[currentNodeIndex] == -1 && rightArr[currentNodeIndex] == -1) // Note to remove 2nd condition = still satisfies heap condition
        {
            char character = charArr[currentNodeIndex];

            //if (character >= 'a' && character <= 'z') // Redundant from buildFrequencyTable & createLeafNodes functions
            //{
                codes[character - 'a'] = currentCode;
            //}
        }
        else // Not a leaf node -> keep traversing
        {
            if (rightArr[currentNodeIndex] != -1) // Right edge adds '1'.
            {
                codesStack.push({rightArr[currentNodeIndex], currentCode + "1"});
            }
            if (leftArr[currentNodeIndex] != -1) // Left edge adds '0'
            {
                codesStack.push({leftArr[currentNodeIndex], currentCode + "0"});
            }
        }
    }
    cout << "Codes have been generated!";
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}