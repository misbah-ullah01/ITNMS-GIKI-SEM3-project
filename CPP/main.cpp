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
void displayHeader();
void clearScreen();
void displayMainMenu();
void displayStationMenu(RouteManager &routeManager, HistoryManager &historyManager);
void displayRouteMenu(RouteManager &routeManager, HistoryManager &historyManager);
void displayVehicleMenu(VehicleManager &vehicleManager, HistoryManager &historyManager);
void displayPassengerMenu(TicketManager &ticketManager, RouteManager &routeManager, HistoryManager &historyManager);
void displayGraphMenu(RouteManager &routeManager);
void displayViewMenu(RouteManager &routeManager, TicketManager &ticketManager, VehicleManager &vehicleManager);
void displayHistoryMenu(HistoryManager &historyManager, RouteManager &routeManager, VehicleManager &vehicleManager);
void displaySearchSortMenu(RouteManager &routeManager, VehicleManager &vehicleManager, TicketManager &ticketManager);

// ANSI Color codes for beautiful UI (works on Windows 10+ and Linux/Mac)
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define DIM "\033[2m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define WHITE "\033[37m"
#define RED "\033[31m"
#define BG_BLUE "\033[44m"

// Enable ANSI colors and UTF-8 on Windows
void enableColors()
{
#ifdef _WIN32
    system("chcp 65001 > nul"); // Set console to UTF-8 encoding
    system("");                 // This trick enables ANSI escape codes on Windows 10+
#endif
}

// ASCII Art Header - Always displayed at top
void displayHeader()
{
    cout << CYAN << BOLD;
    cout << "\n";
    cout << "  +============================================================================+\n";
    cout << "  |                                                                            |\n";
    cout << "  |" << WHITE << "    ██╗████████╗███╗   ██╗███╗   ███╗███████╗                              " << CYAN << "|\n";
    cout << "  |" << WHITE << "    ██║╚══██╔══╝████╗  ██║████╗ ████║██╔════╝                              " << CYAN << "|\n";
    cout << "  |" << WHITE << "    ██║   ██║   ██╔██╗ ██║██╔████╔██║███████╗                              " << CYAN << "|\n";
    cout << "  |" << WHITE << "    ██║   ██║   ██║╚██╗██║██║╚██╔╝██║╚════██║                              " << CYAN << "|\n";
    cout << "  |" << WHITE << "    ██║   ██║   ██║ ╚████║██║ ╚═╝ ██║███████║                              " << CYAN << "|\n";
    cout << "  |" << WHITE << "    ╚═╝   ╚═╝   ╚═╝  ╚═══╝╚═╝     ╚═╝╚══════╝                              " << CYAN << "|\n";
    cout << "  |                                                                            |\n";
    cout << "  |" << YELLOW << "          Intelligent Transport Network Management System                 " << CYAN << "|\n";
    cout << "  |" << DIM << WHITE << "                          Version 1.0                                     " << CYAN << BOLD << "|\n";
    cout << "  |                                                                            |\n";
    cout << "  +============================================================================+\n";
    cout << RESET << "\n";
}

// Clear screen (works on Windows)
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Wait for user to press Enter
void waitForEnter()
{
    cout << "\n"
         << DIM << "  >> Press Enter to continue..." << RESET;
    cin.ignore(10000, '\n');
    cin.get();
}

int main()
{
    enableColors();
    clearScreen();
    displayHeader();

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
        cout << "\n  " << CYAN << ">>" << RESET << " Enter your choice: ";
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
            displaySearchSortMenu(routeManager, vehicleManager, ticketManager);
            break;
        case 8:
            displayHistoryMenu(historyManager, routeManager, vehicleManager);
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
    clearScreen();
    displayHeader();
    cout << GREEN << BOLD;
    cout << "  +========================================================+\n";
    cout << "  |" << WHITE << "                  * MAIN MENU *                        " << GREEN << "|\n";
    cout << "  +========================================================+\n";
    cout << "  |                                                        |\n";
    cout << "  |" << CYAN << "   [1]" << WHITE << "  [STN]  Manage Stations                       " << GREEN << "|\n";
    cout << "  |" << CYAN << "   [2]" << WHITE << "  [RTE]  Manage Routes                         " << GREEN << "|\n";
    cout << "  |" << CYAN << "   [3]" << WHITE << "  [VEH]  Manage Vehicles                       " << GREEN << "|\n";
    cout << "  |" << CYAN << "   [4]" << WHITE << "  [TKT]  Manage Passengers & Tickets           " << GREEN << "|\n";
    cout << "  |" << CYAN << "   [5]" << WHITE << "  [INF]  View System Information               " << GREEN << "|\n";
    cout << "  |" << CYAN << "   [6]" << WHITE << "  [GRF]  Graph Algorithms & Analysis           " << GREEN << "|\n";
    cout << "  |" << CYAN << "   [7]" << WHITE << "  [SRC]  Search & Sort                         " << GREEN << "|\n";
    cout << "  |" << CYAN << "   [8]" << WHITE << "  [HST]  History & Undo                        " << GREEN << "|\n";
    cout << "  |" << RED << "   [9]" << WHITE << "  [EXIT] Exit                                  " << GREEN << "|\n";
    cout << "  |                                                        |\n";
    cout << "  +========================================================+\n";
    cout << RESET;
}

void displayStationMenu(RouteManager &routeManager, HistoryManager &historyManager)
{
    int stationChoice;
    bool stationMenuActive = true;

    while (stationMenuActive)
    {
        clearScreen();
        displayHeader();
        cout << MAGENTA << BOLD;
        cout << "  +========================================================+\n";
        cout << "  |" << WHITE << "              STATION MANAGEMENT                       " << MAGENTA << "|\n";
        cout << "  +========================================================+\n";
        cout << "  |                                                        |\n";
        cout << "  |" << CYAN << "   [1]" << WHITE << "  [+]  Add New Station                         " << MAGENTA << "|\n";
        cout << "  |" << CYAN << "   [2]" << WHITE << "  [-]  Delete Station                          " << MAGENTA << "|\n";
        cout << "  |" << CYAN << "   [3]" << WHITE << "  [=]  Display All Stations                    " << MAGENTA << "|\n";
        cout << "  |" << YELLOW << "   [4]" << WHITE << "  [<]  Back to Main Menu                       " << MAGENTA << "|\n";
        cout << "  |                                                        |\n";
        cout << "  +========================================================+\n";
        cout << RESET;
        cout << "\n  " << CYAN << ">>" << RESET << " Enter choice: ";
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

            cout << "\n"
                 << GREEN << "  +-------------------------------------+" << RESET;
            cout << "\n"
                 << GREEN << "  |" << WHITE << BOLD << "      [+] ADD NEW STATION" << RESET << GREEN << "             |" << RESET;
            cout << "\n"
                 << GREEN << "  +-------------------------------------+" << RESET << "\n";
            cout << "\n  " << CYAN << "Station ID: " << RESET;
            cin >> stationID;
            cin.ignore();

            if (stationID <= 0)
            {
                cout << "ERROR: Station ID must be positive!\n";
                break;
            }

            cout << "  " << CYAN << "Station Name: " << RESET;
            getline(cin, stationName);

            if (stationName.empty())
            {
                cout << RED << "  [X] ERROR: Station name cannot be empty!" << RESET << "\n";
                break;
            }

            cout << "  " << CYAN << "Location (optional): " << RESET;
            getline(cin, location);

            Station newStation(stationID, stationName, location);
            if (routeManager.addStation(newStation))
            {
                cout << "\n"
                     << GREEN << "  [OK] Station added successfully!" << RESET << "\n";
                // Record history for undo
                historyManager.addAction("ADD_STATION:" + to_string(stationID) + ":" + stationName + ":" + location);
            }
            waitForEnter();
            break;
        }
        case 2:
        {
            int deleteID;
            cout << "\n"
                 << RED << "  +-------------------------------------+" << RESET;
            cout << "\n"
                 << RED << "  |" << WHITE << BOLD << "      [-] DELETE STATION" << RESET << RED << "              |" << RESET;
            cout << "\n"
                 << RED << "  +-------------------------------------+" << RESET << "\n";
            cout << "\n  " << CYAN << "Station ID to delete: " << RESET;
            cin >> deleteID;

            if (deleteID <= 0)
            {
                cout << RED << "  [X] ERROR: Station ID must be positive!" << RESET << "\n";
                break;
            }

            if (routeManager.removeStation(deleteID))
            {
                historyManager.addAction("DELETE_STATION:" + to_string(deleteID));
            }
            waitForEnter();
            break;
        }
        case 3:
            cout << "\n";
            routeManager.displayStations();
            waitForEnter();
            break;
        case 4:
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
        clearScreen();
        displayHeader();
        cout << BLUE << BOLD;
        cout << "  +========================================================+\n";
        cout << "  |" << WHITE << "                ROUTE MANAGEMENT                       " << BLUE << "|\n";
        cout << "  +========================================================+\n";
        cout << "  |                                                        |\n";
        cout << "  |" << CYAN << "   [1]" << WHITE << "  [+]  Add New Route                           " << BLUE << "|\n";
        cout << "  |" << CYAN << "   [2]" << WHITE << "  [-]  Delete Route                            " << BLUE << "|\n";
        cout << "  |" << CYAN << "   [3]" << WHITE << "  [=]  Display All Routes                      " << BLUE << "|\n";
        cout << "  |" << YELLOW << "   [4]" << WHITE << "  [<]  Back to Main Menu                       " << BLUE << "|\n";
        cout << "  |                                                        |\n";
        cout << "  +========================================================+\n";
        cout << RESET;
        cout << "\n  " << CYAN << ">>" << RESET << " Enter choice: ";
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
            waitForEnter();
            break;
        }
        case 2:
        {
            int deleteRouteID;
            cout << "\n--- Delete Route ---\n";
            cout << "Enter Route ID to delete: ";
            cin >> deleteRouteID;

            if (deleteRouteID <= 0)
            {
                cout << "ERROR: Route ID must be positive!\n";
                break;
            }

            if (routeManager.removeRouteById(deleteRouteID))
            {
                historyManager.addAction("DELETE_ROUTE:" + to_string(deleteRouteID));
            }
            waitForEnter();
            break;
        }
        case 3:
            cout << "\n";
            routeManager.displayRoutes();
            waitForEnter();
            break;
        case 4:
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
        clearScreen();
        displayHeader();
        cout << YELLOW << BOLD;
        cout << "  +========================================================+\n";
        cout << "  |" << WHITE << "               VEHICLE MANAGEMENT                      " << YELLOW << "|\n";
        cout << "  +========================================================+\n";
        cout << "  |                                                        |\n";
        cout << "  |" << CYAN << "   [1]" << WHITE << "  [+]  Register New Vehicle                    " << YELLOW << "|\n";
        cout << "  |" << CYAN << "   [2]" << WHITE << "  [-]  Delete Vehicle                          " << YELLOW << "|\n";
        cout << "  |" << CYAN << "   [3]" << WHITE << "  [=]  Display All Vehicles                    " << YELLOW << "|\n";
        cout << "  |" << GREEN << "   [4]" << WHITE << "  [<]  Back to Main Menu                       " << YELLOW << "|\n";
        cout << "  |                                                        |\n";
        cout << "  +========================================================+\n";
        cout << RESET;
        cout << "\n  " << CYAN << ">>" << RESET << " Enter choice: ";
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
            waitForEnter();
            break;
        }
        case 2:
        {
            int deleteVehicleID;
            cout << "\n--- Delete Vehicle ---\n";
            cout << "Enter Vehicle ID to delete: ";
            cin >> deleteVehicleID;

            if (deleteVehicleID <= 0)
            {
                cout << "ERROR: Vehicle ID must be positive!\n";
                break;
            }

            vehicleManager.removeVehicle(deleteVehicleID);
            historyManager.addAction("DELETE_VEHICLE:" + to_string(deleteVehicleID));
            waitForEnter();
            break;
        }
        case 3:
            cout << "\n";
            vehicleManager.displayAllVehicles();
            waitForEnter();
            break;
        case 4:
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
        clearScreen();
        displayHeader();
        cout << CYAN << BOLD;
        cout << "  +========================================================+\n";
        cout << "  |" << WHITE << "         PASSENGER & TICKET MANAGEMENT                 " << CYAN << "|\n";
        cout << "  +========================================================+\n";
        cout << "  |                                                        |\n";
        cout << "  |" << GREEN << "   [1]" << WHITE << "  [USR] Add Passenger to Queue                 " << CYAN << "|\n";
        cout << "  |" << GREEN << "   [2]" << WHITE << "  [TKT] Process Next Passenger (Issue Ticket)  " << CYAN << "|\n";
        cout << "  |" << GREEN << "   [3]" << WHITE << "  [QUE] Display Passenger Queue                " << CYAN << "|\n";
        cout << "  |" << GREEN << "   [4]" << WHITE << "  [LST] Display All Issued Tickets             " << CYAN << "|\n";
        cout << "  |" << YELLOW << "   [5]" << WHITE << "  [<]   Back to Main Menu                      " << CYAN << "|\n";
        cout << "  |                                                        |\n";
        cout << "  +========================================================+\n";
        cout << RESET;
        cout << "\n  " << CYAN << ">>" << RESET << " Enter choice: ";
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
            waitForEnter();
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
            ticketManager.processNextPassenger(startID, endID, startName, endName);
            // Update passenger counts at both stations
            routeManager.incrementStationPassengers(startID);
            routeManager.incrementStationPassengers(endID);
            waitForEnter();
            break;
        }
        case 3:
            cout << "\n";
            ticketManager.displayQueue();
            waitForEnter();
            break;
        case 4:
            cout << "\n";
            ticketManager.displayAllTicketsWithNames(RouteManager::getStationNameByIdStatic);
            waitForEnter();
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
        clearScreen();
        displayHeader();
        cout << WHITE << BOLD;
        cout << "  +========================================================+\n";
        cout << "  |" << CYAN << "             VIEW SYSTEM INFORMATION                   " << WHITE << "|\n";
        cout << "  +========================================================+\n";
        cout << "  |                                                        |\n";
        cout << "  |" << GREEN << "   [1]" << RESET << "   Display All Stations                      " << WHITE << BOLD << "|\n";
        cout << "  |" << GREEN << "   [2]" << RESET << "   Display Stations (Sorted by Passengers)   " << WHITE << BOLD << "|\n";
        cout << "  |" << GREEN << "   [3]" << RESET << "   Display All Routes                        " << WHITE << BOLD << "|\n";
        cout << "  |" << GREEN << "   [4]" << RESET << "   Display Routes (Sorted by Distance)       " << WHITE << BOLD << "|\n";
        cout << "  |" << GREEN << "   [5]" << RESET << "   Display All Vehicles                      " << WHITE << BOLD << "|\n";
        cout << "  |" << GREEN << "   [6]" << RESET << "   Display Vehicles (Sorted by Capacity)     " << WHITE << BOLD << "|\n";
        cout << "  |" << GREEN << "   [7]" << RESET << "   Display All Tickets                       " << WHITE << BOLD << "|\n";
        cout << "  |" << GREEN << "   [8]" << RESET << "   Display Passenger Queue                   " << WHITE << BOLD << "|\n";
        cout << "  |" << GREEN << "   [9]" << RESET << "   Show Most Crowded Station                 " << WHITE << BOLD << "|\n";
        cout << "  |" << GREEN << "  [10]" << RESET << "   Show Busiest Route                        " << WHITE << BOLD << "|\n";
        cout << "  |" << GREEN << "  [11]" << RESET << "   Fastest Vehicle Assignment                " << WHITE << BOLD << "|\n";
        cout << "  |" << GREEN << "  [12]" << RESET << "   Traffic Density Prediction                " << WHITE << BOLD << "|\n";
        cout << "  |" << YELLOW << "  [13]" << RESET << "   [<] Back to Main Menu                     " << WHITE << BOLD << "|\n";
        cout << "  |                                                        |\n";
        cout << "  +========================================================+\n";
        cout << RESET;
        cout << "\n  " << CYAN << ">>" << RESET << " Enter choice: ";
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
            waitForEnter();
            break;
        case 2:
            cout << "\n";
            routeManager.displayStationsSortedByPassengers();
            waitForEnter();
            break;
        case 3:
            cout << "\n";
            routeManager.displayRoutes();
            waitForEnter();
            break;
        case 4:
        {
            int sortOrder;
            cout << "\n1. Shortest first\n2. Longest first\nEnter choice: ";
            cin >> sortOrder;
            cout << "\n";
            routeManager.displayRoutesSortedByDistance(sortOrder == 1);
            waitForEnter();
            break;
        }
        case 5:
            cout << "\n";
            vehicleManager.displayAllVehicles();
            waitForEnter();
            break;
        case 6:
        {
            int sortOrder;
            cout << "\n1. Smallest capacity first\n2. Largest capacity first\nEnter choice: ";
            cin >> sortOrder;
            cout << "\n";
            vehicleManager.displayVehiclesSortedByCapacity(sortOrder == 1);
            waitForEnter();
            break;
        }
        case 7:
            cout << "\n";
            ticketManager.displayAllTicketsWithNames(RouteManager::getStationNameByIdStatic);
            waitForEnter();
            break;
        case 8:
            cout << "\n";
            ticketManager.displayQueue();
            waitForEnter();
            break;
        case 9:
            cout << "\n";
            routeManager.showMostCrowdedStation(ticketManager.getAllTickets());
            waitForEnter();
            break;
        case 10:
            cout << "\n";
            routeManager.showBusiestRoute(ticketManager.getAllTickets());
            waitForEnter();
            break;
        case 11:
        {
            int reqPassengers;
            cout << "\nEnter required passenger capacity: ";
            cin >> reqPassengers;
            cout << "\n";
            vehicleManager.assignFastestVehicle(reqPassengers);
            waitForEnter();
            break;
        }
        case 12:
            cout << "\n";
            routeManager.showTrafficDensity(ticketManager.getAllTickets(), 5);
            waitForEnter();
            break;
        case 13:
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
        clearScreen();
        displayHeader();
        cout << MAGENTA << BOLD;
        cout << "  +========================================================+\n";
        cout << "  |" << WHITE << "           GRAPH ALGORITHMS & ANALYSIS                 " << MAGENTA << "|\n";
        cout << "  +========================================================+\n";
        cout << "  |                                                        |\n";
        cout << "  |" << CYAN << "   [1]" << WHITE << "  [BFS] BFS Traversal                          " << MAGENTA << "|\n";
        cout << "  |" << CYAN << "   [2]" << WHITE << "  [DFS] DFS Traversal                          " << MAGENTA << "|\n";
        cout << "  |" << CYAN << "   [3]" << WHITE << "  [DJK] Shortest Path (Dijkstra)               " << MAGENTA << "|\n";
        cout << "  |" << CYAN << "   [4]" << WHITE << "  [MST] Minimum Spanning Tree (Prim's)         " << MAGENTA << "|\n";
        cout << "  |" << CYAN << "   [5]" << WHITE << "  [CYC] Detect Cycle in Network                " << MAGENTA << "|\n";
        cout << "  |" << YELLOW << "   [6]" << WHITE << "  [<]   Back to Main Menu                      " << MAGENTA << "|\n";
        cout << "  |                                                        |\n";
        cout << "  +========================================================+\n";
        cout << RESET;
        cout << "\n  " << CYAN << ">>" << RESET << " Enter choice: ";
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
            waitForEnter();
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
            waitForEnter();
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
            waitForEnter();
            break;
        }
        case 4:
            cout << "\n";
            routeManager.minimumSpanningTree();
            waitForEnter();
            break;
        case 5:
            cout << "\n";
            if (routeManager.detectCycle())
                cout << "Cycle detected in the network!\n";
            else
                cout << "No cycle found in the network.\n";
            waitForEnter();
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
        clearScreen();
        displayHeader();
        cout << BLUE << BOLD;
        cout << "  +========================================================+\n";
        cout << "  |" << WHITE << "                HISTORY & UNDO                         " << BLUE << "|\n";
        cout << "  +========================================================+\n";
        cout << "  |                                                        |\n";
        cout << "  |" << CYAN << "   [1]" << WHITE << "  [LOG] View Action History                    " << BLUE << "|\n";
        cout << "  |" << CYAN << "   [2]" << WHITE << "  [<-]  Undo Last Action                       " << BLUE << "|\n";
        cout << "  |" << CYAN << "   [3]" << WHITE << "  [CLR] Clear History                          " << BLUE << "|\n";
        cout << "  |" << YELLOW << "   [4]" << WHITE << "  [<]   Back to Main Menu                      " << BLUE << "|\n";
        cout << "  |                                                        |\n";
        cout << "  +========================================================+\n";
        cout << RESET;
        cout << "\n  " << CYAN << ">>" << RESET << " Enter choice: ";
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
            waitForEnter();
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

            waitForEnter();
            break;
        }
        case 3:
            historyManager.clearHistory();
            cout << "History cleared." << endl;
            waitForEnter();
            break;
        case 4:
            historyMenuActive = false;
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    }
}

