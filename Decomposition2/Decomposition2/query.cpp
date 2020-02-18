#include "query.h"

istream& operator >> (istream& is, Query& q) {
    q.stops.clear();
    string s;
    is >> s;
    if (s == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        string temp;
        while (stop_count > 0) {
            stop_count--;
            is >> temp;
            q.stops.push_back(temp);
        }
    }
    if (s == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    if (s == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    if (s == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }

    return is;
}