#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <set>
#include <functional>
#include <string>
using namespace std;

// Graph class using adjacency list
class Graph
{
private:
    int V;                                    // number of vertices
    vector<int> nodes;                        // store node IDs
    vector<vector<pair<int, int>>> adj;       // adjacency list: pair<neighbor_index, weight>
    std::function<string(int)> labelProvider; // optional label provider by node ID

    string nodeLabelByIndex(int idx)
    {
        int id = nodes[idx];
        if (labelProvider)
            return labelProvider(id);
        return to_string(id);
    }

public:
    Graph() : V(0) {}

    // Clear the entire graph
    void clear()
    {
        V = 0;
        nodes.clear();
        adj.clear();
    }

    // Set a label provider to display friendly names
    void setLabelProvider(std::function<string(int)> provider)
    {
        labelProvider = std::move(provider);
    }

    // Add a new vertex
    void addVertex(int value)
    {
        nodes.push_back(value);
        adj.push_back(vector<pair<int, int>>());
        V++;
    }

    // Find index of a node
    int getIndex(int value)
    {
        for (int i = 0; i < V; i++)
            if (nodes[i] == value)
                return i;
        return -1; // not found
    }

    // Add edge between two nodes with weight (default 1)
    void addEdge(int u, int v, int weight = 1)
    {
        int i = getIndex(u);
        int j = getIndex(v);
        if (i == -1 || j == -1)
        {
            cout << "Node not found!\n";
            return;
        }
        adj[i].push_back({j, weight});
        adj[j].push_back({i, weight}); // for undirected graph
    }

    // Display graph
    void display()
    {
        for (int i = 0; i < V; i++)
        {
            cout << nodeLabelByIndex(i) << " -> ";
            for (auto &p : adj[i])
            {
                cout << "(" << nodeLabelByIndex(p.first) << "," << p.second << ") ";
            }
            cout << "\n";
        }
    }

    // BFS from start node
    void BFS(int start)
    {
        int s = getIndex(start);
        if (s == -1)
            return;

        vector<bool> visited(V, false);
        queue<int> q;
        visited[s] = true;
        q.push(s);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            cout << nodeLabelByIndex(u) << " ";

            for (auto &p : adj[u])
            {
                int v = p.first;
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << "\n";
    }

    // DFS from start node
    void DFS(int start)
    {
        int s = getIndex(start);
        if (s == -1)
            return;

        vector<bool> visited(V, false);
        stack<int> st;
        st.push(s);

        while (!st.empty())
        {
            int u = st.top();
            st.pop();
            if (!visited[u])
            {
                visited[u] = true;
                cout << nodeLabelByIndex(u) << " ";
            }

            for (auto &p : adj[u])
            {
                int v = p.first;
                if (!visited[v])
                    st.push(v);
            }
        }
        cout << "\n";
    }

    // Dijkstra: shortest path from start node
    void Dijkstra(int start, int end)
    {
        int s = getIndex(start);
        if (s == -1)
            return;

        vector<int> dist(V, numeric_limits<int>::max());
        vector<int> parent(V, -1);
        dist[s] = 0;
        set<pair<int, int>> pq; // {distance, node}
        pq.insert({0, s});

        while (!pq.empty())
        {
            auto it = pq.begin();
            int u = it->second;
            pq.erase(it);

            for (auto &p : adj[u])
            {
                int v = p.first;
                int w = p.second;
                if (dist[u] + w < dist[v])
                {
                    pq.erase({dist[v], v});
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.insert({dist[v], v});
                }
            }
        }

        // Print path from start to end
        int e = getIndex(end);
        cout << "Shortest distance: " << dist[e] << "\n";
        cout << "Path: ";
        vector<int> path;
        int curr = e;
        while (curr != -1)
        {
            path.push_back(curr);
            curr = parent[curr];
        }
        for (int i = path.size() - 1; i >= 0; i--)
            cout << nodeLabelByIndex(path[i]) << " ";
        cout << "\n";
    }

    // Detect cycle in undirected graph using DFS
    bool detectCycleUtil(int u, vector<bool> &visited, int par)
    {
        visited[u] = true;
        for (auto &p : adj[u])
        {
            int v = p.first;
            if (!visited[v])
            {
                if (detectCycleUtil(v, visited, u))
                    return true;
            }
            else if (v != par)
            {
                return true;
            }
        }
        return false;
    }

    bool detectCycle()
    {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                if (detectCycleUtil(i, visited, -1))
                    return true;
        }
        return false;
    }

    // Prim's MST
    void MST()
    {
        vector<bool> inMST(V, false);
        vector<int> key(V, numeric_limits<int>::max());
        key[0] = 0;
        int mstWeight = 0;

        for (int i = 0; i < V - 1; i++)
        {
            int u = -1;
            for (int j = 0; j < V; j++)
            {
                if (!inMST[j] && (u == -1 || key[j] < key[u]))
                    u = j;
            }

            inMST[u] = true;

            for (auto &p : adj[u])
            {
                int v = p.first;
                int w = p.second;
                if (!inMST[v] && w < key[v])
                    key[v] = w;
            }
        }

        cout << "MST Edges:\n";
        for (int i = 1; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                for (auto &p : adj[j])
                {
                    if (p.first == i && inMST[j])
                    {
                        cout << nodeLabelByIndex(j) << " - " << nodeLabelByIndex(i) << " : " << p.second << "\n";
                        mstWeight += p.second;
                        break;
                    }
                }
            }
        }
        cout << "Total MST Weight: " << mstWeight << "\n";
    }
};

#endif
