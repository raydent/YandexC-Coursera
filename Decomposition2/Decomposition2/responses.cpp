#include "responses.h"

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.Buses.size() == 0) {
        os << "No stop" << endl;
    }
    else {
        //os << "Stop " << r.Stop << ":";
        for (const auto& i : r.Buses) {
            os << i << " ";
        }
        os << endl;
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.Flag == false) {
        os << "No bus" << endl;
    }
    else {
        for (const auto& i : r.container) {
            os << "Stop " << i.first << ": ";
            if (i.second.size() == 1) {
                os << "no interchange";
            }
            else {
                for (const auto& bus_item : i.second) {
                    if (bus_item != r.bus) {
                        os << bus_item << " ";
                    }
                }
            }
            os << endl;
        }
    }
    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.Flag == false) {
        os << "No buses" << endl;
    }
    else {
        for (const auto& bus_item : r.bts) {
            os << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                os << stop << " ";
            }
            os << endl;
        }
    }
    return os;
}