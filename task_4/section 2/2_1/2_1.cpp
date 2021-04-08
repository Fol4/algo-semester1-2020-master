#include <iostream>
#include <vector>
#include <algorithm>

struct Athlete {
    int64_t weight;
    int64_t power;

    Athlete(int64_t _weight, int64_t _height) : weight{ _weight }, power{ _height }{}
};

int main() {
    int64_t tmp;
    std::vector<Athlete> base;

    while (std::cin >> tmp) {
        int64_t tmp2;
        std::cin >> tmp2;

        Athlete cur{ tmp, tmp2 };

        base.push_back(cur);
    }

    std::sort(base.begin(), base.end(), [](Athlete lhs, Athlete rhs) {
        if (lhs.weight < rhs.weight) {
            return true;
        }
        else if (lhs.weight == rhs.weight) {
            if (lhs.power < rhs.power) {
                return true;
            }
            else {
                return false;
            }
        }

        return false;
        }
    );

    for (auto b : base) {
        std::cout << b.weight << ' ' << b.power << std::endl;
    }

    int64_t curWeight = base[0].weight;
    int64_t height = 1;

    for (int64_t i = 1; i < base.size(); ++i) {
        if (base[i].power >= curWeight) {
            curWeight += base[i].weight;
            ++height;
        }
    }

    std::cout << height << std::endl;
}