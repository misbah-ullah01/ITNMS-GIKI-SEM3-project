#include <iostream>
#include "ds/array.h"
#include "ds/linkedlist.h"
#include "ds/queue.h"
#include "ds/stack.h"
#include "ds/heap.h"
#include "ds/trees.h"
#include "ds/searching.h"
#include "ds/sorting.h"

#include "models/passenger.h"
#include "models/ticket.h"
#include "models/route.h"
#include "models/station.h"
#include "models/vehicle.h"

#include "system/analytics.h"
#include "system/history_manager.h"
#include "system/route_manager.h"
#include "system/ticket_manager.h"
#include "system/vehicle_manager.h"

using namespace std;

// Function prototypes
void displayMainMenu();
void displayStationMenu(RouteManager &routeManager, HistoryManager &historyManager);
void displayRouteMenu(RouteManager &routeManager, HistoryManager &historyManager);
void displayVehicleMenu(VehicleManager &vehicleManager, HistoryManager &historyManager);
void displayPassengerMenu(TicketManager &ticketManager, RouteManager &routeManager, HistoryManager &historyManager);
void displayGraphMenu(RouteManager &routeManager);
void displayViewMenu(RouteManager &routeManager, TicketManager &ticketManager, VehicleManager &vehicleManager);
void displayHistoryMenu(HistoryManager &historyManager, RouteManager &routeManager, VehicleManager &vehicleManager);
void displaySearchSortMenu();
void displaySearchSortMenu();

int main()
{
    cout << "\n======================================================================\n";
    cout << "    Welcome to Intelligent Transport Network Management System\n";
    cout << "                        (ITNMS v1.0)\n";
    cout << "======================================================================\n\n";

    // System Managers
    RouteManager routeManager;
    routeManager.setInstance(); // Set static instance for function pointer callbacks
    TicketManager ticketManager;
    VehicleManager vehicleManager;
    HistoryManager historyManager;
    Analytics analyticsManager;

    int mainChoice;
    bool running = true;

    while (running)
    {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> mainChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n\n";
            continue;
        }

        switch (mainChoice)
        {
        case 1:
            displayStationMenu(routeManager, historyManager);
            break;
        case 2:
            displayRouteMenu(routeManager, historyManager);
            break;
        case 3:
            displayVehicleMenu(vehicleManager, historyManager);
            break;
        case 4:
            displayPassengerMenu(ticketManager, routeManager, historyManager);
            break;
        case 5:
            displayViewMenu(routeManager, ticketManager, vehicleManager);
            break;
        case 6:
            displayGraphMenu(routeManager);
            break;
        case 7:
            displayHistoryMenu(historyManager, routeManager, vehicleManager);
            break;
        case 8:
            displaySearchSortMenu();
            break;
        case 9:
            cout << "\n======================================================================\n";
            cout << "          Thank you for using ITNMS! Goodbye!\n";
            cout << "======================================================================\n\n";
            running = false;
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n\n";
        }
    }

    return 0;
}

void displayMainMenu()
{
    cout << "\n========== MAIN MENU ==========\n";
    cout << "1. Manage Stations\n";
    cout << "2. Manage Routes\n";
    cout << "3. Manage Vehicles\n";
    cout << "4. Manage Passengers & Tickets\n";
    cout << "5. View System Information\n";
    cout << "6. Graph Algorithms & Analysis\n";
    cout << "7. History & Undo\n";
    cout << "8. Searching & Sorting Demos\n";
    cout << "9. Exit\n";
    cout << "===============================\n";
}

