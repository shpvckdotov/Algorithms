#pragma once

#include "supporting.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))






void partitionCentre(data* a, int l, int r, data pivot, int* mm, int* mb);

void quickSortCentre(data* array, int l, int r);