#include <iostream>
#include <vector>

struct Bkt {
	char type;
	int number;
	int value; 
};

void quickSort(std::vector<Bkt>& array, int low, int high) {
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2].value;

    while (i <= j) {
        while (array[i].value < pivot)
            i++;
        while (array[j].value > pivot)
            j--;
        if (i <= j) {
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

void sort(std::vector<Bkt>& array) {
    for (int i = 0; i < array.size() - 1; ++i) {
        if (array[i].value == array[i + 1].value) {
            if (array[i].type == ']') {
                std::swap(array[i], array[i + 1]);
            }
        }
    }
}

void quickSort(std::vector<std::pair<int, int>>& array, int low, int high) {
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2].first;
    int temp;

    while (i <= j) {
        while (array[i].first < pivot)
            i++;
        while (array[j].first > pivot)
            j--;
        if (i <= j) {
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

int two(std::vector<Bkt>& array) {
    int start = array[0].number;
    int all = 0;
    int first = -1;
    int count = 0;
    bool in = true;
    for (int i = 1; i < array.size() - 1; ++i) {
        if (start == array[i].number) {
            if (all == 0) {
                if (i != array.size() - 1) {
                    start = array[i + 1].number;
                    first = -1;
                }
                in = true;
                ++i;
            }
            else if (all == 1) {
                count += array[i].value - first;
                first = -1;
                in = true;
                all = 0;
            }
            else {
                in = false;
            }
        }
        else if (array[i].type == ']' and array[i+1].type == '[' and all == 0) {
                start = array[i + 1].number;
                first = -1;
                in = true;
                i+=1;
        }
        else if (array[i].type == '[') {
            all++;
            if (first == -1) {
                first = array[i].value;
            }
        }
        else if (array[i].type == ']') {
            if (all == 0) {
                continue;
            }
            all--;
            if (all == 0 and first != -1) {
                count += array[i].value - first;
                first = -1;
            }
            else if (all == 1 and !in) {
                count += array[i].value - first;
                first = -1;
                all = 0;
                in = true;
            }
        }
    }

    return count;
}

int only(std::vector<std::pair<int, int>>& array) {
    int i = 0;
    std::vector<std::pair<int, int>> newArray;
    while (i < array.size()) {
        int count = 0;
        int maxEnd = i;
        for (int j = i; j < array.size() - 1 and (array[maxEnd].second >= array[j + 1].first); ++j) {
            count++;
            if (array[j + 1].second > array[maxEnd].second) {
                maxEnd = j + 1;
            }
        }
        newArray.push_back({ array[i].first, array[maxEnd].second });
        i += count + 1;
    }

    int c = 0;
    for (int i = 0; i < newArray.size(); ++i) {
        c += newArray[i].second - newArray[i].first;
    }

    return c;
}

int main() {
	int n;
	int count = 0;

	std::cin >> n;

	std::vector<Bkt> borders(2*n);
    std::vector<std::pair<int, int>> forCount(n);

	for (int i = 0; i < 2*n; ++i) {
		std::cin >> borders[i].value;
		borders[i].type = '[';
		borders[i].number = count;

        forCount[i/2].first = borders[i].value;

		++i;

		std::cin >> borders[i].value;
		borders[i].type = ']';
		borders[i].number = count;

		++count;

        forCount[i/2].second = borders[i].value;
	}

    quickSort(borders, 0, borders.size() - 1);
    sort(borders);
    quickSort(forCount, 0, forCount.size() - 1);
    
    std::cout << only(forCount) - two(borders) << std::endl;
}