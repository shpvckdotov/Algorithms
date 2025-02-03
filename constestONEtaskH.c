#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define _MODCONST_ 10004321
#define _FIRST_NUMERICAL_SEQUENCE_CONST_ 123
#define _SECOND_NUMERICAL_SEQUENCE_CONST_ 45
#define _MEDIAN_PARTITION_CONST_ 5
#define _MID_DELIMETER_CONST 2

struct _Container {
	int* lower;
	int* bigger;
	int* equals;
};

typedef struct _Container Container;

int* allocateArray(int size) {
	return (int*)malloc(size * sizeof(int));
}

void copyArray(int* to, int* from, const size_t size) {
	for (size_t i = 0; i < size; i++) {
		to[i] = from[i];
	}
}

void swap(int* first, int* second) {
	int tmp = *second;
	*second = *first;
	*first = tmp;
}

void partition(Container* container, int* a, const size_t size, int* sizeLower, int* sizeEquals, int pivot) {
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
	counterLower = 0;
	counterEquals = 0;
	counterBigger = 0;
	for (int i = 0; i < size; i++) {
		if (a[i] < pivot) {
			container->lower[counterLower++] = a[i];
		}
		if (a[i] > pivot) {
			container->bigger[counterBigger++] = a[i];
		}
		if (a[i] == pivot) {
			container->equals[counterEquals++] = a[i];
		}
	}
	*sizeLower = counterLower;
	*sizeEquals = counterEquals;
}

void selectSort(int* vector, const size_t size) {
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

void tempArrayInit(int* ar,int temp,int* j) {
	size_t counter = 0;
	while (counter < temp) {
		ar[counter++] = a[*j];
		*j++;
	}
}

void freeArrays(int* first, int* second, int* third) {
	free(first);
	free(second);
	free(third);
}

int kth(int* a, const size_t size, int k) {
	int ar[_MEDIAN_PARTITION_CONST_];
	if (size < _MEDIAN_PARTITION_CONST_) {
		int temp = size % _MEDIAN_PARTITION_CONST_;
		size_t counter;
		tempArrayInit(ar, temp, &counter);
		selectSort(ar, temp);
		return ar[k];
	}
	size_t count = (size) / _MEDIAN_PARTITION_CONST_;
	size_t j = 0;
	int* medians = allocateArray(count + 1);
	size_t i = 0;
	for (i = 0; i < count; i++) {
		tempArrayInit(ar, _MEDIAN_PARTITION_CONST_, &j);
		selectSort(ar, _MEDIAN_PARTITION_CONST_);
		medians[i] = ar[_MID_DELIMETER_CONST];
	}
	int temp = (size) % _MEDIAN_PARTITION_CONST_;
	tempArrayInit(ar, temp, &j);
	selectSort(ar, temp);
	if (temp != 0) {
		medians[i] = ar[temp / _MID_DELIMETER_CONST];
		count++;
	}
	int m = kth(medians, count, count / _MID_DELIMETER_CONST);
	size_t lowerSize;
	size_t equalsSize;
	Container container;
	partition(&container, a, size, &lowerSize, &equalsSize, m);
	if (k < lowerSize) {
		freeArrays(container.bigger, container.equals, a);
		return kth(container.lower, lowerSize, k);
	}
	if (k < lowerSize + equalsSize) {
		freeArrays(container.bigger, container.equals,container.lower);
		free(a);
		return m;
	}
	freeArrays(container.lower, container.equals, a);
	return kth(container.bigger, size - equalsSize - lowerSize, k - equalsSize - lowerSize);
}
void initArray(int* array,int A0,int A1) {
	int* array = allocateArray(n);
	array[0] = A0;
	array[1] = A1;
	for (int i = 2; i < n; i++) {
		int a = (array[i - 1] * _FIRST_NUMERICAL_SEQUENCE_CONST_ + array[i - 2] * _SECOND_NUMERICAL_SEQUENCE_CONST_) % (_MODCONST_);
		array[i] = a;
	}
}
int main() {
	int n,k,A0,A1;
	if (scanf("%d%d%d%d", &n, &k, &A0, &A1) == 1) {

	}
	int* array = NULL;
	initArray(array, A0, A1);
	k--;
	int a = kth(array, n, k);
	printf("%d", a);
}