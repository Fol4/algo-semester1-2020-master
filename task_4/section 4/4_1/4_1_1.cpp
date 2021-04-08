#include <iostream>
#include <vector>
#include <algorithm>

class Tree {
	struct Node {
		int64_t val;
		int64_t height;
		int64_t trace;

		std::vector<Node*> children;

		Node(int64_t _val) : val{ _val } {}
	};

	std::vector<Node> tree;

	int64_t newHeight(Node* root) {
		if (!root) {
			return 0;
		}

		int64_t height = 0;
		for (auto i : root->children) {
			int64_t nheight = newHeight(i);
			if (nheight > height) {
				height = nheight;
			}
		}

		root->height = height + 1;
		return height + 1;
	}

	int64_t maxHeight(Node* root, int64_t now) {
		int64_t maxH = 0;
		for (auto i : root->children) {
			if (i->val != now and i->height > maxH) {
				maxH = i->height;
			}
		}

		return maxH;
	}

	void fixHeight(Node* root, int64_t maxH) {
		if (!root) {
			return;
		}

		for (auto i : root->children) {
			fixHeight(i, std::max(maxHeight(root, i->val), maxH) + 1);
		}

		root->trace = std::max(maxHeight(root, -1), maxH);
	}

public:

	Tree(int64_t size) {
		for (int64_t i = 0; i < size; ++i) {
			tree.push_back(Node{ i });
		}
	}

	int64_t trace(int64_t i) {
		return tree[i].trace;
	}

	void insert(int64_t parent, int64_t children) {
		tree[parent].children.push_back(&tree[children]);
	}

	void calculate() {
		newHeight(&tree[0]);
		fixHeight(&tree[0], 0);
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

	tree.calculate();

	for (int64_t i = 0; i < n; ++i) {
		std::cout << tree.trace(i) << std::endl;
	}
}