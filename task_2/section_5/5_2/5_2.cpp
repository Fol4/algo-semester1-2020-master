#include <iostream>
#include <vector>

struct Byte {
    int64_t _byte;

    explicit Byte(int64_t byte) : _byte{ byte } {}

    int operator()(long long elem) {
        return (elem >> 8 * _byte)&255;
    }
};

void count_sort(std::vector<long long>& array, Byte byte) {
    std::vector<int64_t> c(256, 0);

    for (int i = 0; i < array.size(); ++i) {
        ++c[byte(array[i])];
    }

    int64_t sum = 0;

    for (int i = 0; i < 256; ++i) {
        int64_t tmp = c[i];
        c[i] = sum;
        sum += tmp;
    }

    std::vector<int64_t> b(array.size());

    for (int64_t i = 0; i < array.size(); ++i) {
        b[c[byte(array[i])]++] = array[i];
    }

    for (int64_t i = 0; i < array.size(); ++i) {
        array[i] = b[i];
    }
}

void radix_sort(std::vector<long long>& array)
{
    for (int64_t i = 0; i < sizeof(long long); ++i) {
        count_sort(array, Byte{ i });
    }
}

int main() {
    int64_t n;

    std::cin >> n;

    std::vector<long long> input(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> input[i];
    }

    radix_sort(input);

    for (auto i : input) {
        std::cout << i << ' ';
    }
}