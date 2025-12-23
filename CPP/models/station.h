#ifndef STATION_H
#define STATION_H

#include <iostream>
using namespace std;

class Station
{
private:
    int stationID;       // Unique ID for station
    string name;         // Station name
    string location;     // Optional: location or address
    int passengersCount; // Optional: number of passengers currently

public:
    Station() : stationID(0), name(""), location(""), passengersCount(0) {}
    // Constructor
    Station(int _id, string _name, string _location = "")
        : stationID(_id), name(_name), location(_location), passengersCount(0) {}

    // Getters
    int getID() const { return stationID; }
    string getName() const { return name; }
    string getLocation() const { return location; }
    int getPassengerCount() const { return passengersCount; }

    // Setters
    void setName(string _name) { name = _name; }
    void setLocation(string _location) { location = _location; }
    void setPassengerCount(int count) { passengersCount = count; }

    // Increment/decrement passenger count
    void addPassenger() { passengersCount++; }
    void removePassenger()
    {
        if (passengersCount > 0)
            passengersCount--;
    }

    // Display station info
    void display() const
    {
        cout << "Station ID: " << stationID
             << ", Name: " << name
             << ", Location: " << location
             << ", Passengers: " << passengersCount << endl;
    }

    // Comparison operator
    bool operator==(const Station &other) const
    {
        return stationID == other.stationID;
    }

    // Less than operator for sorting by passenger count (descending - higher count first)
    bool operator>(const Station &other) const
    {
        return passengersCount > other.passengersCount;
    }

    bool operator<(const Station &other) const
    {
        return passengersCount < other.passengersCount;
    }
};

#endif
