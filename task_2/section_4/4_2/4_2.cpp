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

	std::vector<int> input(n);

	for (int i = 0; i < n; ++i) {
		std::cin >> input[i];
	}

	for (int i = n - 1; i >= 0; i -= k) {
		Heap<int> part;
		int l = 0;

		for (int j = i; j >= 0 and j > i - k; --j) {
			part.add(input[j]);
		}

		if (i != n - 1) {
			while (input[i + l + 1] < part.top()) {
				part.add(input[i + l + 1]);
				++l;
				if (i + l + 1 == n) {
					break;
				}
			}
		}

		int j = i + l;
		while(!part.empty()) {
			input[j] = part.top();
			--j;
			part.pop();
		}
	}

	for (int c : input) {
		std::cout << c << ' ';
	}
}