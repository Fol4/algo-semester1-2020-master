#include <iostream>
#include <vector>

int64_t merge(std::vector<uint64_t>& array, int64_t left, int64_t mid, int64_t right) {
    int64_t it1 = 0;
    int64_t it2 = 0;
    int64_t inv = 0;
    std::vector<uint64_t> result;

    while (left + it1 < mid and mid + it2 < right) {
        if (array[left + it1] <= array[mid + it2]) {
            result.push_back(array[left + it1]);
            it1 += 1;
        }
        else {
            result.push_back(array[mid + it2]);
            inv += mid - (it1 + left);
            it2 += 1;
        }
    }

    while (left + it1 < mid) {
        result.push_back(array[left + it1]);
        it1 += 1;
    }

    while (mid + it2 < right) {
        result.push_back(array[mid + it2]);
        it2 += 1;
    }

    for (int64_t i = 0; i < it1 + it2; ++i) {
        array[left + i] = result[i];
    }

    return inv;
}

int64_t mergeSortRecursive(std::vector<uint64_t>& array, int64_t left, int64_t right) {
    int64_t inv = 0;
    if (left + 1 >= right) {
        return 0;
    }
    int64_t mid = (left + right) / 2;
    inv += mergeSortRecursive(array, left, mid);
    inv += mergeSortRecursive(array, mid, right);
    inv += merge(array, left, mid, right);

    return inv;
}

int main() {
    int64_t size = 1000000;
    std::vector<uint64_t> array(size);
    int64_t i = 0;

    while (!(std::cin >> array[i]).eof()) {
        ++i;
        if (i > size) {
            size *= 2;
            array.resize(size);
        }
    }

    std::cout << mergeSortRecursive(array, 0, i) << std::endl;
}