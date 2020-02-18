#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <iterator>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int size = range_end - range_begin;
	if (range_end - range_begin < 2)
		return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	auto it1 = begin(elements) + (range_end - range_begin) / 3;
	auto it2 = it1 + (range_end - range_begin) / 3;
	MergeSort(begin(elements), it1);
	MergeSort(it1, it2);
	MergeSort(it2, end(elements));
	vector<typename RandomIt::value_type> temp;
	//vector<typename RandomIt::value_type> temp;
	merge(begin(elements), it1, it1, it2, back_inserter(temp));
	merge(begin(temp), end(temp), it2, end(elements), range_begin);
}
int main() {
	vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}