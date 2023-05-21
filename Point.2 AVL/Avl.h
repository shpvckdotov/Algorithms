#pragma once
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "Avl.h"

typedef long long ll;

struct _NodeAvl {
	int key;
	int height;
	struct _Node* left;
	struct _Node* right;
};
typedef struct _NodeAvl avlNode;


typedef struct _Tree Tree;

int height(avlNode* tree);

int balanceFactor(avlNode* tree);

void fixHeight(avlNode* tree);

void swapPointers(avlNode** first, avlNode** second);

void swap(ll* first, ll* second);

avlNode* rotateRight(avlNode* tree);

avlNode* rotateLeft(avlNode* q);

avlNode* findMin(avlNode* node);

avlNode* balance(avlNode* tree);

avlNode* insertAvl(avlNode* tree, int key);

int find(avlNode* tree, int key);

avlNode* detachMin(avlNode* node);

avlNode* eraseAvl(avlNode* tree, ll key);
