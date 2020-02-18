// sqr.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;


template <typename T1, typename T2>
pair<T1, T2> operator * (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs);
template <typename Key, typename Value>
map<Key, Value> operator * (const map<Key, Value>& lhs, const map<Key, Value>& rhs);
template <typename T>
vector<T> operator * (const vector<T>& lhs, const vector<T>& rhs);
template <typename Collection>
Collection Sqr(Collection c);
template <typename Collection>
string Join(const Collection& c, char d);
template <typename T1, typename T2>
pair<T1, T2> operator * (const pair<const T1, T2>& lhs, const pair<const T1, T2>& rhs);

template <typename T1, typename T2>
pair<T1, T2> operator * (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    T1 first = lhs.first * rhs.first;
    T2 second = lhs.second * rhs.second;
    return pair<T1, T2>(first, second);
}

template <typename T>
vector<T> operator * (const vector<T>& lhs, const vector<T>& rhs) {
    vector<T> res;
    if (lhs.size() == rhs.size()) {
        for (int i = 0; i < lhs.size; i++) {
            res.push_back(lhs[i] * rhs[i]);
        }
    }
    return res;
}

template <typename Key, typename Value>
map<Key, Value> operator * (const map<Key, Value>& lhs, const map<Key, Value>& rhs) {
    if (lhs.size() == rhs.size()) {
        for (const auto& i : lhs) {
            rhs[i.first] = i.second * rhs[i.first];
        }
    }
    return rhs;
}

template <typename T1, typename T2>
pair<T1, T2> operator * (const pair<const T1, T2>& lhs, const pair<const T1, T2>& rhs) {
    return pair<const T1, T2>(lhs.first, lhs.second * rhs.second);
}

template <typename Collection>
string Join(const Collection& c, char d) {
    stringstream ss;
    bool first = true;
    for (const auto& i : c) {
        if (!first) {
            ss << d;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}

template <typename Collection>
Collection Sqr(Collection c) {
   for (auto& i : c) {
        i  = i * i;
   }
    return c;
}

int main()
{
    map<int, pair<int, int>> map_of_pairs = {
  {4, {2, 2}},
  {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}


