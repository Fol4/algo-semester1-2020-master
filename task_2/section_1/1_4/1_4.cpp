#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main() {
	int n;
	std::cin >> n;

	std::vector<std::string> input(n);

	for (int i = 0; i < n; ++i) {
		std::cin >> input[i];
	}
	
	std::sort(input.begin(), input.end());

	for (auto s : input) {
		std::cout << s << std::endl;
	}
}

