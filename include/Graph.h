#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    unordered_map<string, vector<string>> adj;
    Graph();
    void addPath(const vector<string>& path);
    vector<string> bfs(const string&);
    vector<string> dfs(const string&);
    vector<string> shortestPath(const string&, const string&);
    vector<string> getNeighbors(const string &node) const;
    void addPathFromCSV(const string& csvPath);
    void printGraph();

private:
    
    void dfsUtil(const string&, unordered_set<string>&, vector<string>&);
};

#endif
