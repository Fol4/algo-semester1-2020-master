#include <iostream>
#include <algorithm>
#include <queue>

class tree
{
    struct Node
    {
        int64_t key;
        int64_t priority;
        Node* left;
        Node* right;

        Node(int64_t k, int64_t p) : key{ k }, priority{ p }, left{ nullptr }, right{ nullptr } {}
        ~Node() {
            delete left;
            delete right;
        }
    };

    Node* root;

private:
    Node* merge(Node* first, Node* second)
    {
        if (!first or !second)
        {
            return !first ? second : first;
        }

        if (first->priority > second->priority)
        {
            first->right = merge(first->right, second);
            return first;
        }
        else
        {
            second->left = merge(first, second->left);
            return second;
        }
    }

    std::pair<Node*, Node*> split(Node* node, int64_t key)
    {
        if (!node)
        {
            return { nullptr, nullptr };
        }

        if (node->key <= key)
        {
            std::pair<Node*, Node*> pair = split(node->right, key);
            node->right = std::move(pair.first);
            pair.first = std::move(node);

            return pair;
        }
        else
        {
            std::pair<Node*, Node*> pair = split(node->left, key);
            node->left = std::move(pair.second);
            pair.second = std::move(node);

            return pair;
        }
    }

    int64_t deep(Node* node) {
        if (!node) {
            return 0;
        }

        return std::max(deep(node->left), deep(node->right)) + 1;
    }

public:
    tree() : root{ nullptr } {}
    ~tree() {
        delete root;
    }

    void add(const int64_t& key, int64_t priority)
    {
        if (!root) {
            root = new Node{ key, priority };
            return;
        }
        Node* inp_node = new Node{ key, priority };

        std::pair<Node*, Node*> pair = split(root, key);
        Node* tmp = merge(pair.first, inp_node);
        root = merge(tmp, pair.second);
    }

    int64_t maxDeep() {
        return deep(root);
    }

    int64_t maxWidth() {
        std::queue<Node*> Queue;
        Queue.push(root);
        int64_t width = Queue.size();

        while (!Queue.empty()) {
            int64_t n = Queue.size();
            for (int64_t i = 0; i < n; ++i) {
                Node* cur = Queue.front();
                Queue.pop();
                if (cur->left) {
                    Queue.push(cur->left);
                }
                if (cur->right) {
                    Queue.push(cur->right);
                }
            }

            if (Queue.size() > width) {
                width = Queue.size();
            }
        }

        return width;
    }
};

class BinaryTree {
private:
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

    Node* root;

    int64_t deep(Node* node) {
        if (!node) {
            return 0;
        }

        return std::max(deep(node->left), deep(node->right)) + 1;
    }

public:
    BinaryTree() : root{ nullptr } {}
    ~BinaryTree() {
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

    int64_t maxDeep() {
        return deep(root);
    }

    int64_t maxWidth() {
        std::queue<Node*> Queue;
        Queue.push(root);
        int64_t width = Queue.size();

        while (!Queue.empty()) {
            int64_t n = Queue.size();
            for (int64_t i = 0; i < n; ++i) {
                Node* cur = Queue.front();
                Queue.pop();
                if (cur->left) {
                    Queue.push(cur->left);
                }
                if (cur->right) {
                    Queue.push(cur->right);
                }
            }

            if (Queue.size() > width) {
                width = Queue.size();
            }
        }

        return width;
    }
};

int main() {
    int64_t n;

    std::cin >> n;

    BinaryTree bin;
    tree treap;

    for (int64_t i = 0; i < n; ++i) {
        int64_t key, priority;

        std::cin >> key >> priority;

        treap.add(key, priority);
        bin.add(key);
    }

    std::cout << treap.maxWidth() - bin.maxWidth() << std::endl;
}