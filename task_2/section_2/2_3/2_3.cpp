#include <iostream>
#include <vector>

void quickSort(std::vector<std::pair<int, int>>& array, int low, int high){
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2].first;
    int temp;

    while (i <= j){
        while (array[i].first < pivot)
            i++;
        while (array[j].first > pivot)
            j--;
        if (i <= j){
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }

    if (j > low)
        quickSort(array, low, j);
    if (i < high)
        quickSort(array, i, high);
}

std::vector<std::pair<int, int>> merge(std::vector<std::pair<int, int>>& array) {
    int i = 0;
    std::vector<std::pair<int, int>> newArray;
    while (i < array.size()) {
        int count = 0;
        int maxEnd = i;
        for (int j = i; j < array.size() - 1 and (array[maxEnd].second >= array[j + 1].first); ++j) {
            count++;
            if (array[j+1].second > array[maxEnd].second) {
                maxEnd = j+1;
            }
        }
        newArray.push_back({ array[i].first, array[maxEnd].second });
        i += count + 1;
    }

    return newArray;
}

int count(std::vector<std::pair<int, int>>& array) {
    int c = 0;
    for (int i = 0; i < array.size(); ++i) {
        c += array[i].second - array[i].first;
    }

    return c;
}

int main() {
	int n;

	std::cin >> n;

	std::vector<std::pair<int, int>> section(n);

	for (int i = 0; i < n; ++i) {
		std::cin >> section[i].first >> section[i].second;
	}

    quickSort(section, 0, n - 1);
    section = merge(section);
    
    std::cout << count(section) << std::endl;
}