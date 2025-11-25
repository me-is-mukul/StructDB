#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <bits/stdc++.h>
using namespace std;

class MaxHeap {
private:
    // Pair: (topicName, accessCount)
    vector<pair<string, int>> heap;
    unordered_map<string, int> freq;        // topic -> access count
    unordered_map<string, int> heapIndex;   // topic -> index in heap

    void heapifyUp(int index);
    void heapifyDown(int index);
    bool exists(const string& topic) const;

public:
    MaxHeap() = default;

    void accessTopic(const string& topic);        // Increment topic usage
    vector<pair<string, int>> getTopN(int n) const; // Get top N topics
    int getFrequency(const string& topic) const; // Get access count of topic
    void printHeap() const;                     // Show heap content
};

#endif
