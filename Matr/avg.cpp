#include <cctype>
#include <iostream>
#include <vector>
int main() {
	int N;
	std::cin >> N;
	std::vector<int> v;
	size_t size = N;
	while (N > 0) {
		N--;
		int temp;
		std::cin >> temp;
		v.push_back(temp);
	}
	uint64_t sum = 0;
	for (auto& i : v) {
		sum += static_cast<uint64_t>(i);
	}
	uint64_t avg = sum / size;
	std::cout << avg << endl;
}