#include <iostream>
#include <vector>

struct Bit {
    int64_t _bit;

    explicit Bit(int64_t bit) : _bit{ bit } {}

    int operator()(long long elem) {
        return (elem >> _bit) & 1;
    }
};

int64_t partition(std::vector<long long>& array, int64_t start, int64_t end, Bit bit) {
    int i = start;
    int j = end;

    while (i != j) {
        while (bit(array[i]) == 0 and i < j)
            i++;
        while (bit(array[j]) == 1 and i < j)
            j--;

        std::swap(array[i], array[j]);
    }

    if (bit(array[end]) == 0) {
        ++j;
    }

    return j - 1;
}

void _msdSort(std::vector<long long>& array, int64_t start, int64_t end, Bit bit) {
    if (end  <= start or bit._bit < 0) {
        return;
    }

    int64_t mid = partition(array, start, end, bit);

    _msdSort(array, start, mid, Bit{ bit._bit - 1 });
    _msdSort(array, mid + 1, end, Bit{ bit._bit - 1 });
}

void msdSort(std::vector<long long>& array) {
    _msdSort(array, 0, array.size() - 1, Bit{ 63 });
}

int main() {
    int64_t n;

    std::cin >> n;

    std::vector<long long> input(n);

    for (int64_t i = 0; i < n; ++i) {
        std::cin >> input[i];
    }

    msdSort(input);

    for (auto c : input) {
        std::cout << c << ' ';
    }
}