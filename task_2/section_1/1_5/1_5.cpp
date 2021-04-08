#include <iostream>
#include <vector>
#include <string>

struct Var {
	std::string name;
	std::vector<int> priority;
};

void new_seq(std::vector<Var>& v, const std::vector<int>& ns, int index) {

	std::vector<int> old_seq(ns.size());

	for (int j = 0; j < ns.size(); ++j) {
		std::cin >> old_seq[j];
	}

	for (int j = 0; j < ns.size(); ++j) {
		v[index].priority.push_back(old_seq[ns[ns.size() - j - 1] - 1]);
	}
}

void sort(std::vector<Var>& v) {
	for(int index = 0; index < v[0].priority.size() ;++ index)
		for (int i = 0; i < v.size(); ++i) {
			for (int j = i; j > 0 && v[j - 1].priority[index] < v[j].priority[index]; --j)
				std::swap(v[j], v[j - 1]);
		}
}

int main() {
	int n, k;

	std::cin >> n >> k;

	std::vector<int> seq(k);
	for (int i = 0; i < k; ++i) {
		std::cin >> seq[i];
	}

	std::vector<Var> base(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> base[i].name;
		new_seq(base, seq, i);
	}

	sort(base);

	for (auto b : base) {
		std::cout << b.name << std::endl;
	}
}