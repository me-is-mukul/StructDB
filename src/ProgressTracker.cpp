#include "ProgressTracker.h"

ProgressTracker::ProgressTracker(Graph &g)
    : graph(g)
{
}

int ProgressTracker::depthFromStart(const string &node) {
    const string root = "start";

    if (node == root) return 0;

    const int WHITE = 0;
    const int GRAY  = 1;
    const int BLACK = 2;

    unordered_map<string,int> color;
    unordered_map<string,int> dist;
    unordered_map<string,string> parent;

    queue<string> q;

    color[root]  = GRAY;
    dist[root]   = 0;
    parent[root] = "";
    while (!q.empty()) q.pop();
    q.push(root);

    while (!q.empty()) {
        string u = q.front();
        q.pop();

        vector<string> nbrs = graph.getNeighbors(u);
        for (const string &v : nbrs) {

            if (!color.count(v) || color[v] == WHITE) {
                color[v]  = GRAY;
                dist[v]   = dist[u] + 1;
                parent[v] = u;
                q.push(v);

                if (v == node) return dist[v];
            }
        }

        color[u] = BLACK;
    }

    return -1;
}


int ProgressTracker::distToClosestLeaf(const string &node) {
    const int WHITE = 0;
    const int GRAY  = 1;
    const int BLACK = 2;

    unordered_map<string,int> color;
    unordered_map<string,int> dist;
    unordered_map<string,string> parent;
    queue<string> q;

    color[node]  = GRAY;
    dist[node]   = 0;
    parent[node] = "";   // NIL
    while (!q.empty()) q.pop();
    q.push(node);

    while (!q.empty()) {
        string u = q.front(); q.pop();

        vector<string> nbrs = graph.getNeighbors(u);
        if (nbrs.empty()) {
            return dist[u];
        }

        for (const string &v : nbrs) {
            if (!color.count(v) || color[v] == WHITE) {
                color[v]  = GRAY;
                dist[v]   = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }

        color[u] = BLACK;
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
    }
    
    return 100.0;
    double progress = ((double)(var2 - var1) / (double)(var2)) * 100.0;
    return progress;
}
