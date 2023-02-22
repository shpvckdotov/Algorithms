#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define _MODCONST_ 10004321
#define _FIRST_NUMERICAL_SEQUENCE_CONST_ 123
#define _SECOND_NUMERICAL_SEQUENCE_CONST_ 45
#define _MEDIAN_PARTITION_CONST_ 5






struct _Container {
	int* lower;
	int* bigger;
	int* equals;
};


typedef struct _Container Container;






int* allocateArray(int size) {
	return (int*)malloc(size * sizeof(int));
}

void copyArray(int* to, int* from, int size) {
	for (int i = 0; i < size; i++) {
		to[i] = from[i];
	}
}


void swap(int* first, int* second) {
	int tmp = *second;
	*second = *first;
	*first = tmp;
}


void partition(Container* container, int* a, int size, int* sizeLower, int* sizeEquals, int pivot) {
	int counterLower = 0;
	int counterEquals = 0;
	int counterBigger = 0;
	for (int i = 0; i < size; i++) {
		if (a[i] < pivot) {
			counterLower++;
		}
		if (a[i] == pivot) {
			counterEquals++;
		}
		if (a[i] > pivot) {
			counterBigger++;
		}
	}
	container->lower = allocateArray(counterLower);
	container->bigger = allocateArray(counterBigger);
	container->equals = allocateArray(counterEquals);
	int counterl = 0;
	int countere = 0;
	int counterb = 0;
	for (int i = 0; i < size; i++) {
		if (a[i] < pivot) {
			container->lower[counterl++] = a[i];
		}
		if (a[i] > pivot) {
			container->bigger[counterb++] = a[i];
		}
		if (a[i] == pivot) {
			container->equals[countere++] = a[i];
		}
	}
	*sizeLower = counterl;
	*sizeEquals = countere;
}





void selectSort(int* vector, int size) {
	for (int i = 0; i < size; i++) {
		int min = i;
		for (int j = i; j < size; j++) {
			if (vector[j] < vector[min]) {
				min = j;
			}
		}
		swap(&vector[i], &vector[min]);
	}
}

int kth(int* a, int size, int k) {
	if (size < _MEDIAN_PARTITION_CONST_) {
		int temp = size % _MEDIAN_PARTITION_CONST_;
		int ar[_MEDIAN_PARTITION_CONST_];
		int counter = 0;
		while (counter < temp) {
			ar[counter] = a[counter];
			counter++;
		}
		selectSort(ar, temp);
		return ar[k];
	}
	int count = (size) / _MEDIAN_PARTITION_CONST_;
	int j = 0;
	int* medians = allocateArray(count + 1);
	int i = 0;
	for (i = 0; i < count; i++) {
		int ar[_MEDIAN_PARTITION_CONST_];
		int counter = 0;
		while (counter < 5) {
			ar[counter++] = a[j];
			j++;
		}
		selectSort(ar, _MEDIAN_PARTITION_CONST_);
		medians[i] = ar[2];
	}
	int temp = (size) % _MEDIAN_PARTITION_CONST_;
	int ar[_MEDIAN_PARTITION_CONST_];
	int counter = 0;
	while (counter < temp) {
		ar[counter++] = a[j];
		j++;
	}
	selectSort(ar, temp);
	if (temp != 0) {
		medians[i] = ar[temp / 2];
		count++;
	}
	int m = kth(medians, count, count / 2);
	int lowerSize;
	int equalsSize;
	Container container;
	partition(&container, a, size, &lowerSize, &equalsSize, m);
	if (k < lowerSize) {
		free(container.equals);
		free(container.bigger);
		free(a);
		return kth(container.lower, lowerSize, k);
	}
	if (k < lowerSize + equalsSize) {
		free(container.lower);
		free(container.equals);
		free(container.bigger);
		free(a);
		return m;
	}
	free(container.lower);
	free(container.equals);
	free(a);
	return kth(container.bigger, size - equalsSize - lowerSize, k - equalsSize - lowerSize);
}


int main() {
	int n;
	int k;
	int A0;
	int A1;
	if (scanf("%d%d%d%d", &n, &k, &A0, &A1) == 1) {

	}
	int* array = allocateArray(n);
	array[0] = A0;
	array[1] = A1;
	for (int i = 2; i < n; i++) {
		int a = (array[i - 1] * _FIRST_NUMERICAL_SEQUENCE_CONST_ + array[i - 2] * _SECOND_NUMERICAL_SEQUENCE_CONST_) % (_MODCONST_);
		array[i] = a;
	}
	k--;
	int a = kth(array, n, k);
	printf("%d", a);
}