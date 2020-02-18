#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

template <typename T>
T operator* (T lhs, T rhs);

template <typename T>
T Sqr(const T t);

template <typename T1, typename T2>
pair<T1, T2> Sqr(const pair<T1, T2>& p);

template <typename T1, typename T2>
pair<const T1, T2> Sqr(const pair<const T1, T2>& p);

template <typename T>
vector<T> Sqr(const vector<T>& v);

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m);


template <typename T>
T operator* (T lhs, T rhs) {
    return lhs * rhs;
}
template <typename T>
T Sqr(const T t) {
    return t * t;
}
template <typename T1, typename T2>
pair<T1, T2> Sqr(const pair<T1, T2>& p) {
    return pair<T1, T2>(Sqr(p.first), Sqr(p.second));
}
template <typename T1, typename T2>
pair<const T1, T2> Sqr(const pair<const T1, T2>& p) {
    return pair<const T1, T2>(p.first, Sqr(p.second));
}
template <typename T>
vector<T> Sqr(const vector<T>& v) {
    vector<T> res;
    for (const auto& i : v) {
        res.push_back(Sqr(i));
    }
    return res;
}
template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
    map<Key, Value> res;
    for (const auto& i : m) {
        res[i.first] = Sqr(i.second);
    }
    return res;
}

int main()
{
    map<int, int> m{ {1, 2}, {2, 4}, {3, 5} };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(m)) {
        cout << ' ' << x.first << ' ' << x.second << endl;
    }
}   
