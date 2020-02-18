#pragma once
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

istream& operator >> (istream& is, Query& q);