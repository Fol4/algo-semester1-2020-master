#include <iostream>
#include <vector>
#include <stack>

template <typename T>
class Heap {
protected:
	std::vector<T> heap;

	void ShiftUp(size_t index) {
		if (index > heap.size())
			return;

		while (index != 0 && heap[index] > heap[Parent(index)]) {
			std::swap(heap[index], heap[Parent(index)]);
			index = Parent(index);
		}
	}

	size_t GetSwapIndex(size_t childIndex, size_t swapIndex) {
		if (childIndex < heap.size() && heap[childIndex] > heap[swapIndex]) {
			swapIndex = childIndex;
		}
		return swapIndex;
	}

	void ShiftDown(size_t index) {
		while (index < heap.size()) {
			size_t swapIndex = index;
			swapIndex = GetSwapIndex(Left(index), swapIndex);
			swapIndex = GetSwapIndex(Right(index), swapIndex);
			if (swapIndex != index) {
				std::swap(heap[index], heap[swapIndex]);
				index = swapIndex;
			}
			else {
				break;
			}
		}
	}

public:
	Heap() {}

	Heap(const std::vector<T>& arr) : heap(arr) {
		for (size_t i = (heap.size() >> 1); i > 0; --i) {
			ShiftDown(i - 1);
		}
	}

	Heap(const Heap<T>& rhs) : heap(rhs.heap) {}

	Heap(Heap&& rhs) : heap(std::move(rhs.heap)) {}

	Heap& operator=(const Heap<T>& rhs) {
		if (this != &rhs) {
			heap = rhs.heap;
		}
		return *this;
	}

	Heap& operator=(Heap<T>&& rhs) {
		if (this != &rhs) {
			heap = std::move(rhs.heap);
		}
	}

	bool operator==(const Heap& rhs) const {
		return heap == rhs.heap;
	}

	size_t Parent(size_t index) const {
		return (index - 1) >> 1;
	}

	size_t Left(size_t index) const {
		return (index << 1) + 1;
	}

	size_t Right(size_t index) const {
		return (index + 1) << 1;
	}

	bool empty() const {
		return heap.empty();
	}

	const T& top() const {
		return heap.at(0);
	}

	void pop() {
		if (!heap.empty()) {
			std::swap(heap.front(), heap.back());
			heap.resize(heap.size() - 1);
			ShiftDown(0);
		}
	}

	void add(const T& element) {
		heap.push_back(element);
		ShiftUp(heap.size() - 1);
	}
};

int main() {
	int n, k;

	std::cin >> n >> k;

	std::vector<int> input(k);

	for (int i = 0; i < k; ++i) {
		std::cin >> input[i];
	}

	Heap<int> dynamic(input);

	for (int i = 0; i < n - k; ++i) {
		int in;
		std::cin >> in;
		dynamic.add(in);
		dynamic.pop();
	}

	std::stack<int> output;

	for (int i = 0; i < k; ++i) {
		output.push(dynamic.top());
		dynamic.pop();
	}

	for (int i = 0; i < k; ++i) {
		std::cout << output.top() << ' ';
		output.pop();
	}
}