#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define _NUMBER_ 1000000000


#define INF 9223372036854775806

typedef long long ll;

struct _Node {
	ll key;
	ll priority;
	ll sum;
	struct _Node* l;
	struct _Node* r;
};
typedef struct _Node Node;

struct _Tree {
	Node* node;
};

typedef struct _Tree Tree;


ll getSum(Node* tree) {
	return tree ? tree->sum : 0;
}

void updateSum(Node* tree) {
	if (tree)
		tree->sum = getSum(tree->l) + getSum(tree->r) + tree->key;
}

ll next(Node* tree, ll k) {
	Node* temp = NULL;
	while (tree != NULL) {
		if (tree->key > k) {
			temp = tree;
			tree = tree->l;
		}
		else {
			tree = tree->r;
		}
	}
	if (temp == NULL) {
		return INF;
	}
	return temp->key;
}

void split(Node** l, Node** r, Node* tree, ll key) {
	if (!tree) {
		*l = *r = NULL;
		return;
	}
	else if (tree->key > key) {
		split(l, &(tree->l), tree->l, key);
		*r = tree;
	}
	else {
		split(&(tree->r), r, tree->r, key);
		*l = tree;
	}
	updateSum(tree);
}

void insert(Node** tree, Node* newNode) {
	if (!*tree)
		*tree = newNode;
	else if (newNode->priority > (**tree).priority) {
		split(&(newNode->l), &(newNode->r) ,*tree, newNode->key);
		*tree = newNode;
	}
	else {
		insert(newNode->key < (**tree).key ? &((**tree).l) : &((**tree).r), newNode);
	}
	updateSum(*tree);
}

void merge(Node** tree, Node* l, Node* r) {
	if (!l || !r)
		*tree = l ? l : r;
	else if (l->priority > r->priority) {
		merge(&(l->r), l->r, r);
		*tree = l;
	}
	else {
		merge(&(r->l), l, r->l);
		*tree = r;
	}
	updateSum(*tree);
}

int find(Node* tree, ll k) {
	int b = 1;
	if (!tree) return 0;
	if (k == tree->key) {
		return 1;
	}
	if (k < tree->key)
		b = find(tree->l, k);
	else if (k > tree->key)
		b = find(tree->r, k);
	return b;
}

ll sum(Node* tree, ll l, ll r) {
	Node* less;
	Node* greater;
	Node* equal;
	less = NULL;
	equal = NULL;
	greater = NULL;
	split(&less, &greater,tree, l - 1);
	split(&equal, &greater,greater, r);
	ll res = getSum(equal);
	Node* sd = NULL;
	merge(&sd, less, equal);
	merge(&tree, sd, greater);
	return res;
}

void plusRequest(Tree* tree, ll* flag, ll* y) {
	ll m;
	if (scanf("%lld", &m)) {

	}
	if (find(tree->node, m) == 1 && *flag == 0) {
		*flag = 0;
		return;
	}
	if (*flag == 1) {
		ll number = (m + *y) % _NUMBER_;
		if (find(tree->node, number) == 1) {
			*flag = 0;
			return;
		}
		Node* newNode = malloc(sizeof(Node));
		newNode->sum = number;
		newNode->key = number;
		newNode->l = NULL;
		newNode->r = NULL;
		newNode->priority = rand() % 1000000;
		insert(&(tree->node), newNode);
	}
	else {
		Node* newNode = malloc(sizeof(Node));
		newNode->sum = m;
		newNode->key = m;
		newNode->l = NULL;
		newNode->r = NULL;
		newNode->priority = rand() % 1000000;
		insert(&(tree->node), newNode);
	}
	*flag = 0;
}


void exqRequest(Tree* tree, ll* flag, ll* y) {
	*flag = 1;
	ll l;
	ll r;
	if (scanf("%lld%lld", &l, &r)) {

	}
	*y = sum(tree->node, l, r);
	printf("%lld\n", *y);
}

int main() {
	ll n;
	if (scanf("%lld", &n) == 1) {

	}
	ll flag = 0;
	ll y = 0;
	Tree tree;
	tree.node = NULL;
	for (int i = 0; i < n; i++) {
		char requests[256];
		if (scanf("%s", requests) == 1) {

		}
		if (!strcmp(requests, "+")) {
			plusRequest(&tree, &flag, &y);
		}
		if (!strcmp(requests, "?")) {
			exqRequest(&tree, &flag, &y);
		}
	}
}