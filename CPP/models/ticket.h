#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include "passenger.h"
#include "route.h"

using namespace std;

class Ticket
{
private:
    int ticketID;
    Passenger passenger;
    string issueDate;
    int startStationID;
    int endStationID;

public:
    Ticket() : ticketID(0), passenger(Passenger(0, "", 0)), issueDate(""), startStationID(0), endStationID(0) {}
    // Constructor
    Ticket(int _id, Passenger _p, int _start = 0, int _end = 0)
        : ticketID(_id), passenger(_p), issueDate("2024-12-22"),
          startStationID(_start), endStationID(_end) {}

    // Getters
    int getTicketID() const { return ticketID; }
    Passenger getPassenger() const { return passenger; }
    string getIssueDate() const { return issueDate; }
    int getStartStationID() const { return startStationID; }
    int getEndStationID() const { return endStationID; }

    // Display ticket info (with station label provider if available)
    void display() const
    {
        cout << "Ticket ID: " << ticketID << " | ";
        passenger.display();
        if (startStationID > 0 && endStationID > 0)
        {
            cout << "    Route: Station " << startStationID << " -> Station " << endStationID << endl;
        }
    }

    // Display with station names
    void displayWithNames(const string &startName, const string &endName) const
    {
        cout << "Ticket ID: " << ticketID << " | ";
        passenger.display();
        if (startStationID > 0 && endStationID > 0)
        {
            cout << "    Route: " << startName << " -> " << endName << endl;
        }
    }

    // Comparison operator
    bool operator==(const Ticket &other) const
    {
        return ticketID == other.ticketID;
    }
};

#endif
