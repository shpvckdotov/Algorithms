#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))

#define _MAX_LENGTH_OF_REQUEST_ 256

const long long N = 1e5 + 1;

struct _Key {
    long long value;
    long long time;
};



typedef struct _Key Key;



Key* heap;
long long* index;
long long n = 0;

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

void indexFill(long long size) {
    for (long long i = 0; i < size; i++) {
        index[i] = -1;
    }
}

void copyArray(long long* to, long long* from, long long f, long long t) {
    for (long long i = 0; f + i < t; i++) {
        to[i] = from[f + i];
    }
}

void siftUp(long long v) {
    while (v != 1) {
        long long u = v >> 1;
        if (heap[v].value < heap[u].value) {
            index[heap[v].time] = u;
            index[heap[u].time] = v;
            swap(&heap[v], &heap[u]);
            v = u;
        }
        else {
            break;
        }
    }
}

void siftDown(long long v) {
    while (2 * v <= n) {
        long long u = 2 * v;
        if (u + 1 <= n && heap[u + 1].value < heap[u].value) {
            ++u;
        }
        if (heap[v].value > heap[u].value) {
            index[heap[v].time] = u;
            index[heap[u].time] = v;
            swap(&heap[v], &heap[u]);
            v = u;
        }
        else {
            break;
        }
    }
}


long long getMin() {
    return heap[1].value;
}

void extractMin() {
    index[heap[n].time] = 1;
    heap[1] = heap[n--];
    siftDown(1);
}

void insert(long long i, long long x) {
    heap[++n].value = x;
    index[i] = n;
    heap[n].time = i;
    siftUp(n);
}

void decreaseKey(long long i, long long delta) {
    long long v = index[i];
    heap[v].value -= delta;
    siftUp(v);
}



int main() {
    const char* insertString = "insert";
    const char* getMinString = "getMin";
    const char* extractMinString = "extractMin";
    const char* decreaseKeyString = "decreaseKey";
    long long q;
    if (scanf("%lld", &q) == 1) {

    }
    heap = allocateArray(N + 1);
    index = allocateIndex(q + 1);
    indexFill(q + 1);
    for (long long i = 1; i < q + 1; ++i) {
        char requests[_MAX_LENGTH_OF_REQUEST_];
        if (scanf("%s", requests) == 1) {

        }
        if (!strcmp(requests, insertString)) {
            long long x;
            if (scanf("%lld", &x) == 1) {

            }
            insert(i, x);
        }
        if (!strcmp(requests, getMinString)) {
            long long x = getMin();
            printf("%lld\n", x);
        }
        if (!strcmp(requests, extractMinString)) {
            extractMin();
        }
        if (!strcmp(requests, decreaseKeyString)) {
            long long index, delta;
            if (scanf("%lld%lld", &index, &delta) == 1) {

            }
            decreaseKey(index, delta);
        }
    }
    free(index);
    free(heap);
    return 0;
}