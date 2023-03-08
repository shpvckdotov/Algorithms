#pragma once

#include "supporting.h"




#define max(a, b) (((a) > (b)) ? (a) : (b))






data kth(data* a, int size, int k);

void bubbleSort(data* array, int start, int end, int shift);

void partitionForQuicksort(data* a, int l, int r, data pivot, int* mm, int* mb);

void quickSortMidMid(data* array, int l, int r);
