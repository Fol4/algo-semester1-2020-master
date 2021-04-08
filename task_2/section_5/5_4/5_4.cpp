#include <iostream>
#include <vector>

struct Byte {
    int64_t _byte;

    explicit Byte(int64_t byte) : _byte{ byte } {}

    int operator()(long long elem) {
        return (elem >> 8 * _byte) & 255;
    }
};

void count_sort(std::vector<unsigned>& array, Byte byte) {
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

    std::vector<unsigned> b(array.size());

    for (int64_t i = 0; i < array.size(); ++i) {
        b[c[byte(array[i])]++] = array[i];
    }

    for (int64_t i = 0; i < array.size(); ++i) {
        array[i] = b[i];
    }
}

void radix_sort(std::vector<unsigned>& array)
{
    for (int64_t i = 0; i < sizeof(unsigned); ++i) {
        count_sort(array, Byte{ i });
    }
}

int main() {
	unsigned n, k, m, l;

	std::cin >> n >> k >> m >> l;

	std::vector<unsigned> input(n);
	
	input[0] = k; 
	for (int i = 0; i < n - 1; i++) {
		input[i + 1] = (unsigned int)((input[i] * (unsigned long long)m) & 0xFFFFFFFFU)% l;
	}

    radix_sort(input);

    int64_t sum = 0;

    for (int i = 0; i < n; i += 2) {
        sum += input[i];
    }

    std::cout << sum % l << std::endl;
}