void displayStationMenu(RouteManager &routeManager, HistoryManager &historyManager)
{
    int stationChoice;
    bool stationMenuActive = true;

    while (stationMenuActive)
    {
        cout << "\n========== STATION MANAGEMENT ==========\n";
        cout << "1. Add New Station\n";
        cout << "2. Display All Stations\n";
        cout << "3. Back to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        cin >> stationChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n\n";
            continue;
        }

        switch (stationChoice)
        {
        case 1:
        {
            int stationID;
            string stationName, location;

            cout << "\n--- Add New Station ---\n";
            cout << "Enter Station ID: ";
            cin >> stationID;
            cin.ignore();

            if (stationID <= 0)
            {
                cout << "ERROR: Station ID must be positive!\n";
                break;
            }

            cout << "Enter Station Name: ";
            getline(cin, stationName);

            if (stationName.empty())
            {
                cout << "ERROR: Station name cannot be empty!\n";
                break;
            }

            cout << "Enter Location (optional): ";
            getline(cin, location);

            Station newStation(stationID, stationName, location);
            if (routeManager.addStation(newStation))
            {
                cout << "Station added successfully!\n";
                // Record history for undo
                historyManager.addAction("ADD_STATION:" + to_string(stationID) + ":" + stationName + ":" + location);
            }
            break;
        }
        case 2:
            cout << "\n";
            routeManager.displayStations();
            break;
        case 3:
            stationMenuActive = false;
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    }
}

void displayRouteMenu(RouteManager &routeManager, HistoryManager &historyManager)
{
    int routeChoice;
    bool routeMenuActive = true;

    while (routeMenuActive)
    {
        cout << "\n========== ROUTE MANAGEMENT ==========\n";
        cout << "1. Add New Route\n";
        cout << "2. Display All Routes\n";
        cout << "3. Back to Main Menu\n";
        cout << "=====================================\n";
        cout << "Enter choice: ";
        cin >> routeChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n\n";
            continue;
        }

        switch (routeChoice)
        {
        case 1:
        {
            int routeID;
            double distance;
            string startName, endName;

            cout << "\n--- Add New Route ---\n";
            cout << "Enter Route ID: ";
            cin >> routeID;
            cin.ignore();

            cout << "Enter Start Station Name: ";
            getline(cin, startName);

            cout << "Enter End Station Name: ";
            getline(cin, endName);

            cout << "Enter Distance (km): ";
            cin >> distance;

            // Validate inputs
            if (distance <= 0)
            {
                cout << "ERROR: Distance must be greater than 0!\n";
                break;
            }

            int startID = routeManager.findStationIdByName(startName);
            int endID = routeManager.findStationIdByName(endName);

            if (startID == -1)
            {
                cout << "ERROR: Start station not found!\n";
                break;
            }
            if (endID == -1)
            {
                cout << "ERROR: End station not found!\n";
                break;
            }

            if (startID == endID)
            {
                cout << "ERROR: Start and End stations cannot be the same!\n";
                break;
            }

            Route newRoute(routeID, startID, endID, distance);
            if (routeManager.addRoute(newRoute))
            {
                cout << "Route added successfully!\n";
                // Record history for undo
                historyManager.addAction("ADD_ROUTE:" + to_string(routeID) + ":" + to_string(startID) + ":" + to_string(endID) + ":" + to_string((int)distance));
            }
            break;
        }
        case 2:
            cout << "\n";
            routeManager.displayRoutes();
            break;
        case 3:
            routeMenuActive = false;
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    }
}

