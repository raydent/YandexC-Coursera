#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	int N;
	cin >> N;
	vector<int> v;
	vector<vector<int>> res;
	for (int i = 1; i <= N; i++) {
		v.push_back(i);
	}
	reverse(begin(v), end(v));
	/*int perm_num = 1;
	while (N > 0) {
		N--;
		perm_num *= N;
	}*/
	bool flag = true;
	//prev_permutation(begin(v), end(v));
	res.push_back(v);
	while (flag) {
		flag = prev_permutation(begin(v), end(v));
		res.push_back(v);
	}
	res.pop_back();
	for (const auto& i : res) {
		for (const auto& i2 : i) {
			cout << i2 << " ";
		}
		cout << endl;
	}
}