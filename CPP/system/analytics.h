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

    // Busiest route based on ticket counts (start->end frequency)
    static void busiestRouteByTickets(const vector<Route> &routes,
                                      const vector<Ticket> &tickets,
                                      function<string(int)> getStationName)
    {
        if (routes.empty())
        {
            cout << "No routes available." << endl;
            return;
        }
        if (tickets.empty())
        {
            cout << "No tickets issued yet. Cannot determine busiest route." << endl;
            return;
        }

        map<pair<int, int>, int> routeCount;
        for (const auto &r : routes)
            routeCount[{r.getStartStationID(), r.getEndStationID()}] = 0;

        for (const auto &t : tickets)
        {
            pair<int, int> key = {t.getStartStationID(), t.getEndStationID()};
            if (routeCount.find(key) != routeCount.end())
                routeCount[key]++;
        }

        int maxCount = 0;
        pair<int, int> busiest = {-1, -1};
        for (const auto &entry : routeCount)
        {
            if (entry.second > maxCount)
            {
                maxCount = entry.second;
                busiest = entry.first;
            }
        }

        if (busiest.first == -1)
        {
            cout << "No route activity recorded." << endl;
            return;
        }

        cout << "Busiest Route: " << getStationName(busiest.first) << " -> " << getStationName(busiest.second)
             << " | Tickets: " << maxCount << endl;
    }

    // Fastest vehicle assignment: choose smallest-capacity vehicle that fits requirement (min-heap logic)
    static void fastestVehicleAssignment(const vector<Vehicle> &vehicles, int requiredPassengers)
    {
        if (vehicles.empty())
        {
            cout << "No vehicles available." << endl;
            return;
        }

        // Find vehicle with minimum capacity >= requiredPassengers
        int bestIdx = -1;
        int bestCap = std::numeric_limits<int>::max();
        for (size_t i = 0; i < vehicles.size(); ++i)
        {
            int cap = vehicles[i].getCapacity();
            if (cap >= requiredPassengers && cap < bestCap)
            {
                bestCap = cap;
                bestIdx = (int)i;
            }
        }

        if (bestIdx != -1)
        {
            cout << "Assigned Vehicle: " << vehicles[bestIdx].getName() << " (ID: " << vehicles[bestIdx].getID() << ")"
                 << " | Capacity: " << vehicles[bestIdx].getCapacity() << endl;
            return;
        }

        // If none fit exactly, pick the largest available (fallback)
        int largestIdx = 0;
        for (size_t i = 1; i < vehicles.size(); ++i)
            if (vehicles[i].getCapacity() > vehicles[largestIdx].getCapacity())
                largestIdx = (int)i;

        cout << "No vehicle with sufficient capacity found; fallback assigned: " << vehicles[largestIdx].getName()
             << " (ID: " << vehicles[largestIdx].getID() << ") | Capacity: " << vehicles[largestIdx].getCapacity() << endl;
    }

    // Traffic density prediction using ticket activity (rank stations via max-heap)
    static void trafficDensityPrediction(const vector<Station> &stations,
                                         const vector<Ticket> &tickets,
                                         function<string(int)> getStationName,
                                         int topN = 5)
    {
        if (stations.empty())
        {
            cout << "No stations available." << endl;
            return;
        }

        map<int, int> activity;
        for (const auto &s : stations)
            activity[s.getID()] = 0;
        for (const auto &t : tickets)
        {
            if (activity.find(t.getStartStationID()) != activity.end())
                activity[t.getStartStationID()]++;
            if (activity.find(t.getEndStationID()) != activity.end())
                activity[t.getEndStationID()]++;
        }

        // Use a max-heap (priority_queue) to get top stations by activity
        priority_queue<pair<int, int>> pq; // {count, stationID}
        for (const auto &entry : activity)
            pq.push({entry.second, entry.first});

        cout << "Top " << topN << " stations by predicted traffic density:\n";
        for (int i = 0; i < topN && !pq.empty(); ++i)
        {
            auto p = pq.top();
            pq.pop();
            cout << i + 1 << ". " << getStationName(p.second) << " (ID: " << p.second << ") - Activity: " << p.first << "\n";
        }
    }

    // Daily usage trends using BST-like ordered map traversal
    static void dailyUsageTrends(const vector<Ticket> &tickets)
    {
        if (tickets.empty())
        {
            cout << "No tickets issued yet." << endl;
            return;
        }

        // Count tickets per date
        map<string, int> counts; // std::map is ordered (BST)
        for (const auto &t : tickets)
            counts[t.getIssueDate()]++;

        cout << "Daily Usage Trends (date -> tickets):\n";
        for (const auto &entry : counts)
        {
            cout << entry.first << " -> " << entry.second << "\n";
        }
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
