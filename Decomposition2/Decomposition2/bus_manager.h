#pragma once
#include "responses.h"


class BusManager {
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
    //map<string, vector<string>> buses_to_stops;
    //unordered_map<string, vector<string>> stops_to_buses;
public:
    void AddBus(const string& bus, const vector<string>& stops);

    BusesForStopResponse GetBusesForStop(const string& stop) const;

    StopsForBusResponse GetStopsForBus(const string& bus) const;

    AllBusesResponse GetAllBuses() const;
};