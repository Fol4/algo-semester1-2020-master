#include <iostream>
#include <vector>

int med(std::vector<int>& v, int low,
	int mid, int high) {
	if (v[low] > v[mid]) {
		if (v[high] > v[low])
			return low;
		return (v[mid] > v[high]) ? mid : high;
	}

	if (v[high] > v[mid])
		return mid;
	return (v[low] > v[high]) ? low : high;
}

int findOrderStatistic(std::vector<int>& v, int k) {
	int  low = 0;
	int high = v.size() - 1;
	while (true) {
		int pivot = med(v, low, (low + high) / 2, high);
		std::swap(v[pivot], v[high]);
		int i = low;
		for (int j = low; j < high; ++j) {
			if (v[j] <= v[high]) {
				std::swap(v[i], v[j]);
				i++;
			}
		}
		std::swap(v[i], v[high]);
		if (i == k) {
			return v[i];
		}
		else if (i > k) {
			high = i - 1;
		}
		else {
			low = i + 1;
		}
	}
}

int main() {
	int k, n;

	std::cin >> n >> k;

	std::vector<int> numbers(n);

	for (int i = 0; i < n; ++i) {
		std::cin >> numbers[i];
	}

	std::cout << findOrderStatistic(numbers, k) << std::endl;
}