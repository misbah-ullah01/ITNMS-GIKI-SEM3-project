#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
private:
    int vehicleID; // Unique vehicle ID
    string name;   // Vehicle name
    int capacity;  // Number of passengers it can carry

public:
    // Constructor
    Vehicle(int _vehicleID, string _name, int _capacity)
        : vehicleID(_vehicleID), name(_name), capacity(_capacity) {}

    // Getters
    int getID() const { return vehicleID; }
    string getName() const { return name; }
    int getCapacity() const { return capacity; }

    // Setters
    void setName(string _name) { name = _name; }
    void setCapacity(int _capacity) { capacity = _capacity; }

    // Display vehicle info
    void display() const
    {
        cout << "Vehicle ID: " << vehicleID
             << ", Name: " << name
             << ", Capacity: " << capacity << endl;
    }

    // Operator overloading for comparisons
    bool operator==(const Vehicle &other) const
    {
        return vehicleID == other.vehicleID;
    }
};

#endif
