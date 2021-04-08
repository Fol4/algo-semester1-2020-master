#include <iostream>
#include <vector>

int main() {
	uint64_t n;

	std::cin >> n;

	std::vector<std::vector<int64_t>> base(n + 1, std::vector<int64_t>(n + 1, 0));

	for (int64_t j = 0; j < n + 1; ++j) {
		base[1][j] = 1;
	}

	for (int64_t i = 2; i < n + 1; ++i) {
		for (int64_t j = 0; j < n + 1; ++j) {
			if (j - i < 0) {
				base[i][j] = base[i - 1][j];
			}
			else {
				base[i][j] = base[i - 1][j] + base[i][j - i];
			}
		}
	}

	std::cout << base[n][n] << std::endl;
}