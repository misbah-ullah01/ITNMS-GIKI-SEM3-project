#ifndef ROUTE_MANAGER_H
#define ROUTE_MANAGER_H

#include <iostream>
#include "../ds/graph.h"
#include "../ds/hashtable.h"
#include "../ds/array.h"
#include "../models/station.h"
#include "../models/route.h"
#include "../models/ticket.h"
#include "analytics.h"

using namespace std;

class RouteManager
{
private:
    Graph graph;                        // Graph representing stations and routes
    DynamicArray<Station> stations;     // List of all stations (for ordered display)
    DynamicArray<Route> routes;         // List of all routes (for ordered display)
    HashTable<int, Station> stationMap; // O(1) lookup: ID -> Station
    HashTable<int, Route> routeMap;     // O(1) lookup: ID -> Route

    static string toLower(const string &s)
    {
        string out = s;
        for (int i = 0; i < (int)out.size(); i++)
        {
            if (out[i] >= 'A' && out[i] <= 'Z')
                out[i] = out[i] + ('a' - 'A');
        }
        return out;
    }

    void rebuildGraph()
    {
        graph.clear();
        // Re-add all station vertices
        for (int i = 0; i < stations.size(); i++)
        {
            graph.addVertex(stations[i].getID());
        }
        // Re-add all edges
        for (int i = 0; i < routes.size(); i++)
        {
            graph.addEdge(routes[i].getStartStationID(), routes[i].getEndStationID(), (int)routes[i].getDistance());
        }
    }

public:
    RouteManager() : stationMap(100), routeMap(100) // Initialize hash tables with capacity
    {
    }

    // Find station ID by name (case-insensitive); returns -1 if not found
    int findStationIdByName(const string &name) const
    {
        string key = toLower(name);
        for (int i = 0; i < stations.size(); i++)
        {
            if (toLower(stations[i].getName()) == key)
                return stations[i].getID();
        }
        return -1;
    }

    // Get station name by ID; fallback to stringified ID if not found
    // Using HashTable for O(1) lookup
    string getStationNameById(int stationID) const
    {
        // Search in array since we need the actual object
        for (int i = 0; i < stations.size(); i++)
        {
            if (stations[i].getID() == stationID)
                return stations[i].getName();
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

        // Remove from array
        for (int i = 0; i < stations.size(); i++)
        {
            if (stations[i].getID() == stationID)
            {
                stations.erase(i);
                break;
            }
        }

        // Remove any routes connected to this station
        DynamicArray<Route> newRoutes;
        for (int i = 0; i < routes.size(); i++)
        {
            if (routes[i].getStartStationID() == stationID || routes[i].getEndStationID() == stationID)
            {
                routeMap.remove(routes[i].getRouteID()); // Also remove from hash table
                continue;
            }
            newRoutes.push_back(routes[i]);
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

        // Remove from array
        for (int i = 0; i < routes.size(); i++)
        {
            if (routes[i].getRouteID() == routeID)
            {
                routes.erase(i);
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
        for (int i = 0; i < stations.size(); i++)
        {
            stations[i].display();
        }
    }

    // Display all routes
    void displayRoutes() const
    {
        cout << "Routes:" << endl;
        for (int i = 0; i < routes.size(); i++)
        {
            routes[i].display();
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
    void showMostCrowdedStation(const DynamicArray<Ticket> &tickets)
    {
        Analytics::mostCrowdedStationByTickets(stations, tickets, getStationNameByIdStatic);
    }

    // Show busiest route
    void showBusiestRoute(const DynamicArray<Ticket> &tickets)
    {
        Analytics::busiestRouteByTickets(routes, tickets, getStationNameByIdStatic);
    }

    // Show traffic density prediction
    void showTrafficDensity(const DynamicArray<Ticket> &tickets, int topN = 5)
    {
        Analytics::trafficDensityPrediction(stations, tickets, getStationNameByIdStatic, topN);
    }

    // Detect cycle in network
    bool detectCycle()
    {
        return graph.detectCycle();
    }

    // Static helper for function pointer (workaround for no lambdas)
    static RouteManager *instance;
    static string getStationNameByIdStatic(int id)
    {
        if (instance)
            return instance->getStationNameById(id);
        return "ID " + to_string(id);
    }
    void setInstance() { instance = this; }
};

// Static member definition
RouteManager *RouteManager::instance = nullptr;

#endif
