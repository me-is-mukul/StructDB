#include "MaxHeap.h"


bool MaxHeap::exists(const string& topic) const {
    return freq.find(topic) != freq.end();
}


void MaxHeap::accessTopic(const string& topic) {
    if (!exists(topic)) {
        freq[topic] = 1;
        heap.push_back({topic, 1});
        int index = heap.size() - 1;
        heapIndex[topic] = index;
        heapifyUp(index);
    } 
    else {

        freq[topic]++;
        int index = heapIndex[topic];
        heap[index].second = freq[topic];
        heapifyUp(index);  // Re-adjust heap
    }
}


void MaxHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].second > heap[parent].second) {
            swap(heap[index], heap[parent]);
            heapIndex[heap[index].first] = index;
            heapIndex[heap[parent].first] = parent;
            index = parent;
        } 
        else break;
    }
}


void MaxHeap::heapifyDown(int index) {
    int n = heap.size();
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < n && heap[left].second > heap[largest].second)
            largest = left;
        if (right < n && heap[right].second > heap[largest].second)
            largest = right;

        if (largest == index) break;

        swap(heap[index], heap[largest]);
        heapIndex[heap[index].first] = index;
        heapIndex[heap[largest].first] = largest;
        index = largest;
    }
}


vector<pair<string, int>> MaxHeap::getTopN(int n) const {
    vector<pair<string, int>> result = heap;
    sort(result.begin(), result.end(),
         [](auto &a, auto &b) { return a.second > b.second; });
    if (n < result.size()) result.resize(n);
    return result;
}


int MaxHeap::getFrequency(const string& topic) const {
    if (exists(topic)) return freq.at(topic);
    return 0;
}


void MaxHeap::printHeap() const {
    cout << "\n===== Most Accessed Topics (Heap View) =====\n";
    for (auto &p : heap) {
        cout << p.first << " -> " << p.second << " times\n";
    }
    cout << "===========================================\n";
}
