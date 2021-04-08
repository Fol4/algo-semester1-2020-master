#include <iostream>
#include <stack>
#include <vector>
#include <time.h>

class AVLtree {
private:
	struct Node {
		int64_t val;
		short diff;
		int64_t number;
		Node* left;
		Node* right;

		Node(int64_t _val) : val{ _val }, diff{ 0 }, left{ nullptr }, right{ nullptr }, number{ 1 }{}
		~Node() {
			delete right;
			delete left;
		}
	};

	Node* root;

	int64_t is_number(Node* cur) {
		if (!cur) {
			return 0;
		}
		else {
			return cur->number;
		}
	}

	void update(Node* cur) {

		if (cur)
			cur->number = 1 + is_number(cur->right) + is_number(cur->left);
	}

	void small_left_rotate(Node* cur, bool is_big) {
		Node* now = cur->right;
		std::swap(cur->val, now->val);
		Node* node_left = cur->left;
		cur->left = now;
		cur->right = now->right;
		now->right = now->left;
		now->left = node_left;

		update(cur->left);
		update(cur);

		if (is_big) {
			cur->diff = -(now->diff + 1);
			now->diff = std::abs(cur->diff);
		}

		std::swap(now->diff, cur->diff);
	}

	void small_right_rotate(Node* cur, bool is_big) {
		Node* now = cur->left;
		std::swap(cur->val, now->val);
		Node* right_node = cur->right;
		cur->right = now;
		cur->left = now->left;
		now->left = now->right;
		now->right = right_node;

		update(cur->right);
		update(cur);

		if (is_big) {
			cur->diff = std::abs(now->diff - 1);
			now->diff = now->diff - 1;
		}

		std::swap(cur->diff, now->diff);
	}

	void big_left_rotate(Node* cur) {
		small_right_rotate(cur->right, false);
		small_left_rotate(cur, false);

		switch (cur->diff) {
		case 0:
			cur->right->diff = 0;
			cur->left->diff = 0;
			cur->diff = 0;
			break;
		case 1:
			cur->right->diff = -1;
			cur->left->diff = 0;
			cur->diff = 0;
			break;
		case -1:
			cur->right->diff = 0;
			cur->diff = 0;
			cur->left->diff = 1;
		}

	}

	void big_right_rotate(Node* cur) {
		small_left_rotate(cur->left, false);
		small_right_rotate(cur, false);
		
		switch (cur->diff) {
		case 0:
			cur->right->diff = 0;
			cur->left->diff = 0;
			cur->diff = 0;
			break;
		case 1:
			cur->left->diff = 0;
			cur->right->diff = -1;
			cur->diff = 0;
			break;
		case -1:
			cur->left->diff = 1;
			cur->diff = 0;
			cur->right->diff = 0;
		}
	}

	void balance_insert(std::stack<Node*> trail) {
		Node* child = trail.top();
		trail.pop();

		while (!trail.empty()) {
			Node* parent = trail.top();
			trail.pop();

			if (parent->left == child) {
				++parent->diff;
			}
			else {
				--parent->diff;
			}

			if (parent->diff == 0) {
				break;
			}

			if (parent->diff == 2) {
				if (parent->left->diff == 0 or parent->left->diff == 1) {
					small_right_rotate(parent, true);
				}
				else {
					big_right_rotate(parent);
				}
			}

			if (parent->diff == -2) {
				if (parent->right->diff == 0 or parent->right->diff == -1) {
					small_left_rotate(parent, true);
				}
				else {
					big_left_rotate(parent);
				}
			}

			if (parent->diff == 0) {
				break;
			}

			child = parent;
		}
	}

	void balance_del(std::stack<Node*> trail, int64_t child) {

		while (!trail.empty()) {
			Node* parent = trail.top();
			trail.pop();

			if (parent->val > child) {
				--parent->diff;
			}
			else {
				++parent->diff;
			}

			if (std::abs(parent->diff) == 1) {
				break;
			}

			if (parent->diff == -2) {	
				if (parent->right->diff == 1) {
					big_left_rotate(parent);
				}
				else {
					small_left_rotate(parent, true);
				}
			}
			if (parent->diff == 2) {
				if (parent->left->diff == -1) {
					big_right_rotate(parent);
				}
				else {
					small_right_rotate(parent, true);
				}
			}

			if (std::abs(parent->diff) == 1) {
				break;
			}

			child = parent->val;
		}
	}

