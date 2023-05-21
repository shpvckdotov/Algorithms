#pragma once
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

struct NodeN {
    int key;
    NodeN* left;
    NodeN* right;
};

typedef struct NodeN NodeN;

NodeN* newNode(int key);

NodeN* insert(NodeN* node, int key);

NodeN* search(NodeN* node, int key);

NodeN* delete(NodeN* node, int key);