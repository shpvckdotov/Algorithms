#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))

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

void copyArray(int* to, int* from, int f, int t) {
	for (int i = 0; f + i < t; i++) {
		to[i] = from[f + i];
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
		int ar[5];
		int counter = 0;
		while (counter < _MEDIAN_PARTITION_CONST_) {
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


void partitionInPlace(int* a, int l, int r, int pivot, int* mm, int* mb) {
	int* lower;
	int* bigger;
	int* equals;
	int counterLower = 0;
	int counterBigger = 0;
	int counterEquals = 0;
	for (int i = l; i < r; i++) {
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
	lower = allocateArray(counterLower);
	bigger = allocateArray(counterBigger);
	equals = allocateArray(counterEquals);
	int counterl = 0;
	int countere = 0;
	int counterb = 0;
	for (int i = l; i < r; i++) {
		if (a[i] < pivot) {
			lower[counterl++] = a[i];
		}
		if (a[i] == pivot) {
			equals[countere++] = a[i];
		}
		if (a[i] > pivot) {
			bigger[counterb++] = a[i];
		}
	}
	int sm = l;
	for (; sm < l + counterLower; sm++) {
		a[sm] = lower[sm - l];
	}
	*mm = sm;
	int asd = sm;
	for (; sm < asd + counterEquals; sm++) {
		a[sm] = equals[sm - asd];
	}
	int abc = sm;
	*mb = sm;
	for (; sm < abc + counterBigger; sm++) {
		a[sm] = bigger[sm - abc];
	}
	free(equals);
	free(bigger);
	free(lower);
}

void quickSort(int* array, int l, int r) {
	int size = r - l;
	if (size == 1 || size == 0) {
		return;
	}
	int* tempArray = allocateArray(size);
	copyArray(tempArray, array, l, r);
	int pivot = kth(tempArray, size, size / 2);
	int mm;
	int mb;
	partitionInPlace(array, l, r, pivot, &mm, &mb);
	quickSort(array, l, mm);
	quickSort(array, mb, r);
}




int main() {
	int n;
	if (scanf("%d", &n) == 1) {

	}
	int* array = allocateArray(n);
	for (int i = 0; i < n; i++) {
		if (scanf("%d", &array[i]) == 1) {

		}
	}
	quickSort(array, 0, n);
	for (int i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}
	free(array);
}