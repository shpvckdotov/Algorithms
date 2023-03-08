#pragma once

#include "stdlib.h"



#define _MAX_NUMBER_OF_DIGITS_ 19
#define _DELIMETER_FOR_NUMBER_SYSTEM_ 10
#define _NUMBER_SYSTEM_DIGITS_QUANTITY_ 10



typedef unsigned long long ll;

ll* allocateArray(int size);

void copyArray(ll* to, ll* from, int size);

void LSD(ll* array, int n);

void stableSort(ll* array, ll del, int n ,ll* cnt);