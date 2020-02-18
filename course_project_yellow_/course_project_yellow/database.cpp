#include "database.h"



void Database::AddEvent(const Date& date, const string& event) {
    storage[date].insert(event);
}
void Database::Add(const Date& date, const string& event) {
    if (storage[date].count(event) == 0) {
        storage[date].insert(event);
        time_ordered_storage[date].push_back(event);
    }
}
bool Database::DeleteEvent(const Date& date, const string& event) {
    if (storage.count(date) > 0 && storage[date].count(event) > 0) {
        storage[date].erase(event);
        return true;
    }
    return false;
}
vector<pair<Date, string>> Database::FindIf(const function<bool(Date, string)>& func) {
    vector<pair<Date, string>> v;
    for (const auto& i : time_ordered_storage) {
        for (const auto& i2 : i.second) {
            if (func(i.first, i2)) {
                pair<Date, string> p(i.first, i2);
                v.push_back(p);
            }
        }
    }
    return v;
}
int Database::RemoveIf(const function<bool(Date, string)>& func) {
    int num = 0;
    for (const auto& i : storage) {
        stable_partition(begin(time_ordered_storage[i.first]), end(time_ordered_storage[i.first]), [i](const auto& i2) {
            return func(i.first, i2)});
        auto it1 = lower_bound(begin(time_ordered_storage[i.first]), end(time_ordered_storage[i.first]), true, [i](const auto& i2) {
            return func(i.first, i2)});
        while (it1 != end(time_ordered_storage[i.first])) {
            auto it2 = upper_bound(begin(time_ordered_storage[i.first]), end(time_ordered_storage[i.first]), true, [i](const auto& i2) {
                return func(i.first, i2)});
            auto tempit = it1;
            while (tempit != it2) {
                num++;
                storage[i.first].erase(*tempit);
                tempit++;
            }
            time_ordered_storage[i].erase(it1, it2);
            auto it1 = lower_bound(begin(time_ordered_storage[i.first]), end(time_ordered_storage[i.first]), true, [i](const auto& i2) {
                return func(i.first, i2)});
        }
        if (storage[i.first].size() == 0) {
            storage.erase(i.first);
        }
        if (time_ordered_storage[i.first].size() == 0) {
            time_ordered_storage.erase(i.first);
        }
    }
    return num;
}
int Database::DeleteDate(const Date& date) {
    if (storage.count(date) == 0) {
        return 0;
    }
    else {
        const int event_count = storage[date].size();
        storage.erase(date);
        return event_count;
    }
}
set<string> Database::Find(const Date& date) const {
    if (storage.count(date) > 0) {
        return storage.at(date);
    }
    else {
        return {};
    }
}
void Database::Print() const {
    for (const auto& item : storage) {
        for (const string& event : item.second) {
            cout << item.first << " " << event << endl;
        }
    }
}
void Database::Print(ostream& os) const {
    for (const auto& i : storage) {
        for (const auto& i2 : i.second) {
            os << i.first << " " << i2 << endl;
        }
    }
}
auto Database::Last(Date date) {
    auto it = time_ordered_storage.lower_bound(date);
    stringstream ss;
    if (it == begin(time_ordered_storage)) {
        //pair<Date, string> p(it->first, it->second.back());
        //ss << make_pair<it->first, it->second.back()>;
        //ss << p;
        throw invalid_argument("No entries");
        //ss << "No entries";
        //return ss;
    }
    else {
        it--;
        pair<Date, string> p(it->first, it->second.back());
        ss << p;
        return p;
    }
}