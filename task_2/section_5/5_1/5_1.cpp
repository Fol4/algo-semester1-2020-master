#include <iostream>
#include <vector>
#include <string>

void count_sort(std::vector<std::string>& array, int64_t byte, int64_t start, int64_t end, std::vector<int64_t>& count) {
    std::vector<int64_t> c(257, 0);

    for (int i = start; i < end; ++i) {
        if (array[i].length() <= byte) {
            ++c[0];
        }
        else {
            ++c[static_cast<int>(array[i][byte]) + 1];
        }
    }

    int64_t sum = 0;

    for (int i = 0; i < 257; ++i) {
        int64_t tmp = c[i];
        c[i] = sum;
        sum += tmp;
    }

    std::vector<std::string> b(end - start);

    for (int64_t i = start; i < end; ++i) {
        if (array[i].length() <= byte) {
            b[c[0]++] = array[i];
        }
        else {
            b[c[static_cast<int>(array[i][byte]) + 1]++] = array[i];
        }
    }

    for (int64_t i = 0; i < 257; ++i) {
        count[i] = c[i] + start;
    }

    for (int64_t i = start; i < end; ++i) {
        array[i] = b[i - start];
    }
}

void _msd_sort(std::vector<std::string>& array, int64_t byte, int64_t start, int64_t end) {

    std::vector<int64_t> count(257, 0);

    count_sort(array, byte, start, end, count);

    for (int64_t i = 1; i < count.size() - 1; ++i) {

        if (count[i + 1] - count[i] > 1) {
            _msd_sort(array, byte + 1, count[i], count[i + 1]);
        }
    }
}

void msd_sort(std::vector<std::string>& array){
        _msd_sort(array, 0, 0, array.size());
}

int main() {
    std::vector<std::string> input;
    std::string tmp;

    while (std::cin >> tmp) {
        input.push_back(tmp);
    }

    msd_sort(input);

    for (auto i : input) {
        std::cout << i << std::endl;
    }
}