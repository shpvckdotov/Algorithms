#include "binaryheap.h"

const long long N = 10000001;
const long long q = 10000001;

void swap(Key* first, Key* second) {
    Key tmp = *second;
    *second = *first;
    *first = tmp;
}

Key* allocateArray(long long size) {
    return (Key*)malloc(size * sizeof(Key));
}

long long* allocateIndex(long long size) {
    return (long long*)malloc(size * sizeof(long long));
}

void indexFill(Heap* heap, long long size) {
    for (long long i = 0; i < size; i++) {
        (heap->index)[i] = -1;
    }
}

void siftUp(Heap* heap, long long v) {
    while (v != 1) {
        long long u = v >> 1;
        if (heap->heap[v].value < heap->heap[u].value) {
            heap->index[heap->heap[v].time] = u;
            heap->index[heap->heap[u].time] = v;
            swap(&heap->heap[v], &heap->heap[u]);
            v = u;
        }
        else {
            break;
        }
    }
}

void siftDown(Heap* heap, long long v) {
    while (2 * v <= heap->n) {
        long long u = 2 * v;
        if (u + 1 <= heap->n && heap->heap[u + 1].value < heap->heap[u].value) {
            ++u;
        }
        if (heap->heap[v].value > heap->heap[u].value) {
            heap->index[heap->heap[v].time] = u;
            heap->index[heap->heap[u].time] = v;
            swap(&heap->heap[v], &heap->heap[u]);
            v = u;
        }
        else {
            break;
        }
    }
}

Data getMin(Heap* heap) {
    return heap->heap[1].value;
}

void extractMin(Heap* heap) {
    heap->index[(heap->heap[heap->n]).time] = 1;
    heap->heap[1] = heap->heap[heap->n--];
    siftDown(heap, 1);
}

void insert(Heap* heap, long long i, Data x) {
    heap->heap[++heap->n].value = x;
    heap->index[i] = heap->n;
    heap->heap[heap->n].time = i;
    siftUp(heap, heap->n);
}

void decreaseKey(Heap* heap, long long i, long long delta) {
    long long v = heap->index[i];
    heap->heap[v].value -= delta;
    siftUp(heap, v);
}


Heap* createHeap() {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->n = 0;
    heap->heap = allocateArray(N + 1);
    heap->index = allocateIndex(q + 1);
    indexFill(heap, q + 1);
    return heap;
}



void destroyHeap(Heap* heap) {
    if (heap == nullptr) {
        return;
    }
    free(heap->heap);
    free(heap->index);
    free(heap);
    return;
}


void heapify(Heap* heap,int i) {
    int leftChild;
    int rightChild;
    int largestChild;

    for (; ; )
    {
        leftChild = 2 * i + 1;
        rightChild = 2 * i + 2;
        largestChild = i;

        if (leftChild < heap->n && heap->heap[leftChild].value > heap->heap[largestChild].value)
        {
            largestChild = leftChild;
        }

        if (rightChild < heap->n && heap->heap[rightChild].value > heap->heap[largestChild].value)
        {
            largestChild = rightChild;
        }

        if (largestChild == i)
        {
            break;
        }

        int temp = heap->heap[i].value;
        heap->heap[i].value = heap->heap[largestChild].value;
        heap->heap[largestChild].value = temp;
        i = largestChild;
    }
}