void displayVehicleMenu(VehicleManager &vehicleManager, HistoryManager &historyManager)
{
    int vehicleChoice;
    bool vehicleMenuActive = true;

    while (vehicleMenuActive)
    {
        cout << "\n========== VEHICLE MANAGEMENT ==========\n";
        cout << "1. Register New Vehicle\n";
        cout << "2. Display All Vehicles\n";
        cout << "3. Back to Main Menu\n";
        cout << "=======================================\n";
        cout << "Enter choice: ";
        cin >> vehicleChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n\n";
            continue;
        }

        switch (vehicleChoice)
        {
        case 1:
        {
            int vehicleID, capacity;
            string vehicleName;

            cout << "\n--- Register New Vehicle ---\n";
            cout << "Enter Vehicle ID: ";
            cin >> vehicleID;
            cin.ignore();

            if (vehicleID <= 0)
            {
                cout << "ERROR: Vehicle ID must be positive!\n";
                break;
            }

            cout << "Enter Vehicle Name: ";
            getline(cin, vehicleName);

            if (vehicleName.empty())
            {
                cout << "ERROR: Vehicle name cannot be empty!\n";
                break;
            }

            cout << "Enter Passenger Capacity: ";
            cin >> capacity;

            if (capacity <= 0)
            {
                cout << "ERROR: Vehicle capacity must be greater than 0!\n";
                break;
            }

            Vehicle newVehicle(vehicleID, vehicleName, capacity);
            if (vehicleManager.addVehicle(newVehicle))
            {
                cout << "Vehicle registered successfully!\n";
                // Record history for undo
                historyManager.addAction("ADD_VEHICLE:" + to_string(vehicleID) + ":" + vehicleName + ":" + to_string(capacity));
            }
            break;
        }
        case 2:
            cout << "\n";
            vehicleManager.displayAllVehicles();
            break;
        case 3:
            vehicleMenuActive = false;
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    }
}

void displayPassengerMenu(TicketManager &ticketManager, RouteManager &routeManager, HistoryManager &historyManager)
{
    int passengerChoice;
    bool passengerMenuActive = true;

    while (passengerMenuActive)
    {
        cout << "\n========== PASSENGER & TICKET MANAGEMENT ==========\n";
        cout << "1. Add Passenger to Queue\n";
        cout << "2. Process Next Passenger (Issue Ticket)\n";
        cout << "3. Display Passenger Queue\n";
        cout << "4. Display All Issued Tickets\n";
        cout << "5. Back to Main Menu\n";
        cout << "==================================================\n";
        cout << "Enter choice: ";
        cin >> passengerChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n\n";
            continue;
        }

        switch (passengerChoice)
        {
        case 1:
        {
            int passengerID, age;
            string passengerName;

            cout << "\n--- Add Passenger to Queue ---\n";
            cout << "Enter Passenger ID: ";
            cin >> passengerID;
            cin.ignore();

            if (passengerID <= 0)
            {
                cout << "ERROR: Passenger ID must be positive!\n";
                break;
            }

            cout << "Enter Passenger Name: ";
            getline(cin, passengerName);

            if (passengerName.empty())
            {
                cout << "ERROR: Passenger name cannot be empty!\n";
                break;
            }

            cout << "Enter Age: ";
            cin >> age;

            if (age <= 0 || age > 120)
            {
                cout << "ERROR: Age must be between 1 and 120!\n";
                break;
            }

            Passenger newPassenger(passengerID, passengerName, age);
            ticketManager.addPassengerToQueue(newPassenger);
            cout << "Passenger added to queue!\n";

            // Record history for undo
            historyManager.addAction("ADD_PASSENGER:" + to_string(passengerID) + ":" + passengerName + ":" + to_string(age));
            break;
        }
        case 2:
        {
            string startName, endName;
            cout << "\n--- Issue Ticket ---\n";
            cout << "Enter departure station name: ";
            cin.ignore();
            getline(cin, startName);

            cout << "Enter arrival station name: ";
            getline(cin, endName);

            int startID = routeManager.findStationIdByName(startName);
            int endID = routeManager.findStationIdByName(endName);

            if (startID == -1)
            {
                cout << "ERROR: Departure station not found!\n";
                break;
            }
            if (endID == -1)
            {
                cout << "ERROR: Arrival station not found!\n";
                break;
            }
            if (startID == endID)
            {
                cout << "ERROR: Departure and arrival stations cannot be the same!\n";
                break;
            }

            cout << "\n";
            ticketManager.processNextPassenger(startID, endID);
            break;
        }
        case 3:
            cout << "\n";
            ticketManager.displayQueue();
            break;
        case 4:
            cout << "\n";
            ticketManager.displayAllTicketsWithNames(RouteManager::getStationNameByIdStatic);
            break;
        case 5:
            passengerMenuActive = false;
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    }
}

