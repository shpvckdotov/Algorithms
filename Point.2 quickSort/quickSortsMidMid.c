#include "quickSortsMidMid.h"










void bubbleSort(data* array, int start, int end, int shift) {
	for (int i = 0; i <= end - start + 1; i += shift) {
		for (int j = start + shift; j <= end - i; j += shift) {
			if (array[j] < array[j - shift]) {
				data temp = array[j];
				array[j] = array[j - shift];
				array[j - shift] = temp;
			}
		}
	}
}

data kth(data* array, int start, int end, int shift) {
	for (int i = start; i <= end; i += shift) {
		bubbleSort(array, i, min(i + shift - 1, end), shift);
	}
	if ((end - start) / shift <= 1) {
		return array[start + (end - start) / 2];
	}
	return kth(array, start + (shift + 1) / 2, end, shift * 5);
}



void partitionForQuicksort(data* a, int l, int r, data pivot, int* mm, int* mb) {
	data* lower;
	data* bigger;
	data* equals;
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

void quickSortMidMid(data* array, int l, int r) {
	int size = r - l;
	if (size == 1 || size == 0) {
		return;
	}
	//data* tempArray = allocateArray(size);
	//copyArray(tempArray, array, l, r);
	//data pivot = kth(tempArray, size, size / 2);
	data pivot = kth(array, l, r - 1, 1);
	int mm;
	int mb;
	partitionForQuicksort(array, l, r, pivot, &mm, &mb);
	quickSortMidMid(array, l, mm);
	quickSortMidMid(array, mb, r);
}



