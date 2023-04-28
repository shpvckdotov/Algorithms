#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define _NUMBER_ 1000000000
#define _MAX_LENGTH_OF_REQUEST_ 256

typedef long long ll;


struct _Node{
	ll key;
	ll height;
	struct _Node* left;
	struct _Node* right;
};
typedef struct _Node Node;

struct _Tree {
	Node* node;
};

typedef struct _Tree Tree;

ll height(Node* tree) {
	return tree ? tree->height : 0;
}

ll balanceFactor(Node* tree) {
	return height(tree->right) - height(tree->left);
}

void fixHeight(Node* tree){
	ll hl = height(tree->left);
	ll hr = height(tree->right);
	tree->height = (hl > hr ? hl : hr) + 1;
}

Node* rotateRight(Node* tree){
	Node* temp = tree->left;
	tree->left = temp->right;
	temp->right = tree;
	fixHeight(tree);
	fixHeight(temp);
	return temp;
}


Node* rotateLeft(Node* q){
	Node* tree = q->right;
	q->right = tree->left;
	tree->left = q;
	fixHeight(q);
	fixHeight(tree);
	return tree;
}

Node* balance(Node* tree) {
	fixHeight(tree);
	if (balanceFactor(tree) == 2) {
		if (balanceFactor(tree->right) < 0)
			tree->right = rotateRight(tree->right);
		return rotateLeft(tree);
	}
	if (balanceFactor(tree) == -2) {
		if (balanceFactor(tree->left) > 0)
			tree->left = rotateLeft(tree->left);
		return rotateRight(tree);
	}
	return tree;
}

ll next(Node* tree, ll key) {
	Node* now = NULL;
	while (tree != NULL) {
		if (tree->key > key) {
			now = tree;
			tree = tree->left;
		}
		else {
			tree = tree->right;
		}
	}
	if (now == NULL) {
		return -1;
	}
	return now->key;
}

Node* insert(Node* tree, ll key) {
	if (!tree) {
		Node* new = malloc(sizeof(Node));
		new->key = key;
		new->height = 1;
		new->left = NULL;
		new->right = NULL;
		return new;
	}
	if (key < tree->key)
		tree->left = insert(tree->left, key);
	else
		tree->right = insert(tree->right, key);
	return balance(tree);
}

int find(Node* tree, ll key) {
	int b = 1;
	if (!tree) return 0;
	if (key == tree->key) {
		return 1;
	}
	if (key < tree->key)
		b = find(tree->left, key);
	else if (key > tree->key)
		b = find(tree->right, key);
	return b;
}

void plusRequest(Tree* tree, ll* flag,ll* y) {
	ll number;
	if (scanf("%lld", &number)) {

	}
	if (find(tree->node, number) == 1 && flag == 0) {
		*flag = 0;
		return;
	}
	if (*flag == 1) {
		ll key = (number + *y) % _NUMBER_;
		if (find(tree->node, key) == 1) {
			*flag = 0;
			return;
		}
		tree->node = insert(tree->node, key);
	}
	else {
		tree->node = insert(tree->node, number);
	}
	*flag = 0;
}


void exqRequest(Tree* tree, ll* flag,ll* y) {
	*flag = 1;
	ll number;
	if (scanf("%lld", &number)) {

	}
	if (find(tree->node, number) == 1) {
		printf("%lld\n", number);
		*y = number;
		return;
	}
	*y = next(tree->node, number);
	if (*y == -1) {
		printf("%lld\n", *y);
	}
	else {
		printf("%lld\n", *y);
	}
}

int main() {
	ll n,flag,y;
	if (scanf("%lld", &n) == 1) {

	}
	flag = 0;
	y = 0;
	Tree tree;
	tree.node = NULL;
	for (int i = 0; i < n; i++) {
		char requests[_MAX_LENGTH_OF_REQUEST_];
		if (scanf("%s", requests) == 1) {

		}
		if (!strcmp(requests,"+")) {
			plusRequest(&tree, &flag,&y);
		}
		if (!strcmp(requests, "?")) {
			exqRequest(&tree, &flag, &y);
		}
	}
}