#ifndef ROUTE_MANAGER_H
#define ROUTE_MANAGER_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include <cctype>
#include "../ds/graph.h"
#include "../ds/hashtable.h"
#include "../models/station.h"
#include "../models/route.h"
#include "../models/ticket.h"
#include "analytics.h"

using namespace std;

class RouteManager
{
private:
    Graph graph;                        // Graph representing stations and routes
    vector<Station> stations;           // List of all stations (for ordered display)
    vector<Route> routes;               // List of all routes (for ordered display)
    HashTable<int, Station> stationMap; // O(1) lookup: ID -> Station
    HashTable<int, Route> routeMap;     // O(1) lookup: ID -> Route

    static string toLower(const string &s)
    {
        string out = s;
        transform(out.begin(), out.end(), out.begin(), [](unsigned char c)
                  { return std::tolower(c); });
        return out;
    }

    void rebuildGraph()
    {
        graph.clear();
        // Re-add all station vertices
        for (const auto &s : stations)
        {
            graph.addVertex(s.getID());
        }
        // Re-add all edges
        for (const auto &r : routes)
        {
            graph.addEdge(r.getStartStationID(), r.getEndStationID(), (int)r.getDistance());
        }
    }

public:
    RouteManager() : stationMap(100), routeMap(100) // Initialize hash tables with capacity
    {
        // Provide station names to graph for user-friendly labels
        graph.setLabelProvider([this](int stationId)
                               { return getStationNameById(stationId); });
    }

    // Find station ID by name (case-insensitive); returns -1 if not found
    int findStationIdByName(const string &name) const
    {
        string key = toLower(name);
        for (const auto &s : stations)
        {
            if (toLower(s.getName()) == key)
                return s.getID();
        }
        return -1;
    }

    // Get station name by ID; fallback to stringified ID if not found
    // Using HashTable for O(1) lookup
    string getStationNameById(int stationID) const
    {
        // Search in vector since we need the actual object
        for (const auto &s : stations)
        {
            if (s.getID() == stationID)
                return s.getName();
        }
        return "ID " + to_string(stationID);
    }

    // Add a station
    // Using HashTable for O(1) duplicate check
    bool addStation(const Station &station)
    {
        // Validate station ID
        if (station.getID() <= 0)
        {
            cout << "ERROR: Station ID must be positive!" << endl;
            return false;
        }

        // Check for duplicate station ID using HashTable (O(1))
        if (stationMap.contains(station.getID()))
        {
            cout << "ERROR: Station with ID " << station.getID() << " already exists!" << endl;
            return false;
        }

        stations.push_back(station);
        stationMap.insert(station.getID(), station); // O(1) insertion into hash table
        graph.addVertex(station.getID());
        cout << "Station added: " << station.getName() << endl;
        return true;
    }

    // Add a route (edge between stations)
    // Using HashTable for O(1) station existence check
    bool addRoute(const Route &route)
    {
        // Check if both stations exist using HashTable (O(1))
        bool startExists = stationMap.contains(route.getStartStationID());
        bool endExists = stationMap.contains(route.getEndStationID());

        if (!startExists || !endExists)
        {
            cout << "ERROR: One or both stations do not exist!" << endl;
            if (!startExists)
                cout << "  - Start Station ID " << route.getStartStationID() << " not found" << endl;
            if (!endExists)
                cout << "  - End Station ID " << route.getEndStationID() << " not found" << endl;
            return false;
        }

        routes.push_back(route);
        routeMap.insert(route.getRouteID(), route); // O(1) insertion into hash table
        graph.addEdge(route.getStartStationID(), route.getEndStationID(), (int)route.getDistance());
        cout << "Route added: " << route.getStartStationID() << " -> " << route.getEndStationID() << endl;
        return true;
    }

    // Remove a station and any connected routes
    // Using HashTable for O(1) removal
    bool removeStation(int stationID)
    {
        // Remove from hash table first (O(1))
        if (!stationMap.remove(stationID))
        {
            cout << "Station not found: ID " << stationID << endl;
            return false;
        }

        // Remove from vector
        for (auto it = stations.begin(); it != stations.end(); ++it)
        {
            if (it->getID() == stationID)
            {
                stations.erase(it);
                break;
            }
        }

        // Remove any routes connected to this station
        vector<Route> newRoutes;
        newRoutes.reserve(routes.size());
        for (const auto &r : routes)
        {
            if (r.getStartStationID() == stationID || r.getEndStationID() == stationID)
            {
                routeMap.remove(r.getRouteID()); // Also remove from hash table
                continue;
            }
            newRoutes.push_back(r);
        }
        routes.swap(newRoutes);

        rebuildGraph();
        cout << "Station removed: ID " << stationID << " (connected routes pruned)" << endl;
        return true;
    }

    // Remove a route by route ID
    // Using HashTable for O(1) removal
    bool removeRouteById(int routeID)
    {
        // Remove from hash table first (O(1))
        if (!routeMap.remove(routeID))
        {
            cout << "Route not found: ID " << routeID << endl;
            return false;
        }

        // Remove from vector
        for (auto it = routes.begin(); it != routes.end(); ++it)
        {
            if (it->getRouteID() == routeID)
            {
                routes.erase(it);
                break;
            }
        }

        rebuildGraph();
        cout << "Route removed: ID " << routeID << endl;
        return true;
    }

    // Check if station exists
    // Using HashTable for O(1) lookup
    bool stationExists(int stationID) const
    {
        return stationMap.contains(stationID);
    }

    // Display all stations
    void displayStations() const
    {
        cout << "Stations:" << endl;
        for (const auto &s : stations)
        {
            s.display();
        }
    }

    // Display all routes
    void displayRoutes() const
    {
        cout << "Routes:" << endl;
        for (const auto &r : routes)
        {
            r.display();
        }
    }

    // BFS from a starting station
    void BFS(int startID)
    {
        cout << "BFS starting from Station ID " << startID << ":" << endl;
        graph.BFS(startID);
    }

    // DFS from a starting station
    void DFS(int startID)
    {
        cout << "DFS starting from Station ID " << startID << ":" << endl;
        graph.DFS(startID);
    }

    // Shortest path using Dijkstra
    void shortestPath(int startID, int endID)
    {
        cout << "Shortest path from " << startID << " to " << endID << ":" << endl;
        graph.Dijkstra(startID, endID);
    }

    // Minimum Spanning Tree
    void minimumSpanningTree()
    {
        cout << "Minimum Spanning Tree:" << endl;
        graph.MST();
    }

    // Show most crowded station based on ticket activity
    void showMostCrowdedStation(const vector<Ticket> &tickets)
    {
        Analytics::mostCrowdedStationByTickets(stations, tickets,
                                               [this](int id)
                                               { return getStationNameById(id); });
    }
};

#endif
