#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    /*for (const auto& i : stops) {
        buses_to_stops[bus].push_back(i);
    }*/
    for (const auto& i : stops) {
        stops_to_buses[i].push_back(bus);
    }
    /*for (const auto& i : buses_to_stops) {
        cout << i.first << " ";
        for (const auto i2 : i.second) {
            cout << i2 << " ";
        }
        cout << endl;
    }
    for (const auto& i : stops_to_buses) {
        cout << i.first << " ";
        for (const auto i2 : i.second) {
            cout << i2 << " ";
        }
        cout << endl;
    }*/
}
BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse res;
    if (stops_to_buses.count(stop) == 0) {
        res.Buses.resize(0);
    }
    else {
        res.Stop = stop;
        for (auto& i : stops_to_buses.at(stop)) {
            res.Buses.push_back(i);
        }
    }
    return res;
}
StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    StopsForBusResponse res;
    if (buses_to_stops.count(bus) == 0) {
        res.Flag = false;
    }
    else {
        res.Flag = true;
        res.bus = bus;
        for (const auto& i : buses_to_stops.at(bus)) {
            //res.container[i] = stops_to_buses.at(i);
            res.container.push_back(make_pair(i, stops_to_buses.at(i)));
            // res.container.push_back(stops_to_buses.at(i));
        }
    }
    return res;
}
AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse res;
    if (buses_to_stops.size() != 0) {
        res.Flag = true;
        for (const auto& i : buses_to_stops) {
            res.bts[i.first] = i.second;
        }
    }
    return res;
}