#include "Avl.h"

typedef long long ll;

struct _Node {
	int key;
	int height;
	struct _Node* left;
	struct _Node* right;
};

typedef struct _Node avlNode;

struct _Tree {
	avlNode* node;
};

typedef struct _Tree Tree;

int height(avlNode* tree) {
	return tree ? tree->height : 0;
}

int balanceFactor(avlNode* tree) {
	return height(tree->right) - height(tree->left);
}

void fixHeight(avlNode* tree) {
	int hl = height(tree->left);
	int hr = height(tree->right);
	tree->height = (hl > hr ? hl : hr) + 1;
}

void swapPointers(avlNode** first, avlNode** second) {
	avlNode* tmp = *first;
	*first = *second;
	*second = tmp;
}

avlNode* rotateRight(avlNode* tree) {
	avlNode* temp = tree->left;
	tree->left = temp->right;
	temp->right = tree;
	fixHeight(tree);
	fixHeight(temp);
	return temp;
}

avlNode* rotateLeft(avlNode* q) {
	avlNode* tree = q->right;
	q->right = tree->left;
	tree->left = q;
	fixHeight(q);
	fixHeight(tree);
	return tree;
}

avlNode* findMin(avlNode* node) {
	avlNode* curr = node;
	while (curr != NULL && curr->left != NULL) {
		curr = curr->left;
	}
	return curr;
}

avlNode* balance(avlNode* tree) {
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

avlNode* insertAvl(avlNode* tree, int key) {
	if (!tree) {
		avlNode* new = malloc(sizeof(avlNode));
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

int find(avlNode* tree, int key) {
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

avlNode* removeMin(avlNode* node) {
	if (node == NULL) {
		return NULL;
	}
	if (node->left == NULL) {
		return node->right;
	}
	node->left = removeMin(node->left);
	return balance(node);
}

avlNode* eraseAvl(avlNode* tree,ll key) {
	if (tree == NULL) {
		return tree;
	}
	if (key < tree->key) {
		tree->left = Erase(tree->left, key);
		return balance(tree);
	}
	if (tree->key < key) {
		tree->right = Erase(tree->right, key);
		return balance(tree);
	}
	if (tree->right == NULL) {
		avlNode* left_child = tree->left;
		free(tree);
		return left_child;
	}

	avlNode* right_min = findMin(tree->right);
	tree->right = removeMin(tree->right);
	swap(&right_min->key, &tree->key);
	free(right_min);
	return balance(tree);
}

void swap(ll* first, ll* second) {
	ll tmp = *first;
	*first = *second;
	*second = tmp;
}