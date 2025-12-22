#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <iostream>
#include "../ds/array.h"
#include "../ds/pair.h"
#include "../ds/heap.h"
#include "../models/station.h"
#include "../models/route.h"
#include "../models/vehicle.h"
#include "../models/ticket.h"
using namespace std;

// Define INT_MAX replacement to avoid <limits>
#ifndef INT_MAX_VALUE
#define INT_MAX_VALUE 2147483647
#endif

class Analytics
{
public:
    // Find the station with the most passengers
    static Station mostCrowdedStation(const DynamicArray<Station> &stations)
    {
        if (stations.size() == 0)
        {
            cerr << "Error: No stations available" << endl;
            return Station();
        }

        int maxIdx = 0;
        for (int i = 1; i < stations.size(); i++)
        {
            if (stations[i].getPassengerCount() > stations[maxIdx].getPassengerCount())
                maxIdx = i;
        }
        return stations[maxIdx];
    }

    // Busiest route based on ticket counts (start->end frequency)
    static void busiestRouteByTickets(const DynamicArray<Route> &routes,
                                      const DynamicArray<Ticket> &tickets,
                                      string (*getStationName)(int))
    {
        if (routes.size() == 0)
        {
            cout << "No routes available." << endl;
            return;
        }
        if (tickets.size() == 0)
        {
            cout << "No tickets issued yet. Cannot determine busiest route." << endl;
            return;
        }

        // Store route keys and counts
        DynamicArray<Pair<int, int>> routeKeys; // {startID, endID}
        DynamicArray<int> routeCounts;

        for (int i = 0; i < routes.size(); i++)
        {
            routeKeys.push_back(Pair<int, int>(routes[i].getStartStationID(), routes[i].getEndStationID()));
            routeCounts.push_back(0);
        }

        for (int i = 0; i < tickets.size(); i++)
        {
            int startID = tickets[i].getStartStationID();
            int endID = tickets[i].getEndStationID();
            for (int j = 0; j < routeKeys.size(); j++)
            {
                if (routeKeys[j].first == startID && routeKeys[j].second == endID)
                {
                    routeCounts[j]++;
                    break;
                }
            }
        }

        int maxCount = 0;
        int busiestIdx = -1;
        for (int i = 0; i < routeCounts.size(); i++)
        {
            if (routeCounts[i] > maxCount)
            {
                maxCount = routeCounts[i];
                busiestIdx = i;
            }
        }

        if (busiestIdx == -1)
        {
            cout << "No route activity recorded." << endl;
            return;
        }

        cout << "Busiest Route: " << getStationName(routeKeys[busiestIdx].first) << " -> " << getStationName(routeKeys[busiestIdx].second)
             << " | Tickets: " << maxCount << endl;
    }

