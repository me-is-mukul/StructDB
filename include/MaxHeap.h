#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <bits/stdc++.h>
using namespace std;

class MaxHeap {
private:
    
    vector<pair<string, int>> heap;
    unordered_map<string, int> freq;
    unordered_map<string, int> heapIndex;

    void heapifyUp(int index);
    void heapifyDown(int index);
    bool exists(const string& topic) const;

public:
    MaxHeap() = default;

    void accessTopic(const string& topic);
    vector<pair<string, int>> getTopN(int n) const;
    int getFrequency(const string& topic) const;
    void printHeap() const;
};

#endif
