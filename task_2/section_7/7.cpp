#include <iostream>
#include <vector>

int median(std::vector<int_fast32_t>& v, int_fast32_t low,
	int_fast32_t mid, int_fast32_t high) {
	if (v[low] > v[mid]) {
		if (v[high] > v[low])
			return low;
		return (v[mid] > v[high]) ? mid : high;
	}

	if (v[high] > v[mid])
		return mid;
	return (v[low] > v[high]) ? low : high;
}

void quickSort(std::vector<int_fast32_t>& array, int_fast32_t low, int_fast32_t high) {

	int_fast32_t i = low;
	int_fast32_t j = high;
	int_fast32_t pivot = array[median(array, low, (high - low) / 2, high)];

	while (i <= j) {
		while (array[i] < pivot)
			i++;
		while (array[j] > pivot)
			j--;
		if (i <= j) {
			std::swap(array[i], array[j]);
			i++;
			j--;
		}
		else {
			break;
		}
	}

	if (j > low)
		quickSort(array, low, j);
	if (i < high)
		quickSort(array, i, high);
}

int main() {
	std::ios_base::sync_with_stdio(false);

	std::vector<int_fast32_t> input;
	input.reserve(25 * 10 * 10 * 10 * 10 * 10 * 10);

	int_fast32_t size = 0;
	int_fast32_t tmp;

	std::cin.tie(NULL);

	while (std::cin >> tmp) {
		input.push_back(tmp);
		++size;
	}

	std::flush(std::cout);

	quickSort(input, 0, size - 1);

	for (int_fast32_t i = 9; i < size; i += 10) {
		std::cout << input[i] << ' ';
	}

	std::flush(std::cout);
}