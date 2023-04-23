#pragma once

#include "supporting.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))






data medianThree(data a, data b, data c);

void partition3Mid(data* a, int l, int r, data pivot, int* mm, int* mb);

void quickSort3Mid(data* array, int l, int r);