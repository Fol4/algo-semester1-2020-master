#include <iostream>
#include <vector>

void sort(std::vector<std::pair<int, int>>& v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = i; j > 0 && v[j - 1].first > v[j].first; --j)
			std::swap(v[j], v[j - 1]);
	}
}

std::vector<std::pair<int, int>> delete_time(std::vector<std::pair<int, int>>& v) {
	std::vector<std::pair<int, int>> newV;
	newV.push_back(v[0]);
	int now = 0;

	for (int i = 1; i < v.size(); ++i) {
		if (v[now].first == v[i].first and v[now].second > v[i].second) {
			newV.pop_back();
			newV.push_back(v[i]);
			now = i;
		}
		else if (v[now].second <= v[i].first) {
			newV.push_back(v[i]);
			now = i;
		}
		else if (v[now].second >= v[i].second) {
			newV.pop_back();
			newV.push_back(v[i]);
			now = i;
		}
	}

	return newV;
}

int count(const std::vector<std::pair<int, int>>& v) {
	int ad = 0;

	if (v.size() == 1) {
		return 2;
	}

	for (int i = 0; i < v.size() - 1; ++i) {
		if (v[i].second == v[i + 1].first) {
			int near = 1;
			for (int j = i + 1; j < v.size() - 1; ++j) {
				if (v[j].second == v[j + 1].first) {
					near++;
				}
				else {
					break;
				}
			}
			ad += near + 2;
			i += near;
		}
		else {
			ad += 2;
		}
	}

	if (v[v.size() - 1].first != v[v.size() - 2].second) {
		ad += 2;
	}

	return ad;
}

int main() {
	int n;

	std::cin >> n;

	std::vector<std::pair<int, int>> time(n, { {}, {} });

	for (int i = 0; i < n; ++i) {
		std::cin >> time[i].first >> time[i].second;
	}

	sort(time);
	std::vector<std::pair<int, int>> newTime = delete_time(time);

	std::cout << count(newTime) << std::endl;
}