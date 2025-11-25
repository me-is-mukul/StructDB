#ifndef PROGRESS_TRACKER_H
#define PROGRESS_TRACKER_H

#include "Graph.h"
#include <bits/stdc++.h>
using namespace std;

class ProgressTracker {
public:
    ProgressTracker(Graph &g);
    double computeProgress(const string &currentNode);

private:
    Graph &graph;
    int depthFromStart(const string &node);
    int distToClosestLeaf(const string &node);
};

#endif 