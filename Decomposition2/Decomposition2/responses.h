#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <unordered_map>
using namespace std;

struct BusesForStopResponse {
    vector<string> Buses;
    string Stop;
};

struct StopsForBusResponse {
    bool Flag = false;
    vector<pair<string, vector<string>>> container;
    //map<string, vector<string>> container;
    //unordered_map <string, vector<string>> container;
    string bus;
};
struct AllBusesResponse {
    bool Flag = false;
    map <string, vector<string>> bts;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);
ostream& operator << (ostream& os, const StopsForBusResponse& r);
ostream& operator << (ostream& os, const AllBusesResponse& r);