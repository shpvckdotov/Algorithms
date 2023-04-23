#pragma once

#include "supporting.h"


#define max(a, b) (((a) > (b)) ? (a) : (b))






typedef struct _Container Container;

void partitionRandom(data* a, int l, int r, data pivot, int* mm, int* mb);

void quickSortRandom(data* array, int l, int r);