#include "sum_reverse_sort.h"
#include <algorithm>
int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
	string res;
	for (int t = s.size() - 1; t >= 0; t--) {
		res.push_back(s[t]);
	}
	return res;
}

void Sort(vector<int>& nums) {
	sort(nums.begin(), nums.end());
}