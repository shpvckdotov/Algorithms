#include "Decart.h"

void split(NodeD** l, NodeD** r, NodeD* tree, ll key) {
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
}

void insert(NodeD** tree, NodeD* it) {
	if (!*tree)
		*tree = it;
	else if (it->priority > (**tree).priority) {
		split(&(it->l), &(it->r), *tree, it->key);
		*tree = it;
	}
	else {
		insert(it->key < (**tree).key ? &((**tree).l) : &((**tree).r), it);
	}
}

void merge(NodeD** tree, NodeD* l, NodeD* r) {
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
}

void erase(NodeD** tree, ll key) {
	if ((**tree).key == key)
		merge(tree, ((**tree).l), (**tree).r);
	else
		erase(key < (**tree).key ? &((**tree).l) : &((**tree).r), key);
}

int find(NodeD* tree, ll k) {
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
