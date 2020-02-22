#pragma once
#include <set>
#include <string>
#include <map>
#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>
#include "date.h"
using namespace std;



ostream& operator<< (ostream& os, const pair<Date, string>& p);

class Database {
public:
    void AddEvent(const Date& date, const string& event);

    bool DeleteEvent(const Date& date, const string& event);

    int DeleteDate(const Date& date);
    
    void Add(const Date& date, const string& event);

    template <class Predicate>
    vector<pair<Date, string>> FindIf(Predicate func) const {
        vector<pair<Date, string>> v;
        for (const auto& i : time_ordered_storage) {
            /*for (const auto& i2 : i.second) {
                if (func(i.first, i2)) {
                    pair<Date, string> p(i.first, i2);
                    v.push_back(p);
                }
            }*/
            auto predicate = [i, &func](const string& event) {
                return func(i.first, event);
            };
            /*auto it = find_if(begin(i.second), end(i.second), predicate);
            while (it != end(i.second)) {
                v.push_back(make_pair(i.first, *it));
                ++it;
                it = find_if(it, end(i.second), predicate);
            }*/
            for (auto it = find_if(begin(i.second), end(i.second), predicate); it != end(i.second); 
                it = find_if(next(it), end(i.second), predicate)) {
                v.push_back(make_pair(i.first, *it));
            }
        }
        return v;
    };
    template <class Predicate>
    int RemoveIf(Predicate func) {
        int num = 0;
        map<Date, vector<string>::iterator> to_be_deleted;
        for (auto& i : time_ordered_storage) {
            auto predicate = [&func, i](const string& event) {
                return !func(i.first, event);
            };
            auto it = stable_partition(begin(i.second), end(i.second), predicate);
            to_be_deleted[i.first] = it;
        }
        for (auto& i : to_be_deleted) {
            num += end(time_ordered_storage[i.first]) - i.second;
            time_ordered_storage[i.first].erase(i.second, end(time_ordered_storage[i.first]));
            storage[i.first] = set<string>(begin(time_ordered_storage[i.first]), end(time_ordered_storage[i.first]));
            if (storage[i.first].empty()) {
                storage.erase(i.first);
                time_ordered_storage.erase(i.first);
            }
        }
        return num;
    }

    set<string> Find(const Date& date) const;

    void Print() const;
    void Print(ostream& os) const;
    pair<Date, string> Last(Date date) const;
private:
    map<Date, set<string>> storage;
    map<Date, vector<string>> time_ordered_storage;
};
