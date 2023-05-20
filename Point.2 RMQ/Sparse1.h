#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE_ARR 1000000
#define N_TEST 5




void buildDegs(int* logs, int n);

void buildST(int** sparseTable, int* a, int n, int* logs);

int getMin(int** sparseTable, int n, int* logs, int l, int r);
