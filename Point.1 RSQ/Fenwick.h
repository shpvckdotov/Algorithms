#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Fenwick.h"

#define SIZE_TREE 1000000
#define SIZE_ARR 1000000
#define N_TEST 5

void modify(long long* tree, int i, int x, int n){
    while (i < n){
        tree[i] += x;
        i = i | (i + 1);
    }
}

void setTree(long long* tree, int i, int x, long long* a, int n){
    long long delta = x - a[i];
    a[i] = x;
    while (i < n){
        tree[i] += x;
        i = i | (i + 1);
    }
}

void buildTree(long long* a, long long* tree, int n){
    for (int i = 0; i < n; i++){
        modify(tree, i, a[i], n);
    }
}

long long getSum(long long* tree, int l, int r){
    long long sum = 0;
    long long s1 = 0;
    long long s2 = 0;
    l--;
    while (l >= 0)
    {
        s1 += tree[l];
        l = (l & (l + 1)) - 1;
    }
    while (r >= 0){
        s2 += tree[r];
        r = (r & (r + 1)) - 1;
    }
    sum = s2 - s1;
    return sum;
}



int main(){
    long long* tree = (long long*)calloc(SIZE_TREE, sizeof(long long));
    long long* a = (long long*)calloc(SIZE_ARR + 10, sizeof(long long));
    long time = 0;
    FILE* fp = fopen("fenwick.txt", "w+");
    for (int i = 0; i < N_TEST; i++) {
        for (int j = 0; j <= SIZE_ARR; j++){
            a[j] = random() % 1000;
        }
        buildTree(a, tree, SIZE_ARR);
        double startTime = getCPUTime();
        for (int j = 0; j < SIZE_ARR; j++){
            char op = random() % 2;
            if (op){
                int l = rand() % (SIZE_ARR - 10);
                l++;
                int len = rand() % (SIZE_ARR - l - 2);
                int r = l + len;
                long long sum = getSum(tree, l, r);
            }
            else
            {
                int x = rand() % 1000;
                int idx = rand() % SIZE_ARR;
                setTree(tree, idx, x, a, SIZE_ARR);
            }
        }
        double endTime = getCPUTime();
        fprintf(fp, "%lf\n", endTime - startTime);
    }
    fclose(fp);
    free(a);
    free(tree);
}