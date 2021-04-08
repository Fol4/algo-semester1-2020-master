#include <iostream>
#include <vector>
#include <algorithm>

struct Time {
	int64_t start;
	int64_t end;

	Time(int64_t _start, int64_t _end) : start{ _start }, end{ _end }{}
};

int main() {
    int64_t tmp;
    std::vector<Time> base;

    while (std::cin >> tmp) {
        int64_t tmp2;
        std::cin >> tmp2;

        Time cur{ tmp, tmp2 };

        base.push_back(cur);
    }

    std::sort(base.begin(), base.end(), [](Time lhs, Time rhs) {
        return lhs.end < rhs.end;
        }
    );

    /*for (auto b : base) {
        std::cout << b.start << ' ' << b.end << std::endl;
    }*/

    int64_t amount = 1;
    Time cur = base[0];

    for (int64_t i = 1; i < base.size(); ++i) {
        if (base[i].start >= cur.end) {
            cur = base[i];
            ++amount;
        }
    }

    std::cout << amount << std::endl;
}