    // Fastest vehicle assignment: choose smallest-capacity vehicle that fits requirement
    static void fastestVehicleAssignment(const DynamicArray<Vehicle> &vehicles, int requiredPassengers)
    {
        if (vehicles.size() == 0)
        {
            cout << "No vehicles available." << endl;
            return;
        }

        // Find vehicle with minimum capacity >= requiredPassengers
        int bestIdx = -1;
        int bestCap = INT_MAX_VALUE;
        for (int i = 0; i < vehicles.size(); i++)
        {
            int cap = vehicles[i].getCapacity();
            if (cap >= requiredPassengers && cap < bestCap)
            {
                bestCap = cap;
                bestIdx = i;
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
        for (int i = 1; i < vehicles.size(); i++)
            if (vehicles[i].getCapacity() > vehicles[largestIdx].getCapacity())
                largestIdx = i;

        cout << "No vehicle with sufficient capacity found; fallback assigned: " << vehicles[largestIdx].getName()
             << " (ID: " << vehicles[largestIdx].getID() << ") | Capacity: " << vehicles[largestIdx].getCapacity() << endl;
    }

    // Traffic density prediction using ticket activity (rank stations)
    static void trafficDensityPrediction(const DynamicArray<Station> &stations,
                                         const DynamicArray<Ticket> &tickets,
                                         string (*getStationName)(int),
                                         int topN = 5)
    {
        if (stations.size() == 0)
        {
            cout << "No stations available." << endl;
            return;
        }

        // Count activity per station
        DynamicArray<int> stationIDs;
        DynamicArray<int> activity;
        for (int i = 0; i < stations.size(); i++)
        {
            stationIDs.push_back(stations[i].getID());
            activity.push_back(0);
        }

        for (int i = 0; i < tickets.size(); i++)
        {
            int startID = tickets[i].getStartStationID();
            int endID = tickets[i].getEndStationID();
            for (int j = 0; j < stationIDs.size(); j++)
            {
                if (stationIDs[j] == startID)
                    activity[j]++;
                if (stationIDs[j] == endID)
                    activity[j]++;
            }
        }

        // Sort by activity (simple selection sort for top N)
        cout << "Top " << topN << " stations by predicted traffic density:\\n";
        DynamicArray<bool> used(stations.size());
        for (int i = 0; i < stations.size(); i++)
            used.push_back(false);

        for (int n = 0; n < topN && n < stations.size(); n++)
        {
            int maxIdx = -1;
            for (int i = 0; i < activity.size(); i++)
            {
                if (!used[i] && (maxIdx == -1 || activity[i] > activity[maxIdx]))
                    maxIdx = i;
            }
            if (maxIdx == -1)
                break;
            used[maxIdx] = true;
            cout << n + 1 << ". " << getStationName(stationIDs[maxIdx]) << " (ID: " << stationIDs[maxIdx] << ") - Activity: " << activity[maxIdx] << "\\n";
        }
    }

    // Daily usage trends
    static void dailyUsageTrends(const DynamicArray<Ticket> &tickets)
    {
        if (tickets.size() == 0)
        {
            cout << "No tickets issued yet." << endl;
            return;
        }

        // Count tickets per date
        DynamicArray<string> dates;
        DynamicArray<int> counts;

        for (int i = 0; i < tickets.size(); i++)
        {
            string date = tickets[i].getIssueDate();
            int found = -1;
            for (int j = 0; j < dates.size(); j++)
            {
                if (dates[j] == date)
                {
                    found = j;
                    break;
                }
            }
            if (found == -1)
            {
                dates.push_back(date);
                counts.push_back(1);
            }
            else
            {
                counts[found]++;
            }
        }

        // Simple sort by date string (lexicographic)
        for (int i = 0; i < dates.size() - 1; i++)
        {
            for (int j = i + 1; j < dates.size(); j++)
            {
                if (dates[j] < dates[i])
                {
                    // Swap
                    string tmpD = dates[i];
                    dates[i] = dates[j];
                    dates[j] = tmpD;
                    int tmpC = counts[i];
                    counts[i] = counts[j];
                    counts[j] = tmpC;
                }
            }
        }

        cout << "Daily Usage Trends (date -> tickets):\\n";
        for (int i = 0; i < dates.size(); i++)
        {
            cout << dates[i] << " -> " << counts[i] << "\\n";
        }
    }

    // Total passengers across all stations
    static int totalPassengers(const DynamicArray<Station> &stations)
    {
        int total = 0;
        for (int i = 0; i < stations.size(); i++)
            total += stations[i].getPassengerCount();
        return total;
    }

    // Find most crowded station based on ticket activity
    static void mostCrowdedStationByTickets(const DynamicArray<Station> &stations,
                                            const DynamicArray<Ticket> &tickets,
                                            string (*getStationName)(int))
    {
        if (stations.size() == 0)
        {
            cout << "No stations available." << endl;
            return;
        }

        if (tickets.size() == 0)
        {
            cout << "No tickets issued yet. Cannot determine crowded station." << endl;
            return;
        }

        // Count departures and arrivals per station
        DynamicArray<int> stationIDs;
        DynamicArray<int> stationActivity;
        for (int i = 0; i < stations.size(); i++)
        {
            stationIDs.push_back(stations[i].getID());
            stationActivity.push_back(0);
        }

        for (int i = 0; i < tickets.size(); i++)
        {
            int startID = tickets[i].getStartStationID();
            int endID = tickets[i].getEndStationID();
            for (int j = 0; j < stationIDs.size(); j++)
            {
                if (startID > 0 && stationIDs[j] == startID)
                    stationActivity[j]++;
                if (endID > 0 && stationIDs[j] == endID)
                    stationActivity[j]++;
            }
        }

        // Find station with max activity
        int maxActivity = 0;
        int busiestStationID = -1;
        for (int i = 0; i < stationActivity.size(); i++)
        {
            if (stationActivity[i] > maxActivity)
            {
                maxActivity = stationActivity[i];
                busiestStationID = stationIDs[i];
            }
        }

        if (busiestStationID == -1)
        {
            cout << "Could not determine busiest station." << endl;
            return;
        }

        // Display result
        cout << "\\n===== MOST CROWDED STATION =====\\n";
        cout << "Station: " << getStationName(busiestStationID) << " (ID: " << busiestStationID << ")\\n";
        cout << "Total Activity: " << maxActivity << " (departures + arrivals)\\n";

        // Breakdown
        int departures = 0, arrivals = 0;
        for (int i = 0; i < tickets.size(); i++)
        {
            if (tickets[i].getStartStationID() == busiestStationID)
                departures++;
            if (tickets[i].getEndStationID() == busiestStationID)
                arrivals++;
        }
        cout << "  - Departures: " << departures << "\\n";
        cout << "  - Arrivals: " << arrivals << "\\n";
        cout << "================================\\n"
             << endl;
    }
};

#endif
