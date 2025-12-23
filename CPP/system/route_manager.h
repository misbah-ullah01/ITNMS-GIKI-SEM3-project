#ifndef ROUTE_MANAGER_H
#define ROUTE_MANAGER_H

#include <iostream>
#include <string>
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

    // Update passenger count at a station (increment for arrivals)
    void incrementStationPassengers(int stationID)
    {
        for (int i = 0; i < stations.size(); i++)
        {
            if (stations[i].getID() == stationID)
            {
                stations[i].addPassenger();
                break;
            }
        }
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

    // Display stations sorted by passenger count
    void displayStationsSortedByPassengers(bool ascending = false) const
    {
        if (stations.size() == 0)
        {
            cout << "No stations available." << endl;
            return;
        }

        // Create a copy and sort using quickSort
        DynamicArray<Station> sorted;
        for (int i = 0; i < stations.size(); i++)
            sorted.push_back(stations[i]);

        // Using insertion sort for simplicity with custom comparator
        for (int i = 1; i < sorted.size(); i++)
        {
            Station key = sorted[i];
            int j = i - 1;
            if (ascending)
            {
                while (j >= 0 && sorted[j] > key)
                {
                    sorted[j + 1] = sorted[j];
                    j--;
                }
            }
            else
            {
                while (j >= 0 && sorted[j] < key) // descending order
                {
                    sorted[j + 1] = sorted[j];
                    j--;
                }
            }
            sorted[j + 1] = key;
        }

        cout << "Stations (sorted by passenger count - " << (ascending ? "lowest" : "highest") << " first):" << endl;
        for (int i = 0; i < sorted.size(); i++)
        {
            sorted[i].display();
        }
    }

    // Display routes sorted by distance
    void displayRoutesSortedByDistance(bool ascending = true) const
    {
        if (routes.size() == 0)
        {
            cout << "No routes available." << endl;
            return;
        }

        // Create a copy and sort
        DynamicArray<Route> sorted;
        for (int i = 0; i < routes.size(); i++)
            sorted.push_back(routes[i]);

        // Insertion sort
        for (int i = 1; i < sorted.size(); i++)
        {
            Route key = sorted[i];
            int j = i - 1;
            if (ascending)
            {
                while (j >= 0 && sorted[j] > key)
                {
                    sorted[j + 1] = sorted[j];
                    j--;
                }
            }
            else
            {
                while (j >= 0 && sorted[j] < key)
                {
                    sorted[j + 1] = sorted[j];
                    j--;
                }
            }
            sorted[j + 1] = key;
        }

        cout << "Routes (sorted by distance - " << (ascending ? "shortest" : "longest") << " first):" << endl;
        for (int i = 0; i < sorted.size(); i++)
        {
            string startName = getStationNameById(sorted[i].getStartStationID());
            string endName = getStationNameById(sorted[i].getEndStationID());
            cout << "Route ID: " << sorted[i].getRouteID()
                 << ", From: " << startName
                 << ", To: " << endName
                 << ", Distance: " << sorted[i].getDistance() << " km" << endl;
        }
    }

    // Display all routes with station names
    void displayRoutes() const
    {
        cout << "Routes:" << endl;
        for (int i = 0; i < routes.size(); i++)
        {
            string startName = "Unknown";
            string endName = "Unknown";

            // Find station names
            for (int j = 0; j < stations.size(); j++)
            {
                if (stations[j].getID() == routes[i].getStartStationID())
                    startName = stations[j].getName();
                if (stations[j].getID() == routes[i].getEndStationID())
                    endName = stations[j].getName();
            }

            cout << "Route ID: " << routes[i].getRouteID()
                 << ", From: " << startName
                 << ", To: " << endName
                 << ", Distance: " << routes[i].getDistance() << " km" << endl;
        }
    }

    // BFS from a starting station
    void BFS(int startID)
    {
        graph.setLabelProvider(getStationNameByIdStatic);
        string startName = getStationNameById(startID);
        cout << "BFS starting from " << startName << ":" << endl;
        graph.BFS(startID);
    }

    // DFS from a starting station
    void DFS(int startID)
    {
        graph.setLabelProvider(getStationNameByIdStatic);
        string startName = getStationNameById(startID);
        cout << "DFS starting from " << startName << ":" << endl;
        graph.DFS(startID);
    }

    // Shortest path using Dijkstra
    void shortestPath(int startID, int endID)
    {
        graph.setLabelProvider(getStationNameByIdStatic);
        string startName = getStationNameById(startID);
        string endName = getStationNameById(endID);
        cout << "Shortest path from " << startName << " to " << endName << ":" << endl;
        graph.Dijkstra(startID, endID);
    }

    // Minimum Spanning Tree
    void minimumSpanningTree()
    {
        graph.setLabelProvider(getStationNameByIdStatic);
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

    // Search for route between two stations
    void searchRoute(int startID, int endID) const
    {
        bool found = false;
        for (int i = 0; i < routes.size(); i++)
        {
            if ((routes[i].getStartStationID() == startID && routes[i].getEndStationID() == endID) ||
                (routes[i].getStartStationID() == endID && routes[i].getEndStationID() == startID))
            {
                string startName = getStationNameById(routes[i].getStartStationID());
                string endName = getStationNameById(routes[i].getEndStationID());
                cout << "Route found!" << endl;
                cout << "Route ID: " << routes[i].getRouteID()
                     << ", From: " << startName
                     << ", To: " << endName
                     << ", Distance: " << routes[i].getDistance() << " km" << endl;
                found = true;
            }
        }
        if (!found)
        {
            cout << "No direct route found between these stations." << endl;
        }
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
