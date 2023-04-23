#pragma once

#include "mergeSort.h"

#include "stdlib.h"

typedef int data;

#define max(a, b) (((a) > (b)) ? (a) : (b))

data* allocateArray(int size);

void copyArray(data* to, data* from, int f, int t);

void merge(data* b, data* c, data* a, int sizeB, int sizeC);

void mergeSort(data* a, int size);

