#include "Graph.h"

Graph::Graph() {}

void Graph::addPathFromCSV(const string &csvPath)
{
    ifstream file(csvPath);
    if (!file.is_open()) {
        cerr << "Error opening CSV file: " << csvPath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> tokens;
        tokens.push_back("start");   

        stringstream ss(line);
        string item;

        while (getline(ss, item, ',')) {
            // trim spaces
            item.erase(0, item.find_first_not_of(" \t"));
            item.erase(item.find_last_not_of(" \t") + 1);
            tokens.push_back(item);
        }

        addPath(tokens);
    }

    file.close();
}

void Graph::addPath(const vector<string> &path)
{
    if (path.size() < 2)
        return;

    for (size_t i = 0; i < path.size() - 1; i++)
    {
        const string &u = path[i];
        const string &v = path[i + 1];


        if (!adj.count(u)) adj[u] = {};
        if (!adj.count(v)) adj[v] = {};


        auto &nbrs = adj[u];
        if (find(nbrs.begin(), nbrs.end(), v) == nbrs.end()) {
            nbrs.push_back(v);
        }
    }
}


void Graph::dfsUtil(const string &node, unordered_set<string> &visited, vector<string> &result)
{
    visited.insert(node);
    result.push_back(node);

    for (auto &nb : adj[node])
    {
        if (!visited.count(nb))
            dfsUtil(nb, visited, result);
    }
}

vector<string> Graph::dfs(const string &start)
{
    vector<string> result;
    unordered_set<string> visited;

    if (adj.count(start))
        dfsUtil(start, visited, result);

    return result;
}

vector<string> Graph::bfs(const string &start)
{
    vector<string> result;
    if (!adj.count(start))
        return result;

    unordered_set<string> visited;
    queue<string> q;

    q.push(start);
    visited.insert(start);

    while (!q.empty())
    {
        string node = q.front();
        q.pop();
        result.push_back(node);

        for (auto &nb : adj[node])
        {
            if (!visited.count(nb))
            {
                visited.insert(nb);
                q.push(nb);
            }
        }
    }

    return result;
}

vector<string> Graph::shortestPath(const string &src, const string &dest)
{
    vector<string> path;
    if (!adj.count(src) || !adj.count(dest))
        return path;

    unordered_map<string, string> parent;
    unordered_set<string> visited;
    queue<string> q;

    q.push(src);
    visited.insert(src);
    parent[src] = "";

    while (!q.empty())
    {
        string node = q.front();
        q.pop();

        if (node == dest)
            break;

        for (auto &nb : adj[node])
        {
            if (!visited.count(nb))
            {
                visited.insert(nb);
                parent[nb] = node;
                q.push(nb);
            }
        }
    }

    if (!parent.count(dest))
        return {};

    for (string cur = dest; cur != ""; cur = parent[cur])
        path.push_back(cur);

    reverse(path.begin(), path.end());
    return path;
}

vector<string> Graph::getNeighbors(const string &node) const
{
    if (!adj.count(node)) 
        return {};

    return adj.at(node);
}


void Graph::printGraph()
{
    for (auto &p : adj)
    {
        cout << p.first << " -> ";
        for (auto &nb : p.second)
            cout << nb << " ";
        cout << "\n";
    }
}
