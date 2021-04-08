#include <iostream>
#include <vector>
#include <algorithm>

struct Date {
	int day;
	int month;
	int year;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.year < rhs.year) {
		return true;
	}
	else if (lhs.year > rhs.year) {
		return false;
	}
	else {
		if (lhs.month < rhs.month) {
			return true;
		}
		else if (lhs.month > rhs.month) {
			return false;
		}
		else {
			if (lhs.day < rhs.day) {
				return true;
			}
			else if (lhs.day > rhs.day) {
				return false;
			}
			else {
				return false;
			}
		}
	}
}

bool operator==(const Date& lhs, const Date& rhs) {
	return lhs.day == rhs.day and lhs.month == rhs.month and lhs.year == rhs.year;
}

int main() {
	int n;

	std::cin >> n;

	std::vector<std::pair<Date, char>> coworkers;

	for (int i = 0; i < n; ++i) {
		Date born;
		Date dead;

		std::cin >> born.day >> born.month >> born.year >> dead.day >> dead.month >> dead.year;

		int y18 = born.year + 18;
		int y80 = born.year + 80;

		Date enter{ born.day, born.month, y18 };
		Date quit{ born.day, born.month, y80 };

		if (enter < dead) {
			coworkers.push_back({ enter, '+' });
			if (quit < dead) {
				coworkers.push_back({ quit, '-' });
			}
			else {
				coworkers.push_back({ dead, '-' });
			}
		}
	}

	
	sort(coworkers.begin(), coworkers.end(), [](std::pair<Date, char>& lhs, std::pair<Date, char>& rhs)
		{
			if (lhs.first == rhs.first) {
				if (rhs.second == '-') {
					return false;
				}
				else return true;
			}
			return lhs.first < rhs.first;
		});

	int count = 0;
	int maxCount = 0;

	for (int i = 0; i < n + 1; ++i) {
		if (coworkers[i].second == '+' ) {
			count++;
			if (count > maxCount) {
				maxCount = count;
			}
		}
		else {
			count--;
		}
	}	

	std::cout << maxCount << std::endl;
}