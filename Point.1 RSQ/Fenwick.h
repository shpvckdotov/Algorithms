#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Fenwick.h"

#define SIZE_TREE 1000000
#define SIZE_ARR 1000000
#define N_TEST 5

void modify(long long* tree, int i, int x, int n);

void setTree(long long* tree, int i, int x, long long* a, int n);

void buildTree(long long* a, long long* tree, int n);

long long getSum(long long* tree, int l, int r);
