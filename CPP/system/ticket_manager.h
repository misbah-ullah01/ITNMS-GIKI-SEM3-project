#ifndef TICKET_MANAGER_H
#define TICKET_MANAGER_H

#include <iostream>
#include "../ds/queue.h"
#include "../ds/array.h"
#include "../models/passenger.h"
#include "../models/ticket.h"

using namespace std;

class TicketManager
{
private:
    Queue<Passenger> passengerQueue;    // FIFO queue for passengers
    DynamicArray<Ticket> ticketsIssued; // Store all issued tickets
    int nextTicketID = 1;               // Auto-increment ticket ID

public:
    // Add passenger to queue
    void addPassengerToQueue(const Passenger &p)
    {
        passengerQueue.push(p);
        cout << "Passenger added to queue: " << p.getName() << endl;
    }

    // Process next passenger in queue with route information
    void processNextPassenger(int startStationID = 0, int endStationID = 0)
    {
        if (passengerQueue.empty())
        {
            cout << "No passengers in queue." << endl;
            return;
        }

        Passenger p = passengerQueue.front();
        passengerQueue.pop();

        Ticket t(nextTicketID++, p, startStationID, endStationID);
        ticketsIssued.push_back(t);

        cout << "Ticket issued for passenger: " << p.getName()
             << " | Ticket ID: " << t.getTicketID();
        if (startStationID > 0 && endStationID > 0)
        {
            cout << " | Route: " << startStationID << " -> " << endStationID;
        }
        cout << endl;
    }

    // Display all passengers waiting in queue
    void displayQueue()
    {
        if (passengerQueue.empty())
        {
            cout << "Passenger queue is empty." << endl;
            return;
        }

        Queue<Passenger> tempQueue = passengerQueue; // copy to preserve original
        cout << "Passengers in queue:" << endl;
        while (!tempQueue.empty())
        {
            cout << "- " << tempQueue.front().getName() << endl;
            tempQueue.pop();
        }
    }

    // Display all issued tickets
    void displayAllTickets()
    {
        if (ticketsIssued.empty())
        {
            cout << "No tickets issued yet." << endl;
            return;
        }

        cout << "Issued Tickets:" << endl;
        for (int i = 0; i < ticketsIssued.size(); i++)
        {
            ticketsIssued[i].display();
        }
    }

    // Get total number of tickets issued
    int totalTicketsIssued() const
    {
        return ticketsIssued.size();
    }

    // Display tickets with station names (uses function pointer instead of std::function)
    void displayAllTicketsWithNames(string (*getStationName)(int)) const
    {
        if (ticketsIssued.empty())
        {
            cout << "No tickets issued yet." << endl;
            return;
        }

        cout << "Issued Tickets:" << endl;
        for (int i = 0; i < ticketsIssued.size(); i++)
        {
            const Ticket &t = ticketsIssued[i];
            if (t.getStartStationID() > 0 && t.getEndStationID() > 0)
            {
                t.displayWithNames(getStationName(t.getStartStationID()),
                                   getStationName(t.getEndStationID()));
            }
            else
            {
                t.display();
            }
        }
    }

    // Get all tickets (for analytics)
    const DynamicArray<Ticket> &getAllTickets() const
    {
        return ticketsIssued;
    }
};

#endif
