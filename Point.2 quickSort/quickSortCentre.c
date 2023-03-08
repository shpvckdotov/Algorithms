#include "quickSortCentre.h"













void partitionCentre(data* a, int l, int r, data pivot, int* mm, int* mb) {
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

void quickSortCentre(data* array, int l, int r) {
	int size = r - l;
	if (size == 1 || size == 0) {
		return;
	}
	//data* tempArray = allocateArray(size);
	//copyArray(tempArray, array, l, r);
	data pivot = array[l + size / 2];
	//free(tempArray);
	int mm;
	int mb;
	partitionCentre(array, l, r, pivot, &mm, &mb);
	quickSortCentre(array, l, mm);
	quickSortCentre(array, mb, r);
}
