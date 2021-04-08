#include <iostream>
#include <algorithm>
#include <vector>

struct Box {
	size_t x;
	size_t y;
	size_t z;
	size_t index;
};

int main() {
	int n;

	std::cin >> n;

	std::vector<Box> boxes;

	for (size_t i = 0; i < n; ++i) {
		size_t x, y, z;
		std::cin >> x >> y >> z;

		boxes.push_back({ std::max(x,std::max(y,z)),std::max(std::min(x,y),std::min(y,z))
			,std::min(x,std::min(y,z)),i });
	}

	std::sort(boxes.begin(), boxes.end(), [](Box first, Box second) {
		if (first.x > second.x) {
			return false;
		} else if (first.y > second.y) {
			return false;
		} else if (first.z >= second.z) {
			return false;
		} else {
			return true;
		}
		}
	);

	for (auto b : boxes) {
		std::cout << b.index << ' ';
	}
}