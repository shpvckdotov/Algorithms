#include "lsdSort.h"


typedef unsigned long long ll;

ll* allocateArray(int size) {
	return (ll*)malloc(size * sizeof(ll));
}

void copyArray(ll* to, ll* from, int size) {
	for (int i = 0; i < size; i++) {
		to[i] = from[i];
	}
}


void LSD(ll* array, int n) {
	ll del = 1;
	for (int i = 1; i <= _MAX_NUMBER_OF_DIGITS_; i++) {
		del *= _DELIMETER_FOR_NUMBER_SYSTEM_;
		ll* answer = allocateArray(n);
		ll cnt[10] = { 0 };
		stableSort(array, del, n,cnt);
		ll t = n;
		do {
			t--;
			ll digit = array[t] % del;
			digit /= (del / _DELIMETER_FOR_NUMBER_SYSTEM_);
			answer[cnt[digit]-- - 1] = array[t];
		} while (t != 0);
		copyArray(array, answer, n);
		free(answer);
	}
}

void stableSort(ll* array, ll del, int n,ll* cnt) {
	for (int j = 0; j < n; j++) {
		ll digit = array[j] % del;
		digit /= (del / _DELIMETER_FOR_NUMBER_SYSTEM_);
		++cnt[digit];
	}
	for (int j = 1; j < _NUMBER_SYSTEM_DIGITS_QUANTITY_; j++) {
		cnt[j] += cnt[j - 1];
	}
}
