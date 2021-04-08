#include <iostream>
#include <vector>
#include <cmath>

struct Coord {
	double x;
	double y;
	double angle;
};

void set_angle(std::vector<Coord>& dots, Coord start) {
	for (int i = 1; i < dots.size(); ++i) {
		if (dots[i].x == dots[0].x) {
			dots[i].angle = 2;
		}
		else {
			dots[i].angle = atan2((dots[i].y - dots[0].y), (dots[i].x - dots[0].x));
		}
	}
}

void sort_angle(std::vector<Coord>& dots) {

	for (int i = 1; i < dots.size(); ++i){
		for (int j = i; j > 1 && dots[j - 1].angle < dots[j].angle; --j)
			std::swap(dots[j], dots[j - 1]);
	}
}

int main() {
	int n;
	double first_x, first_y;

	std::cin >> n;
	std::cin >> first_x >> first_y;

	Coord start;
	start.x = first_x;
	start.y = first_y;
	int startInd = 0;

	std::vector<Coord> dots(n);
	dots[0] = start;

	for (int i = 1; i < n; ++i) {
		std::cin >> dots[i].x >> dots[i].y;

		if (dots[i].x < start.x) {
			start.x = dots[i].x;
			start.y = dots[i].y;
			startInd = i;
		}
		else if (dots[i].x == start.x) {
			if (dots[i].y < start.y) {
				start.x = dots[i].x;
				start.y = dots[i].y;
				startInd = i;
			}
		}
	}

	std::swap(dots[0], dots[startInd]);

	set_angle(dots, start);
	sort_angle(dots);

	for (auto c : dots) {
		std::cout << c.x << ' ' << c.y << std::endl;
	}
}