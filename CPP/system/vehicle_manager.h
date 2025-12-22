#ifndef VEHICLE_MANAGER_H
#define VEHICLE_MANAGER_H

#include <iostream>
#include "../ds/array.h"
#include "../ds/hashtable.h"
#include "../models/vehicle.h"

using namespace std;

class VehicleManager
{
private:
    DynamicArray<Vehicle> vehicles;     // DynamicArray for storing vehicles (ordered display)
    HashTable<int, Vehicle> vehicleMap; // O(1) lookup: ID -> Vehicle

public:
    VehicleManager() : vehicleMap(50) {} // Initialize hash table with capacity

    // Add a vehicle
    // Using HashTable for O(1) duplicate check
    bool addVehicle(const Vehicle &v)
    {
        // Validate vehicle ID
        if (v.getID() <= 0)
        {
            cout << "ERROR: Vehicle ID must be positive!" << endl;
            return false;
        }

        // Validate capacity
        if (v.getCapacity() <= 0)
        {
            cout << "ERROR: Vehicle capacity must be greater than 0!" << endl;
            return false;
        }

        // Check for duplicate vehicle ID using HashTable (O(1))
        if (vehicleMap.contains(v.getID()))
        {
            cout << "ERROR: Vehicle with ID " << v.getID() << " already exists!" << endl;
            return false;
        }

        vehicles.push_back(v);
        vehicleMap.insert(v.getID(), v); // O(1) insertion into hash table
        cout << "Vehicle added: " << v.getName() << " | ID: " << v.getID() << endl;
        return true;
    }

    // Remove a vehicle by ID
    // Using HashTable for O(1) removal
    void removeVehicle(int vehicleID)
    {
        // Remove from hash table first (O(1))
        if (!vehicleMap.remove(vehicleID))
        {
            cout << "Vehicle not found: ID " << vehicleID << endl;
            return;
        }

        // Remove from array
        for (int i = 0; i < vehicles.size(); i++)
        {
            if (vehicles[i].getID() == vehicleID)
            {
                vehicles.erase(i);
                cout << "Vehicle removed: ID " << vehicleID << endl;
                return;
            }
        }
    }

    // Display all vehicles
    void displayAllVehicles()
    {
        if (vehicles.empty())
        {
            cout << "No vehicles available." << endl;
            return;
        }
        cout << "All Vehicles:" << endl;
        for (int i = 0; i < vehicles.size(); i++)
        {
            vehicles[i].display();
        }
    }

    // Get total number of vehicles
    int totalVehicles() const
    {
        return vehicles.size();
    }

    // Assign fastest vehicle (smallest capacity that fits requirement)
    void assignFastestVehicle(int requiredPassengers)
    {
        Analytics::fastestVehicleAssignment(vehicles, requiredPassengers);
    }
};

#endif
