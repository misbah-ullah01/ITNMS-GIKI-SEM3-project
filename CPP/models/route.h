#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <string>
using namespace std;

class Route
{
private:
    int routeID;        // Unique route ID
    int startStationID; // ID of start station
    int endStationID;   // ID of end station
    double distance;    // Distance between stations (km)

public:
    // Constructor
    Route(int _routeID, int _start, int _end, double _distance)
        : routeID(_routeID), startStationID(_start), endStationID(_end), distance(_distance) {}

    // Getters
    int getRouteID() const { return routeID; }
    int getStartStationID() const { return startStationID; }
    int getEndStationID() const { return endStationID; }
    double getDistance() const { return distance; }

    // Setters
    void setDistance(double _distance) { distance = _distance; }

    // Display route info
    void display() const
    {
        cout << "Route ID: " << routeID
             << ", From: " << startStationID
             << ", To: " << endStationID
             << ", Distance: " << distance << " km" << endl;
    }

    // Operator overloading for comparisons
    bool operator==(const Route &other) const
    {
        return routeID == other.routeID;
    }
};

#endif
