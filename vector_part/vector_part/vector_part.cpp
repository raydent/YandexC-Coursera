#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
void PrintVectorPart(const vector<int>& numbers) {
	auto it = find_if(begin(numbers), end(numbers), [](const int& elem) {return elem < 0; });
	while(it != begin(numbers)) {
		it--;
		cout << *it << " ";
	}
	cout << endl;
}
int main() {
	PrintVectorPart({ 6, 1, 8, -5, 4 });
	cout << endl;
	PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
	cout << endl;
	PrintVectorPart({ 6, 1, 8, 5, 4 });
	cout << endl;
	return 0;
}