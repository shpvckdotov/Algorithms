#pragma once
#include <stdlib.h>
#include <stddef.h>
#include "Splay.h"
#include <stdint.h>

typedef struct NodeS {
    int key;
    struct NodeS* left;
    struct NodeS* right;
    struct NodeS* parent;
} NodeS;

NodeS* GetParent(NodeS* node);

NodeS* GetGrandParent(NodeS* node);

int IsLeftChild(NodeS* node);

IsRightChild(NodeS* node);

NodeS* RotateLeft(NodeS* node);

NodeS* RotateRight(NodeS* node);

void ZigZig(NodeS* parent, NodeS* grandparent);

void ZigZag(NodeS* parent, NodeS* grandparent);

void SplayNode(NodeS* node);

NodeS* NewNode(int key);

NodeS* SplayTreeInsert(NodeS* root, int key);

NodeS* SplayTreeSearch(NodeS* root, int key);

void SplayTreeRemove(NodeS* root, int key);

void SplayTreeDTOR(NodeS* root);

