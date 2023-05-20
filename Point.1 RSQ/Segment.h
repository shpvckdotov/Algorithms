#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N_TEST 5
#define SIZE_TREE 1000000
#define SIZE_ARR 1000000

void buildTree(long long* a, long long* tree, int i, int t_l, int t_r);

void setTree(long long* tree, int i, int x, int idx, int l, int r);

long long getSum(long long* tree, int i, int t_l, int t_r, int l, int r);
