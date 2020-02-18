// UnitBuses.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <unordered_map>
using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

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

struct BusesForStopResponse {
    vector<string> Buses;
    string Stop;
};

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

struct StopsForBusResponse {
    bool Flag = false;
    vector<pair<string, vector<string>>> container;
    //map<string, vector<string>> container;
    //unordered_map <string, vector<string>> container;
    string bus;
};

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

struct AllBusesResponse {
    bool Flag = false;
    map <string, vector<string>> bts;
};

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

class BusManager {
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
    //map<string, vector<string>> buses_to_stops;
    //unordered_map<string, vector<string>> stops_to_buses;
public:
    void AddBus(const string& bus, const vector<string>& stops) {
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

    BusesForStopResponse GetBusesForStop(const string& stop) const {
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

    StopsForBusResponse GetStopsForBus(const string& bus) const {
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

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse res;
        if (buses_to_stops.size() != 0) {
            res.Flag = true;
            for (const auto& i : buses_to_stops) {
                res.bts[i.first] = i.second;
            }
        }
        return res;
    }
};

// РќРµ РјРµРЅСЏСЏ С‚РµР»Р° С„СѓРЅРєС†РёРё main, СЂРµР°Р»РёР·СѓР№С‚Рµ С„СѓРЅРєС†РёРё Рё РєР»Р°СЃСЃС‹ РІС‹С€Рµ

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
