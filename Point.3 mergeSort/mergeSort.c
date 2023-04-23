#include "mergeSort.h"


data* allocateArray(int size) {
	return (data*)malloc(size * sizeof(data));
}

void copyArray(data* to, data* from, int f, int t) {
	for (int i = 0; f + i < t; i++) {
		to[i] = from[f + i];
	}
}

void merge(data* b, data* c, data* a, int sizeB, int sizeC) {
	int i = 0;
	int j = 0;
	int p = 0;
	while (i < sizeB && j < sizeC) {
		if (b[i] <= c[j]) {
			a[p++] = b[i];
			i++;
		}
		else {
			a[p++] = c[j];
			j++;
		}
	}
	while (i < sizeB) {
		a[p++] = b[i];
		i++;
	}
	while (j < sizeC) {
		a[p++] = c[j];
		j++;
	}
}



void mergeSort(data* a, int size) {
	if (size == 1) {
		return;
	}
	int pivot = size / 2;
	int* b = allocateArray(pivot);
	int* c = allocateArray(size - pivot);
	copyArray(b, a, 0, pivot);
	copyArray(c, a, pivot, size);
	mergeSort(b, pivot);
	mergeSort(c, size - pivot);
	merge(b, c, a, pivot, size - pivot);
	free(b);
	free(c);
}