void displayViewMenu(RouteManager &routeManager, TicketManager &ticketManager, VehicleManager &vehicleManager)
{
    int viewChoice;
    bool viewMenuActive = true;

    while (viewMenuActive)
    {
        cout << "\n========== VIEW SYSTEM INFORMATION ==========\n";
        cout << "1. Display All Stations\n";
        cout << "2. Display All Routes\n";
        cout << "3. Display All Vehicles\n";
        cout << "4. Display All Tickets\n";
        cout << "5. Display Passenger Queue\n";
        cout << "6. Show Most Crowded Station (by Tickets)\n";
        cout << "7. Show Busiest Route\n";
        cout << "8. Fastest Vehicle Assignment\n";
        cout << "9. Traffic Density Prediction\n";
        cout << "10. Daily Usage Trends\n";
        cout << "11. Back to Main Menu\n";
        cout << "============================================\n";
        cout << "Enter choice: ";
        cin >> viewChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n\n";
            continue;
        }

        switch (viewChoice)
        {
        case 1:
            cout << "\n";
            routeManager.displayStations();
            break;
        case 2:
            cout << "\n";
            routeManager.displayRoutes();
            break;
        case 3:
            cout << "\n";
            vehicleManager.displayAllVehicles();
            break;
        case 4:
            cout << "\n";
            ticketManager.displayAllTicketsWithNames(RouteManager::getStationNameByIdStatic);
            break;
        case 5:
            cout << "\n";
            ticketManager.displayQueue();
            break;
        case 6:
            cout << "\n";
            // Get stations and tickets for analytics
            {
                // We need to expose stations from RouteManager
                // For now, call analytics via RouteManager
                routeManager.showMostCrowdedStation(ticketManager.getAllTickets());
            }
            break;
        case 7:
            cout << "\n";
            routeManager.showBusiestRoute(ticketManager.getAllTickets());
            break;
        case 8:
        {
            int reqPassengers;
            cout << "\nEnter required passenger capacity: ";
            cin >> reqPassengers;
            cout << "\n";
            vehicleManager.assignFastestVehicle(reqPassengers);
            break;
        }
        case 9:
            cout << "\n";
            routeManager.showTrafficDensity(ticketManager.getAllTickets(), 5);
            break;
        case 10:
            cout << "\n";
            Analytics::dailyUsageTrends(ticketManager.getAllTickets());
            break;
        case 11:
            viewMenuActive = false;
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    }
}

void displayGraphMenu(RouteManager &routeManager)
{
    int graphChoice;
    bool graphMenuActive = true;

    while (graphMenuActive)
    {
        cout << "\n========== GRAPH ALGORITHMS & ANALYSIS ==========\n";
        cout << "1. BFS Traversal\n";
        cout << "2. DFS Traversal\n";
        cout << "3. Shortest Path (Dijkstra)\n";
        cout << "4. Minimum Spanning Tree (Prim's)\n";
        cout << "5. Detect Cycle in Network\n";
        cout << "6. Back to Main Menu\n";
        cout << "================================================\n";
        cout << "Enter choice: ";
        cin >> graphChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n\n";
            continue;
        }

        switch (graphChoice)
        {
        case 1:
        {
            string startName;
            cout << "\nEnter starting station name: ";
            cin.ignore();
            getline(cin, startName);
            int startID = routeManager.findStationIdByName(startName);
            if (startID == -1)
            {
                cout << "ERROR: Station not found!\n";
                break;
            }
            cout << "\n";
            routeManager.BFS(startID);
            break;
        }
        case 2:
        {
            string startName;
            cout << "\nEnter starting station name: ";
            cin.ignore();
            getline(cin, startName);
            int startID = routeManager.findStationIdByName(startName);
            if (startID == -1)
            {
                cout << "ERROR: Station not found!\n";
                break;
            }
            cout << "\n";
            routeManager.DFS(startID);
            break;
        }
        case 3:
        {
            string startName, endName;
            cout << "\nEnter starting station name: ";
            cin.ignore();
            getline(cin, startName);
            cout << "Enter ending station name: ";
            getline(cin, endName);
            int startID = routeManager.findStationIdByName(startName);
            int endID = routeManager.findStationIdByName(endName);
            if (startID == -1 || endID == -1)
            {
                if (startID == -1)
                    cout << "ERROR: Start station not found!\n";
                if (endID == -1)
                    cout << "ERROR: End station not found!\n";
                break;
            }
            cout << "\n";
            routeManager.shortestPath(startID, endID);
            break;
        }
        case 4:
            cout << "\n";
            routeManager.minimumSpanningTree();
            break;
        case 5:
            cout << "\n";
            if (routeManager.detectCycle())
                cout << "Cycle detected in the network!\n";
            else
                cout << "No cycle found in the network.\n";
            break;
        case 6:
            graphMenuActive = false;
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    }
}