	void del_node(std::stack<Node*>& trail, Node* node, int64_t& last) {

		--node->number;

		if (!node->left and !node->right) {
			if (trail.empty()) {
				root = nullptr;
				return;
			}

			if (trail.top()->right == node) {
				trail.top()->right = nullptr;
			}
			else {
				trail.top()->left = nullptr;
			}

			delete node;
		}
		else if (node->left and node->right) {
			auto cur = node->right;

			trail.push(node);

			while (cur->left) {
				--cur->number;

				trail.push(cur);
				cur = cur->left;
			}

			node->val = cur->val;
			last = cur->val;

			del_node(trail, cur, last);
		}
		else {
			Node* cur;

			if (node->left) {
				cur = node->left;
			}
			else {
				cur = node->right;
			}

			node->val = cur->val;
			node->diff = cur->diff;
			node->left = cur->left;
			cur->left = nullptr;
			node->right = cur->right;
			cur->right = nullptr;

			delete cur;
		}
	}

public:
	AVLtree() : root{ nullptr } {}
	~AVLtree() {
		delete root;
	}
	
	int64_t insert(int64_t val) {
		int64_t num = 0;

		if (!root) {
			root = new Node{ val };
			return num;
		}

		Node* cur = root;
		std::stack<Node*> trail;

		while (cur) {
			trail.push(cur);
			++cur->number;

			if (val < cur->val) {
				if (!cur->left) {
					num += cur->number - 1;
					cur->left = new Node{ val };
					trail.push(cur->left);

					break;
				}
				else {
					num += cur->number - cur->left->number - 1;
				}

				cur = cur->left;
			}
			else {
				if (!cur->right) {
					cur->right = new Node{ val };
					trail.push(cur->right);

					break;
				}

				cur = cur->right;
			}
		}

		balance_insert(trail);

		return num;
	}

	void del(int64_t height) {
		Node* cur = root;

		if (!root) {
			return;
		}

		if (height >= root->number) {
			return;
		}

		std::stack<Node*> trail;

		while (true) {
			trail.push(cur);
			if (cur->number - is_number(cur->left) - 1 == height) {
				break;
			}
			else if (height < is_number(cur->right)) {
				--cur->number;
				cur = cur->right;
			}
			else {
				height -= cur->number - is_number(cur->left);
				--cur->number;
				cur = cur->left;
			}
		}

		int64_t last = trail.top()->val;
		trail.pop();
                       
		del_node(trail, cur, last);
		balance_del(trail, last);
	}
};

int main() {
	int64_t n;
	std::cin >> n;

	AVLtree tree;
	std::vector<int64_t> result;

	for (int64_t i = 0; i < n; ++i) {
		short command;
		int64_t height;

		std::cin >> command >> height;

		if (command == 1) {
			result.push_back(tree.insert(height));
		}
		else if (command == 2) {
			tree.del(height);
		}
	}

	for (auto i : result) {
		std::cout << i << ' ';
	}
}

//int main() {
//
//	srand(time(NULL));
//
//	/*std::cin >> n;*/
//	for (int j = 0; j < 1000; ++j) {
//		int64_t deleted = 0;
//		int64_t n = 1 + rand()%100;
//		std::cout << "TEST" << " " << j << std::endl;
//		std::cout << n << std::endl;
//		AVLtree tree;
//		std::vector<int64_t> result;
//		std::vector<int64_t> randomTable(100000, 0);
//
//		for (int64_t i = 0; i < n; ++i) {
//
//			short command = 1 + rand() % 2;
//			int64_t height = 1 + rand() % 1000;
//			while (randomTable[height - 1] == 1) {
//				height = 1 + rand() % 100;
//			}
//			randomTable[height - 1] = 1;
//
//			int64_t order = 0;
//			if (i - deleted != 0) {
//				order = rand() % (i - deleted);
//			}
//
//			/*std::cout << "command = " << command << " | height = " << height
//				<< " | order = " << order << std::endl;*/
//
//			/*std::cin >> command >> height;*/
//
//			if (command == 1) {
//				std::cout << 1 << ' ' << height << std::endl;
//
//				result.push_back(tree.insert(height));
//			}
//			else if (command == 2) {
//				std::cout << 2 << ' ' << order << std::endl;
//				tree.del(order);
//				++deleted;
//			}
//		}
//
//		std::cout << "result :" << std::endl;
//		for (auto i : result) {
//			std::cout << i << ' ';
//		}
//
//		std::cout << "------------------------------" << std::endl;
//	}
//}