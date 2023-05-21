#pragma once
#include <iostream>
#include <vector>

using namespace std;

class KHeap {
public:
    KHeap(int k) : k(k) {}
    int pop() {
        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
        return root;
    }

    int top() const {
        return heap[0];
    }

    bool empty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }

    void push(int x) {
        heap.push_back(x);
        int i = heap.size() - 1;
        int parent = (i - 1) / k;
        while (i > 0 && heap[parent] > heap[i]) {
            swap(heap[i], heap[parent]);
            i = parent;
            parent = (i - 1) / k;
        }
    }

    KHeap(int k, vector<int> elements) : k(k), heap(elements) {
        buildHeap();
    }

private:
    int k;
    vector<int> heap;

    void heapify(int i) {
        int min = i;
        for (int j = 1; j <= k; ++j) {
            int child = k * i + j;
            if (child < heap.size() && heap[child] < heap[min]) {
                min = child;
            }
        }
        if (min != i) {
            swap(heap[i], heap[min]);
            heapify(min);
        }
    }

    void buildHeap() {
        for (int i = heap.size() / k; i >= 0; --i) {
            heapify(i);
        }
    }
};

void heapSort(vector<int>& arr, int k) {
    KHeap kh(k, arr);
    arr.clear();
    while (!kh.empty()) {
        arr.push_back(kh.pop());
    }
}