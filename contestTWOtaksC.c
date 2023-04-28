#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define _NUMBER_ 1000000000
#define INF 9223372036854775806

typedef long long ll;

struct _Node {
	ll key;
	ll priority;
	ll position;
	struct _Node* l;
	struct _Node* r;
};
typedef struct _Node Node;

struct _Tree {
	Node* node;
};

typedef struct _Tree Tree;

ll getPosition(Node* tree) {
	return tree ? tree->position : 0;
}

void updatePosition(Node* tree) {
	if (tree)
		tree->position = getPosition(tree->l) + getPosition(tree->r) + 1;
}

ll prev(Node* tree, ll k) {
	Node* temp = NULL;
	while (tree != NULL) {
		if (tree->key < k) {
			temp = tree;
			tree = tree->r;
		}
		else {
			tree = tree->l;
		}
	}
	if (temp == NULL) {
		return INF;
	}
	return temp->key;
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

void split(Node** l, Node** r,Node* tree, ll key) {
	if (!tree) {
		*l = *r = NULL;
		return;
	}
	else if (tree->key > key) {
		split(l, &(tree->l),tree->l, key);
		*r = tree;
	}
	else {
		split(&(tree->r), r,tree->r, key);
		*l = tree;
	}
	updatePosition(tree);
}

void insert(Node** tree, Node* it) {
	if (!*tree)
		*tree = it;
	else if (it->priority > (**tree).priority) {
		split(&(it->l), &(it->r) ,*tree, it->key);
		*tree = it;
	}
	else {
		insert(it->key < (**tree).key ? &((**tree).l) : &((**tree).r), it);
	}
	updatePosition(*tree);
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
	updatePosition(*tree);
}

void erase(Node** tree, ll key) {
	if ((**tree).key == key)
		merge(tree, ((**tree).l), (**tree).r);
	else
		erase(key < (**tree).key ? &((**tree).l) : &((**tree).r), key);
	updatePosition(*tree);
}

ll getStatistic(Node* tree, ll k) {
	if (!tree)
		return INF;
	else if (getPosition(tree->r) == k - 1)
		return tree->key;
	else if (getPosition(tree->r) >= k)
		return getStatistic(tree->r, k);
	else
		return getStatistic(tree->l, k - getPosition(tree->r) - 1);
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

void insertion(Tree* tree,ll* position,ll n) {
	if (find(tree->node, n) == 0) {
		Node* newNode = malloc(sizeof(Node));
		newNode->position = 1;
		newNode->key = n;
		newNode->l = NULL;
		newNode->r = NULL;
		newNode->priority = rand() % 1000000;
		insert(&(tree->node), newNode);
		(*position)++;
	}
}

int main() {
	Tree tree;
	tree.node = NULL;
	ll position = 0;
	char requests[256];
	while (scanf("%s", requests) == 1) {
		ll n;
		if (!strcmp(requests, "insert")) {
			if (scanf("%lld", &n) == 1) {

			}
			insertion(&tree, &position, n);
		}
		if (!strcmp(requests, "delete")) {
			if (scanf("%lld", &n) == 1) {

			}
			if (find(tree.node, n) == 1) {
				erase(&(tree.node), n);
				position--;
			}
		}
		if (!strcmp(requests, "exists")) {
			;
			if (scanf("%lld", &n) == 1) {

			}
			if (find(tree.node, n) == 1) {
				printf("%s", "true\n");
			}
			else {
				printf("%s", "false\n");
			}
		}
		if (!strcmp(requests, "next")) {

			if (scanf("%lld", &n) == 1) {

			}
			ll ans = next(tree.node, n);
			if (ans == INF) {
				printf("%s", "none\n");
			}
			else {
				printf("%lld\n", ans);
			}
		}
		if (!strcmp(requests, "prev")) {
			if (scanf("%lld", &n) == 1) {

			}
			ll ans = prev(tree.node, n);
			if (ans == INF) {
				printf("%s", "none\n");
			}
			else {
				printf("%lld\n", ans);
			}
		}
		if (!strcmp(requests, "kth")) {
			if (scanf("%lld", &n) == 1) {

			}
			if (n + 1 > position || n < 0 || position == 0) {
				printf("%s", "none\n");
			}
			else {
				ll kth = getStatistic(tree.node, position - n);
				printf("%lld\n", kth);
			}
		}
	}
}