void displayHistoryMenu(HistoryManager &historyManager, RouteManager &routeManager, VehicleManager &vehicleManager)
{
    int historyChoice;
    bool historyMenuActive = true;

    while (historyMenuActive)
    {
        cout << "\n========== HISTORY & UNDO ==========" << endl;
        cout << "1. View Action History" << endl;
        cout << "2. Undo Last Action" << endl;
        cout << "3. Clear History" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "===================================" << endl;
        cout << "Enter choice: ";
        cin >> historyChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n\n";
            continue;
        }

        switch (historyChoice)
        {
        case 1:
            cout << "\n";
            historyManager.displayHistory();
            break;
        case 2:
        {
            string last = historyManager.undo();
            if (last == "No actions to undo.")
            {
                cout << last << endl;
                break;
            }

            // Parse action format: TYPE:field1:field2:...
            // Supported: ADD_STATION:id:name:location
            //            ADD_ROUTE:id:start:end:distance
            //            ADD_VEHICLE:id:name:capacity
            size_t pos = 0;
            DynamicArray<string> parts;
            string token;
            string temp = last;
            while ((pos = temp.find(':')) != string::npos)
            {
                parts.push_back(temp.substr(0, pos));
                temp.erase(0, pos + 1);
            }
            parts.push_back(temp);

            if (parts.size() == 0)
            {
                cout << "Could not parse last action." << endl;
                break;
            }

            string actionType = parts[0];
            if (actionType == "ADD_STATION" && parts.size() >= 2)
            {
                int id = stoi(parts[1]);
                if (routeManager.removeStation(id))
                {
                    cout << "Undo successful: removed station " << id << endl;
                }
                else
                {
                    cout << "Undo failed for station " << id << endl;
                }
            }
            else if (actionType == "ADD_ROUTE" && parts.size() >= 2)
            {
                int rid = stoi(parts[1]);
                if (routeManager.removeRouteById(rid))
                {
                    cout << "Undo successful: removed route " << rid << endl;
                }
                else
                {
                    cout << "Undo failed for route " << rid << endl;
                }
            }
            else if (actionType == "ADD_VEHICLE" && parts.size() >= 2)
            {
                int vid = stoi(parts[1]);
                vehicleManager.removeVehicle(vid);
                cout << "Undo attempted: remove vehicle " << vid << endl;
            }
            else
            {
                cout << "Undo not supported for this action: " << last << endl;
            }

            break;
        }
        case 3:
            historyManager.clearHistory();
            cout << "History cleared." << endl;
            break;
        case 4:
            historyMenuActive = false;
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    }
}

