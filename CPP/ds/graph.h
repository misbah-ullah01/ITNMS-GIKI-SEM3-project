#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "array.h"
#include "pair.h"
#include "queue.h"
#include "stack.h"
using namespace std;

// Define INT_MAX replacement to avoid <limits>
#ifndef INT_MAX_VALUE
#define INT_MAX_VALUE 2147483647
#endif

// Graph class using adjacency list with custom DS
class Graph
{
private:
    int V;                                          // number of vertices
    DynamicArray<int> nodes;                        // store node IDs
    DynamicArray<DynamicArray<Pair<int, int>>> adj; // adjacency list: Pair<neighbor_index, weight>
    string (*labelProvider)(int);                   // function pointer for labels

    string nodeLabelByIndex(int idx)
    {
        int id = nodes[idx];
        if (labelProvider)
            return labelProvider(id);
        return to_string(id);
    }

public:
    Graph() : V(0), labelProvider(nullptr) {}

    // Clear the entire graph
    void clear()
    {
        V = 0;
        // Reset arrays
        while (nodes.size() > 0)
            nodes.erase(nodes.size() - 1);
        while (adj.size() > 0)
            adj.erase(adj.size() - 1);
    }

    // Set a label provider to display friendly names
    void setLabelProvider(string (*provider)(int))
    {
        labelProvider = provider;
    }

    // Add a new vertex
    void addVertex(int value)
    {
        nodes.push_back(value);
        adj.push_back(DynamicArray<Pair<int, int>>());
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
            cout << "Node not found!\\n";
            return;
        }
        adj[i].push_back(Pair<int, int>(j, weight));
        adj[j].push_back(Pair<int, int>(i, weight)); // for undirected graph
    }

    // Display graph
    void display()
    {
        for (int i = 0; i < V; i++)
        {
            cout << nodeLabelByIndex(i) << " -> ";
            for (int k = 0; k < adj[i].size(); k++)
            {
                Pair<int, int> &p = adj[i][k];
                cout << "(" << nodeLabelByIndex(p.first) << "," << p.second << ") ";
            }
            cout << "\\n";
        }
    }

    // BFS from start node
    void BFS(int start)
    {
        int s = getIndex(start);
        if (s == -1)
            return;

        DynamicArray<bool> visited(V);
        for (int i = 0; i < V; i++)
            visited.push_back(false);

        Queue<int> q;
        visited[s] = true;
        q.push(s);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            cout << nodeLabelByIndex(u) << " ";

            for (int k = 0; k < adj[u].size(); k++)
            {
                int v = adj[u][k].first;
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << "\\n";
    }

    // DFS from start node
    void DFS(int start)
    {
        int s = getIndex(start);
        if (s == -1)
            return;

        DynamicArray<bool> visited(V);
        for (int i = 0; i < V; i++)
            visited.push_back(false);

        Stack<int> st;
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

            for (int k = 0; k < adj[u].size(); k++)
            {
                int v = adj[u][k].first;
                if (!visited[v])
                    st.push(v);
            }
        }
        cout << "\\n";
    }

    // Dijkstra: shortest path from start node
    void Dijkstra(int start, int end)
    {
        int s = getIndex(start);
        if (s == -1)
            return;

        DynamicArray<int> dist(V);
        DynamicArray<int> parent(V);
        for (int i = 0; i < V; i++)
        {
            dist.push_back(INT_MAX_VALUE);
            parent.push_back(-1);
        }
        dist[s] = 0;

        // Simple O(V^2) Dijkstra without priority queue
        DynamicArray<bool> processed(V);
        for (int i = 0; i < V; i++)
            processed.push_back(false);

        for (int count = 0; count < V; count++)
        {
            // Find min dist vertex not yet processed
            int u = -1;
            for (int i = 0; i < V; i++)
            {
                if (!processed[i] && (u == -1 || dist[i] < dist[u]))
                    u = i;
            }

            if (u == -1 || dist[u] == INT_MAX_VALUE)
                break;

            processed[u] = true;

            for (int k = 0; k < adj[u].size(); k++)
            {
                int v = adj[u][k].first;
                int w = adj[u][k].second;
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
            }
        }

        // Print path from start to end
        int e = getIndex(end);
        cout << "Shortest distance: " << dist[e] << "\\n";
        cout << "Path: ";
        DynamicArray<int> path;
        int curr = e;
        while (curr != -1)
        {
            path.push_back(curr);
            curr = parent[curr];
        }
        for (int i = path.size() - 1; i >= 0; i--)
            cout << nodeLabelByIndex(path[i]) << " ";
        cout << "\\n";
    }

    // Detect cycle in undirected graph using DFS
    bool detectCycleUtil(int u, DynamicArray<bool> &visited, int par)
    {
        visited[u] = true;
        for (int k = 0; k < adj[u].size(); k++)
        {
            int v = adj[u][k].first;
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
        DynamicArray<bool> visited(V);
        for (int i = 0; i < V; i++)
            visited.push_back(false);

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
        DynamicArray<bool> inMST(V);
        DynamicArray<int> key(V);
        for (int i = 0; i < V; i++)
        {
            inMST.push_back(false);
            key.push_back(INT_MAX_VALUE);
        }
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

            for (int k = 0; k < adj[u].size(); k++)
            {
                int v = adj[u][k].first;
                int w = adj[u][k].second;
                if (!inMST[v] && w < key[v])
                    key[v] = w;
            }
        }

        cout << "MST Edges:\\n";
        for (int i = 1; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                for (int k = 0; k < adj[j].size(); k++)
                {
                    Pair<int, int> &p = adj[j][k];
                    if (p.first == i && inMST[j])
                    {
                        cout << nodeLabelByIndex(j) << " - " << nodeLabelByIndex(i) << " : " << p.second << "\\n";
                        mstWeight += p.second;
                        break;
                    }
                }
            }
        }
        cout << "Total MST Weight: " << mstWeight << "\\n";
    }
};

#endif
