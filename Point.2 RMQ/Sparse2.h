#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


#define SIZE_ARR 1000000
#define N_TEST 5


void buildDegs(int* degs, int n);

void buildST(int** sparseTable, int* a, int n, int* degs){
    for (int j = 0; j <= degs[n]; j++){
        for (int i = 1; i <= n; i++){
            if (j == 0){
                sparseTable[j][i] = a[i];
            }
            else{
                if (i + (1 << j) - 1 > n){
                    break;
                }
                sparseTable[j][i] = min(sparseTable[j - 1][i], sparseTable[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
}

int getMin(int** sparseTable, int n, int* degs, int l, int r);

