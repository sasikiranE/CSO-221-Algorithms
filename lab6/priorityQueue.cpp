#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class maxHeap {
    vector<int> items;
    int size;

public:
    maxHeap() {
        size = 0;
    }

    maxHeap(vector<int> &arr) {
        size = arr.size();
        for (int i = 0; i < size; i++) {
            items.push_back(arr[i]);
        }
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    void insert(int value) {
        items.push_back(value);
        size++;
        bubbleUp();
    }

    bool isEmpty() { return size == 0; }

    int top() {
        if (size == 0) return INT_MIN;
        return items[0];
    }

    void pop() {
        if (size == 0) {
            return;
        }
        items[0] = items[size - 1];
        size--;
        int index = 0;
        heapify(index);
    }

private:
    int parent(int x) {
        return (x - 1) / 2;
    }

    int left(int x) {
        return 2 * x + 1;
    }

    int right(int x) {
        return 2 * x + 2;
    }

    void bubbleUp() {
        int index = size - 1;
        while (index > 0 and items[index] > items[parent(index)]) {
            swap(items[index], items[parent(index)]);
            index = parent(index);
        }
    }

    void heapify(int idx) {
        int left_idx = left(idx);
        int right_idx = right(idx);
        int largestChildIndex = idx;
        if (left_idx < size and items[left_idx] > items[largestChildIndex])
            largestChildIndex = left_idx;
        if (right_idx < size and items[right_idx] > items[largestChildIndex])
            largestChildIndex = right_idx;
        if (largestChildIndex != idx) {
            swap(items[idx], items[largestChildIndex]);
            heapify(largestChildIndex);
        }
    }
};


class PriorityQueue {
	maxHeap heap = maxHeap();

public:
	void push(int val) {
		heap.insert(val);
	}

	int top() {
		return heap.top();
	}

	void pop() {
		heap.pop();
	}

	bool isEmpty() {
		return heap.isEmpty();
	}
};

int main() {
	vector<int> v = {9, 4, 10, 18, 5};
	PriorityQueue pq = PriorityQueue();
	for (auto &e : v) {
		pq.push(e);
	}
	while (!pq.isEmpty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << "\n";
	return 0;
}