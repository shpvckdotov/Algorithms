#pragma once
#include <cstdio>
#include <cstdlib>


#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef long long Data;

struct _Key {
    Data value;
    long long time;
};

typedef struct _Key Key;

struct _Heap {
    Key* heap;
    long long* index;
    long long n;
};

typedef struct _Key Key;

typedef struct _Heap Heap;

void swap(Key* first, Key* second);

Key* allocateArray(long long size);

long long* allocateIndex(long long size);

void indexFill(Heap* heap, long long size);

void siftUp(Heap* heap, long long v);

void siftDown(Heap* heap, long long v);

Data getMin(Heap* heap);

void extractMin(Heap* heap);

void insert(Heap* heap, long long i, Data x);

void decreaseKey(Heap* heap, long long i, long long delta);

Heap* createHeap();

void destroyHeap(Heap* heap);