void displaySearchSortMenu()
{
    int choice;
    bool menuActive = true;

    while (menuActive)
    {
        cout << "\n========== SEARCHING & SORTING DEMOS ==========\n";
        cout << "1. Linear Search Demo\n";
        cout << "2. Binary Search Demo\n";
        cout << "3. Bubble Sort Demo\n";
        cout << "4. Selection Sort Demo\n";
        cout << "5. Insertion Sort Demo\n";
        cout << "6. Quick Sort Demo\n";
        cout << "7. Merge Sort Demo\n";
        cout << "8. Heap Sort Demo\n";
        cout << "9. Back to Main Menu\n";
        cout << "===============================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n\n";
            continue;
        }

        if (choice == 9)
        {
            menuActive = false;
            continue;
        }

        // Sample array for demonstrations
        int arr[] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50, 33, 17};
        int size = sizeof(arr) / sizeof(arr[0]);
        int arrCopy[20];

        switch (choice)
        {
        case 1:
        {
            cout << "\n--- Linear Search Demo ---\n";
            cout << "Array: ";
            for (int i = 0; i < size; i++)
                cout << arr[i] << " ";
            cout << "\n";
            int key;
            cout << "Enter value to search: ";
            cin >> key;
            int result = linearSearch(arr, size, key);
            if (result != -1)
                cout << "Found at index: " << result << "\n";
            else
                cout << "Not found.\n";
            cout << "Time Complexity: O(n)\n";
            break;
        }
        case 2:
        {
            cout << "\n--- Binary Search Demo ---\n";
            for (int i = 0; i < size; i++)
                arrCopy[i] = arr[i];
            // Sort first
            bubbleSort(arrCopy, size);
            cout << "Sorted Array: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\n";
            int key;
            cout << "Enter value to search: ";
            cin >> key;
            int result = binarySearch(arrCopy, size, key);
            if (result != -1)
                cout << "Found at index: " << result << "\n";
            else
                cout << "Not found.\n";
            cout << "Time Complexity: O(log n)\n";
            break;
        }
        case 3:
        {
            cout << "\n--- Bubble Sort Demo ---\n";
            for (int i = 0; i < size; i++)
                arrCopy[i] = arr[i];
            cout << "Before: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\n";
            bubbleSort(arrCopy, size);
            cout << "After: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\nTime Complexity: O(n²)\n";
            break;
        }
        case 4:
        {
            cout << "\n--- Selection Sort Demo ---\n";
            for (int i = 0; i < size; i++)
                arrCopy[i] = arr[i];
            cout << "Before: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\n";
            selectionSort(arrCopy, size);
            cout << "After: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\nTime Complexity: O(n²)\n";
            break;
        }
        case 5:
        {
            cout << "\n--- Insertion Sort Demo ---\n";
            for (int i = 0; i < size; i++)
                arrCopy[i] = arr[i];
            cout << "Before: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\n";
            insertionSort(arrCopy, size);
            cout << "After: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\nTime Complexity: O(n²)\n";
            break;
        }
        case 6:
        {
            cout << "\n--- Quick Sort Demo ---\n";
            for (int i = 0; i < size; i++)
                arrCopy[i] = arr[i];
            cout << "Before: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\n";
            quickSort(arrCopy, 0, size - 1);
            cout << "After: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\nTime Complexity: O(n log n) average\n";
            break;
        }
        case 7:
        {
            cout << "\n--- Merge Sort Demo ---\n";
            for (int i = 0; i < size; i++)
                arrCopy[i] = arr[i];
            cout << "Before: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\n";
            mergeSort(arrCopy, 0, size - 1);
            cout << "After: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\nTime Complexity: O(n log n)\n";
            break;
        }
        case 8:
        {
            cout << "\n--- Heap Sort Demo ---\n";
            for (int i = 0; i < size; i++)
                arrCopy[i] = arr[i];
            cout << "Before: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\n";
            heapSort(arrCopy, size);
            cout << "After: ";
            for (int i = 0; i < size; i++)
                cout << arrCopy[i] << " ";
            cout << "\nTime Complexity: O(n log n)\n";
            break;
        }
        default:
            cout << "\nInvalid choice!\n";
        }
    }
}
