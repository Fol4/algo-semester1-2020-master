#include <iostream>
#include <queue>

class AVLtree {
private:
	struct Node{
		int64_t val;
		uint16_t height;
		int64_t number;
		Node* left;
		Node* right;

		Node(int64_t _val, int64_t _number) : val{ _val }, height{ 1 }, number{ _number }, left{ nullptr }, right{ nullptr } {}
	};

	Node* root;

	int balanced(Node* cur) {
		return height(cur->right) - height(cur->left);
	}

	void fix_height(Node* cur) {
		uint16_t heightLeft = height(cur->left);
		uint16_t heightRight = height(cur->right);
		cur->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
	}

	Node* right_rotate(Node* cur) {
		Node* now = cur->left;

		cur->left = now->right;
		now->right = cur;

		fix_height(cur);
		fix_height(now);

		return now;
	}

	Node* left_rotate(Node* cur) {
		Node* now = cur->right;

		cur->right = now->left;
		now->left = cur;

		fix_height(cur);
		fix_height(now);

		return now;
	}

	Node* balance(Node* cur) {
		fix_height(cur);

		if (balanced(cur) == 2)
		{
			if (balanced(cur->right) < 0) {
				cur->right = right_rotate(cur->right);
			}

			return left_rotate(cur);
		}

		if (balanced(cur) == -2)
		{
			if (balanced(cur->left) > 0) {
				cur->left = left_rotate(cur->left);
			}

			return right_rotate(cur);
		}
		return cur;
	}

	Node* find_min(Node* cur) {
		return cur->left ? find_min(cur->left) : cur;
	}

	Node* remove_min(Node* cur) {
		if (cur->left == 0) {
			return cur->right;
		}

		cur->left = remove_min(cur->left);

		return balance(cur);
	}

	Node* _del(Node* cur, int64_t val) {
		if (!cur) {
			return 0;
		}

		if (val < cur->val) {
			cur->left = _del(cur->left, val);
		}
		else if (val > cur->val) {
			cur->right = _del(cur->right, val);
		}
		else {
			Node* left = cur->left;
			Node* right = cur->right;

			delete cur;

			if (!right) {
				return left;
			}

			Node* min = find_min(right);
			min->right = remove_min(right);
			min->left = left;
			
			return balance(min);
		}

		return balance(cur);
	}

	Node* _insert(Node* cur, int64_t val, int64_t number) {
		if (!cur) {
			return new Node{val, number};
		}

		if (val < cur->val) {
			number++;
			cur->left = _insert(cur->left, val, number);
		}
		else {
			++cur->number;
			cur->right = _insert(cur->right, val, number);
		}

		return balance(cur);
	}

public:
	AVLtree() : root{ nullptr } {}
	~AVLtree() {
		delete root;
	}

	uint16_t height(Node* cur){
		return cur ? cur->height : 0;
	}

	void del(int64_t val) {
		root = _del(root, val);
	}

	void insert(int64_t val) {
		if (!root) {
			root = new Node{ val, 0 };
		}

		root = _insert(root, val, root->number);
	}
};

int main() {
	int64_t n;
	std::cin >> n;

	AVLtree tree;

	for (int64_t i = 0; i < n; ++i) {
		int64_t val;
		std::cin >> val;
		tree.insert(val);
	}
}