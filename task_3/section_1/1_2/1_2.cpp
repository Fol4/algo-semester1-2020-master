#include <iostream>
#include <stack>
#include <queue>

struct Node {
	int64_t val;
	Node* right;
	Node* left;

	Node(int64_t v) : val{ v }, right{ nullptr }, left{ nullptr }{}

	~Node() {
		delete right;
		delete left;
	}
};

class Tree {
private:
	Node* root;

public:
	Tree() : root{ nullptr } {}
	~Tree() {
		delete root;
	}

	void add(int64_t v) {
		Node* newNode = new Node{ v };

		if (!root) {
			root = newNode;
			return;
		}

		Node* cur = root;

		while (cur) {
			if (cur->val <= v) {
				if (!cur->right) {
					cur->right = newNode;
					return;
				}
				else {
					cur = cur->right;
				}
			}
			else {
				if (!cur->left) {
					cur->left = newNode;
					return;
				}
				else {
					cur = cur->left;
				}
			}
		}
	}

	void preorder() {
		std::stack<Node*> Stack;
		Node* now = root;

		while (now or !Stack.empty()) {
			if (!Stack.empty()) {
				now = Stack.top();
				Stack.pop();
			}

			while (now) {
				std::cout << now->val << ' ';
				if (now->right) {
					Stack.push(now->right);
				}
				now = now->left;
			}
		}
	}

	void inorder() {
		std::stack<Node*> Stack;
		Node* now = root;

		while (now or !Stack.empty()) {
			if (!Stack.empty()) {
				now = Stack.top();
				Stack.pop();
				std::cout << now->val << ' ';
				if (now->right) {
					now = now->right;
				}
				else {
					now = nullptr;
				}
			}

			while (now) {
				Stack.push(now);
				now = now->left;
			}
		}
	}

	void postorder() {
		std::stack<Node*> Stack;
		Node* now = root;

		while (now or !Stack.empty()) {
			if (!Stack.empty()) {
				now = Stack.top();
				Stack.pop();
				if (!Stack.empty() and now->right == Stack.top()) {
					now = Stack.top();
					Stack.pop();
				}
				else {
					std::cout << now->val << ' ';
					now = nullptr;
				}
			}

			while (now) {
				Stack.push(now);
				if (now->right) {
					Stack.push(now->right);
					Stack.push(now);
				}
				now = now->left;
			}
		}
	}

	void levelorder() {
		std::queue<Node*> Queue;
		Node* now = root;
		Queue.push(root);

		while (!Queue.empty()) {

			Node* now = Queue.front();
			Queue.pop();

			std::cout << now->val << ' ';

			if (now->left) {
				Queue.push(now->left);
			}

			if (now->right) {
				Queue.push(now->right);
			}
		}
	}
};

int main() {
	uint64_t n;
	std::cin >> n;

	Tree tree;
	for (uint64_t i = 0; i < n; ++i) {
		int64_t now;
		std::cin >> now;

		tree.add(now);
	}

	tree.preorder();
}