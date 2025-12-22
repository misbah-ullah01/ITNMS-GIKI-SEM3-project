#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <functional>
#include "../models/station.h"
#include "../models/route.h"
#include "../models/vehicle.h"
#include "../models/ticket.h"
using namespace std;

class Analytics
{
public:
    // Find the station with the most passengers
    static Station mostCrowdedStation(const vector<Station> &stations)
    {
        if (stations.empty())
            throw runtime_error("No stations available");

        return *max_element(stations.begin(), stations.end(),
                            [](const Station &a, const Station &b)
                            {
                                return a.getPassengerCount() < b.getPassengerCount();
                            });
    }

    // Total passengers across all stations
    static int totalPassengers(const vector<Station> &stations)
    {
        int total = 0;
        for (const auto &station : stations)
            total += station.getPassengerCount();
        return total;
    }

    // Find most crowded station based on ticket activity
    static void mostCrowdedStationByTickets(const vector<Station> &stations,
                                            const vector<Ticket> &tickets,
                                            function<string(int)> getStationName)
    {
        if (stations.empty())
        {
            cout << "No stations available." << endl;
            return;
        }

        if (tickets.empty())
        {
            cout << "No tickets issued yet. Cannot determine crowded station." << endl;
            return;
        }

        // Count departures and arrivals per station
        map<int, int> stationActivity;
        for (const auto &s : stations)
        {
            stationActivity[s.getID()] = 0;
        }

        for (const auto &ticket : tickets)
        {
            int startID = ticket.getStartStationID();
            int endID = ticket.getEndStationID();

            if (startID > 0 && stationActivity.find(startID) != stationActivity.end())
            {
                stationActivity[startID]++; // Departure
            }
            if (endID > 0 && stationActivity.find(endID) != stationActivity.end())
            {
                stationActivity[endID]++; // Arrival
            }
        }

        // Find station with max activity
        int maxActivity = 0;
        int busiestStationID = -1;
        for (const auto &entry : stationActivity)
        {
            if (entry.second > maxActivity)
            {
                maxActivity = entry.second;
                busiestStationID = entry.first;
            }
        }

        if (busiestStationID == -1)
        {
            cout << "Could not determine busiest station." << endl;
            return;
        }

        // Display result
        cout << "\n===== MOST CROWDED STATION =====" << endl;
        cout << "Station: " << getStationName(busiestStationID) << " (ID: " << busiestStationID << ")" << endl;
        cout << "Total Activity: " << maxActivity << " (departures + arrivals)" << endl;

        // Breakdown
        int departures = 0, arrivals = 0;
        for (const auto &ticket : tickets)
        {
            if (ticket.getStartStationID() == busiestStationID)
                departures++;
            if (ticket.getEndStationID() == busiestStationID)
                arrivals++;
        }
        cout << "  - Departures: " << departures << endl;
        cout << "  - Arrivals: " << arrivals << endl;
        cout << "================================\n"
             << endl;
    }
};

#endif
