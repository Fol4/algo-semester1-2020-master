#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
	long x;
	long y;
};

int main() {
	size_t n;

	std::cin >> n;

	std::vector<Point> points(n);

	for (size_t i = 0; i < n; ++i) {
		std::cin >> points[i].x >> points[i].y;
	}

	std::sort(points.begin(), points.end(), [](Point first, Point second) {
		if (first.x > second.x) {
			return false;
		}
		else if (first.x == second.x) {
			if (first.y >= second.y) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
		}
	);

	for (auto p : points) {
		std::cout << p.x << ' ' << p.y << std::endl;
	}
}