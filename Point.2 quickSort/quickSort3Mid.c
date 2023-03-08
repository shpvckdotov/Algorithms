#include "quickSort3Mid.h"




data medianThree(data a, data b, data c) {
    if ((a > b) ^ (a > c))
        return a;
    else if ((b < a) ^ (b < c))
        return b;
    else
        return c;
}


void partition3Mid(data* a, int l, int r, data pivot, int* mm, int* mb) {
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

void quickSort3Mid(data* array, int l, int r) {
	int size = r - l;
	if (size == 1 || size == 0) {
		return;
	}
	//data* tempArray = allocateArray(size);
	//copyArray(tempArray, array, l, r);
	data pivot = medianThree(array[l], array[l + size / 2] , array[r - 1]);
	//free(tempArray);
	int mm;
	int mb;
	partition3Mid(array, l, r, pivot, &mm, &mb);
	quickSort3Mid(array, l, mm);
	quickSort3Mid(array, mb, r);
}
