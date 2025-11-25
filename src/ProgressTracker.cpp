#include "ProgressTracker.h"

ProgressTracker::ProgressTracker(Graph &g)
    : graph(g)
{
}

int ProgressTracker::depthFromStart(const string &node) {
    const string root = "start";

    if (node == root) {
        return 0;
    }

    unordered_set<string> visited;
    queue<pair<string,int>> q; 

    visited.insert(root);
    q.push({root, 0});

    while (!q.empty()) {
        pair<string,int> p = q.front();
        q.pop();
        string cur = p.first;
        int dist = p.second;


        if (cur == node) return dist;

        vector<string> nbrs = graph.getNeighbors(cur);
        for (const string &nb : nbrs) {
            if (!visited.count(nb)) {
                visited.insert(nb);
                q.push({nb, dist + 1});
            }
        }
    }

    return -1; 
}

int ProgressTracker::distToClosestLeaf(const string &node) {
    vector<string> nodeNbrs = graph.getNeighbors(node);
    if (nodeNbrs.empty()) return 0;

    unordered_set<string> visited;
    queue<pair<string,int>> q;
    visited.insert(node);
    q.push({node, 0});

    while (!q.empty()) {
        pair<string,int> p = q.front();
        q.pop();
        string cur = p.first;
        int dist = p.second;


        vector<string> nbrs = graph.getNeighbors(cur);
        if (nbrs.empty()) {
            return dist;
        }

        for (const string &nb : nbrs) {
            if (!visited.count(nb)) {
                visited.insert(nb);
                q.push({nb, dist + 1});
            }
        }
    }

    return -1; 
}

double ProgressTracker::computeProgress(const string &currentNode) {
    int dRoot = depthFromStart(currentNode);   
    if (dRoot < 0) return -1.0; 

    int dToLeaf = distToClosestLeaf(currentNode);
    if (dToLeaf < 0) return -1.0; 

    int var1 = dRoot;
    int var2 = dRoot + dToLeaf;

    if (var2 == 0) {
        return 100.0;
    }

    double progress = (static_cast<double>(var2 - var1) / static_cast<double>(var2)) * 100.0;
    return progress;
}
