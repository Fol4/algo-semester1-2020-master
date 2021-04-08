#include <iostream>
#include <vector>
#include <algorithm>

class Tree {
private:
	struct Node {
		int64_t val;
		int64_t edge;
		int64_t distance;
		std::vector<Node*> children;
		Node* parent;

		Node(int64_t v) : val{ v }, edge{ 0 }, distance{ 0 }, parent{ nullptr }{}
	};

	std::vector<Node> tree;
	
public:
	Tree(int64_t size) {
		for (int64_t i = 0; i < size; ++i) {
			tree.push_back(Node{ i });
		}
	}

	void insert(int64_t parent, int64_t children) {
		tree[parent].children.push_back(&tree[children]);
		tree[children].parent = &tree[parent];
	}

	void dfs(int64_t root) {
		for (auto i : tree[root].children) {
			dfs(i->val);
			tree[root].distance += i->distance + i->edge;
			tree[root].edge += i->edge;
		}

		tree[root].edge++;
	}

	void output() {
		dfs(0);

		for (int64_t i = 0; i < tree.size(); ++i) {
			if (i == 0) {
				std::cout << tree[i].distance << std::endl;
			}
			else {
				tree[i].distance = tree[i].parent->distance + tree.size() - 2 * tree[i].edge;
				std::cout << tree[i].distance << std::endl;
			}
		}
	}
};

int main() {
	int64_t n;
	std::cin >> n;

	Tree tree{ n };

	for (int64_t i = 0; i < n - 1; ++i) {
		int64_t left, right;
		std::cin >> left >> right;
		tree.insert(std::min(left, right), std::max(left, right));
	}

	tree.output();
}