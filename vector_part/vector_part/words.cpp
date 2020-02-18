#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
vector<string> SplitIntoWords(const string& s) {
	auto it1 = begin(s), it2 = begin(s);
	vector<string> v;
	while (it2 != end(s)) {
		it2 = find_if(it2, end(s), [](char c) {return c == ' '; });
        //if (it2 == end(s)) {
          //  it2--;
        //}
		string temp(it1, it2);
		v.push_back(temp);
        if (it2 != end(s))
            it2++;
        it1 = it2;
	}
	return v;
}
int main() {
	vector<int> vec;
	auto vector_begin = begin(vec);
	auto vector_end = end(vec);

	string str;
	auto string_begin = begin(str);
	auto string_end = end(str);

	set<int> s;
	auto set_begin = begin(s);
	auto set_end = end(s);
	auto res = accumulate(vector_begin, vector_end, 0);

    return 0;
}