#include <string>
#include <algorithm>
#include <set>
#include <vector>
#include <iostream>
using namespace std;





template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix) {
    // [char prefix](const string s){ return s[0] == prefix; }
    RandomIt it1 = lower_bound(range_begin, range_end, prefix, [](const string& s, const char& c) { return s[0] < c; });
    RandomIt it2 = upper_bound(range_begin, range_end, prefix, [](const char& c, const string& s) { return c < s[0]; });
    //RandomIt it1 = binary_search(range_begin, range_end, prefix, cmp);
    return make_pair(it1, it2);
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix) {
    RandomIt it1 = lower_bound(range_begin, range_end, prefix, [](const string& s, const string& prefix) 
        {     string temp(begin(s), begin(s) + prefix.size());
    return temp < prefix;
        });
    RandomIt it2 = upper_bound(range_begin, range_end, prefix, [](const string& prefix, const string& s) 
        {     string temp(begin(s), begin(s) + prefix.size());
    return temp > prefix;
        });
    return make_pair(it1, it2);
}
int main() {
    const vector<string> sorted_strings = { "moscow", "motovilikha", "murmansk" };

    const auto mo_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto mt_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " <<
        (mt_result.second - begin(sorted_strings)) << endl;

    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " <<
        (na_result.second - begin(sorted_strings)) << endl;

    return 0;
}