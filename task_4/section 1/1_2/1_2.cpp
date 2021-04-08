#include <iostream>
#include <iostream>

class HashTable {
private:
	struct Node {
		std::string val = "";
		bool is_deleted = false;

		void operator=(Node rhs) {
			this->val = rhs.val;
			this->is_deleted = rhs.is_deleted;
		}
	};

	Node* table = new Node[8];
	uint64_t capacity = 8;
	uint64_t size = 0;
	uint64_t hashV1 = 11;
	uint64_t hashV2 = 13;

	void resize() {

		capacity *= 4;
		Node* new_table = new Node[capacity];

		std::swap(table, new_table);

		for (uint64_t i = 0; i < capacity / 4; ++i) {
			if (new_table[i].val != "") {
				add(new_table[i].val);
			}
		}

		delete[] new_table;
	}

	uint64_t hash1(const std::string& str) {

		uint64_t newHash = 0;

		for (int64_t i = str.size() - 1; i >= 0; --i) {
			newHash = (hashV1 * newHash + str[i]) % capacity;
		}

		return newHash % capacity;
	}

	uint64_t hash2(const std::string& str) {

		uint64_t newHash = 0;

		for (int64_t i = str.size() - 1; i >= 0; --i) {
			newHash = (hashV2 * newHash + str[i]) % capacity;
		}

		return (newHash * 2 + 1) % capacity;
	}

public:

	bool add(const std::string& str) {

		uint64_t index = hash1(str);
		uint64_t step = hash2(str);

		while (table[index].val != "") {
			if (table[index].val == str) {
				return false;
			}

			index = (index + step) % capacity;
		}

		table[index].val = str;
		table[index].is_deleted = false;
		size++;

		if ((double)size / (double)capacity > 0.75) {
			resize();
		}

		return true;
	}

	bool del(const std::string& str) {

		uint64_t index = hash1(str);
		uint64_t step = hash2(str);

		while (table[index].val != "" or table[index].is_deleted) {
			if (table[index].val == str) {
				table[index].val = "";
				table[index].is_deleted = true;
				size--;

				return true;
			}

			index = (index + step) % capacity;

		}

		return false;
	}

	bool check(const std::string& str) {

		uint64_t index = hash1(str);
		uint64_t step = hash2(str);

		while (table[index].val != "" or table[index].is_deleted) {
			if (table[index].val == str) {
				return true;
			}

			index = (index + step) % capacity;
		}

		return false;
	}
};

int main() {
	char tmp;
	HashTable t;

	while (std::cin >> tmp) {
		char tmpS;
		std::string input;
		std::cin >> input;

		if (tmp == '?') {
			std::cout << (t.check(input) ? "OK" : "FAIL") << std::endl;
		}
		else if (tmp == '+') {
			std::cout << (t.add(input) ? "OK" : "FAIL") << std::endl;
		}
		else if (tmp == '-') {
			std::cout << (t.del(input) ? "OK" : "FAIL") << std::endl;
		}
	}
}