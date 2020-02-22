#include "database.h"


ostream& operator<< (ostream& os, const pair<Date, string>& p) {
    os << p.first << " " << p.second;
    return os;
}

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
    for (const auto& item : time_ordered_storage) {
        for (const string& event : item.second) {
            cout << item.first << " " << event << endl;
        }
    }
}
void Database::Print(ostream& os) const {
    for (const auto& i : time_ordered_storage) {
        for (const auto& i2 : i.second) {
            os << i.first << " " << i2 << endl;
        }
    }
}
pair<Date, string> Database::Last(Date date) const {
    if (time_ordered_storage.empty() || date < time_ordered_storage.begin()->first) {
        throw invalid_argument("No entries");
    }
    auto it = prev(time_ordered_storage.upper_bound(date));
    return make_pair(it->first, it->second.back());
}