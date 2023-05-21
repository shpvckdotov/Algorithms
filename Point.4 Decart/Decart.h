#pragma once
#include <stdlib.h>
#include <stddef.h>

#define _NUMBER_ 1000000000
#define INF 9223372036854775806

typedef long long ll;

struct NodeD {
	ll key;
	ll priority;
	ll position;
	struct _Node* l;
	struct _Node* r;
};
typedef struct NodeD NodeD;

struct _Tree {
	NodeD* node;
};

typedef struct _Tree Tree;

void split(NodeD** l, NodeD** r, NodeD* tree, ll key);

void insert(NodeD** tree, NodeD* it);

void merge(NodeD** tree, NodeD* l, NodeD* r);

void erase(NodeD** tree, ll key);

int find(NodeD* tree, ll k);
