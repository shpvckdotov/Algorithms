#include "supporting.h"


data* allocateArray(int size) {
	return (data*)malloc(size * sizeof(data));
}

void copyArray(data* to, data* from, int f, int t) {
	for (int i = 0; f + i < t; i++) {
		to[i] = from[f + i];
	}
}


void swap(data* first, data* second) {
	data tmp = *second;
	*second = *first;
	*first = tmp;
}