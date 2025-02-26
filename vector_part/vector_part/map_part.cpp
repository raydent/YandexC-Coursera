#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {	
	auto it = find_if(begin(elements), end(elements), [border](T t) {return t > border; });
	vector<T> v;
	while (it != end(elements)) {
		v.push_back(*it);
		it++;
	}
	return v;
}

int main() {
	for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
		cout << x << " ";
	}
	cout << endl;

	string to_find = "Python";
	cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
	return 0;
}