void displaySearchSortMenu(RouteManager &routeManager, VehicleManager &vehicleManager, TicketManager &ticketManager)
{
    int choice;
    bool menuActive = true;

    while (menuActive)
    {
        clearScreen();
        displayHeader();
        cout << GREEN << BOLD;
        cout << "  +========================================================+\n";
        cout << "  |" << WHITE << "                 SEARCH & SORT                         " << GREEN << "|\n";
        cout << "  +========================================================+\n";
        cout << "  |                                                        |\n";
        cout << "  |" << CYAN << "   [1]" << WHITE << "  [STN] Search Station by Name                 " << GREEN << "|\n";
        cout << "  |" << CYAN << "   [2]" << WHITE << "  [RTE] Search Route by Station Names          " << GREEN << "|\n";
        cout << "  |" << CYAN << "   [3]" << WHITE << "  [VEH] Search Vehicle by ID                   " << GREEN << "|\n";
        cout << "  |" << CYAN << "   [4]" << WHITE << "  [TKT] Search Ticket by ID                    " << GREEN << "|\n";
        cout << "  |" << MAGENTA << "   [5]" << WHITE << "  [SRT] Sort Stations by Passengers            " << GREEN << "|\n";
        cout << "  |" << MAGENTA << "   [6]" << WHITE << "  [SRT] Sort Routes by Distance                " << GREEN << "|\n";
        cout << "  |" << MAGENTA << "   [7]" << WHITE << "  [SRT] Sort Vehicles by Capacity              " << GREEN << "|\n";
        cout << "  |" << YELLOW << "   [8]" << WHITE << "  [<]   Back to Main Menu                      " << GREEN << "|\n";
        cout << "  |                                                        |\n";
        cout << "  +========================================================+\n";
        cout << RESET;
        cout << "\n  " << CYAN << ">>" << RESET << " Enter choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            string stationName;
            cout << "\nEnter station name to search: ";
            cin.ignore();
            getline(cin, stationName);
            int stationID = routeManager.findStationIdByName(stationName);
            if (stationID != -1)
            {
                cout << "\nStation found!\n";
                cout << "Station ID: " << stationID << ", Name: " << routeManager.getStationNameById(stationID) << endl;
            }
            else
            {
                cout << "\nStation '" << stationName << "' not found.\n";
            }
            waitForEnter();
            break;
        }
        case 2:
        {
            string startName, endName;
            cout << "\nEnter start station name: ";
            cin.ignore();
            getline(cin, startName);
            cout << "Enter end station name: ";
            getline(cin, endName);
            int startID = routeManager.findStationIdByName(startName);
            int endID = routeManager.findStationIdByName(endName);
            if (startID == -1)
            {
                cout << "\nStart station '" << startName << "' not found.\n";
            }
            else if (endID == -1)
            {
                cout << "\nEnd station '" << endName << "' not found.\n";
            }
            else
            {
                cout << "\nSearching for route from " << startName << " to " << endName << "...\n";
                routeManager.searchRoute(startID, endID);
            }
            waitForEnter();
            break;
        }
        case 3:
        {
            int vehicleID;
            cout << "\nEnter vehicle ID to search: ";
            cin >> vehicleID;
            vehicleManager.searchVehicleById(vehicleID);
            waitForEnter();
            break;
        }
        case 4:
        {
            int ticketID;
            cout << "\nEnter ticket ID to search: ";
            cin >> ticketID;
            ticketManager.searchTicketById(ticketID, RouteManager::getStationNameByIdStatic);
            waitForEnter();
            break;
        }
        case 5:
        {
            cout << "\nSort stations by passenger count:\n";
            cout << "1. Most passengers first (Descending)\n";
            cout << "2. Least passengers first (Ascending)\n";
            cout << "Enter choice: ";
            int sortOrder;
            cin >> sortOrder;
            cout << "\n";
            routeManager.displayStationsSortedByPassengers(sortOrder == 2);
            waitForEnter();
            break;
        }
        case 6:
        {
            cout << "\nSort routes by distance:\n";
            cout << "1. Shortest first (Ascending)\n";
            cout << "2. Longest first (Descending)\n";
            cout << "Enter choice: ";
            int sortOrder;
            cin >> sortOrder;
            cout << "\n";
            routeManager.displayRoutesSortedByDistance(sortOrder == 1);
            waitForEnter();
            break;
        }
        case 7:
        {
            cout << "\nSort vehicles by capacity:\n";
            cout << "1. Smallest capacity first (Ascending)\n";
            cout << "2. Largest capacity first (Descending)\n";
            cout << "Enter choice: ";
            int sortOrder;
            cin >> sortOrder;
            cout << "\n";
            vehicleManager.displayVehiclesSortedByCapacity(sortOrder == 1);
            waitForEnter();
            break;
        }
        case 8:
            menuActive = false;
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    }
}
