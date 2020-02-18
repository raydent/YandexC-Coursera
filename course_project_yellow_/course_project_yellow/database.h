#pragma once
#include <set>
#include <string>
#include <map>
#include "date.h"
#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>
using namespace std;



ostream& operator<< (ostream& os, pair<Date, string> p) {
    os << p.first << " " << p.second;
    return os;
}
class Database {
public:
    void AddEvent(const Date& date, const string& event);

    bool DeleteEvent(const Date& date, const string& event);

    int DeleteDate(const Date& date);
    
    void Add(const Date& date, const string& event);

    /*template <typename Func>
    vector<pair<Date, string>> FindIf(Func func(Date d, string s)) {
        vector<pair<Date, string>>;
        for (const auto& i : storage) {
            if (func(i.first, i.second)) {
                v.push_back(i);
            }
        }
        return v;
    };*/
    vector<pair<Date, string>> FindIf(const function<bool(Date, string)>& func);
    int RemoveIf(const function<bool(Date, string)>& func);
    set<string> Find(const Date& date) const;

    void Print() const;
    void Print(ostream& os) const;
    auto Last(Date date);
private:
    map<Date, set<string>> storage;
    map<Date, vector<string>> time_ordered_storage;
};
