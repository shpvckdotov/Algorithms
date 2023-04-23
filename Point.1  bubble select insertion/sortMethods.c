#include "sortMethods.h"










void swap(data* first, data* second) {
	data tmp = *second;
	*second = *first;
	*first = tmp;
}






void bubbleSort(data* vector, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = 1; j <= size - i; j++) {
			if (vector[j] < vector[j - 1]) {
				swap(&vector[j], &vector[j - 1]);
			}
		}
	}
}




void selectSort(data* vector, int size) {
	for (int i = 0; i < size; i++) {
		data min = i;
		for (int j = i; j < size; j++) {
			if (vector[j] < vector[min]) {
				min = j;
			}
		}
		swap(&vector[i], &vector[min]);
	}
}








void insertionSort(data* vector, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = i; j > 0 && vector[j - 1] > vector[j]; j--) {
			swap(&vector[j - 1], &vector[j]);
		}
	}
}



