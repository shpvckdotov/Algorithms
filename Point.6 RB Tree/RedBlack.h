#pragma once
#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct NodeRB {
    int data;
    int color;
    struct NodeRB* left;
    struct NodeRB* right;
    struct NodeRB* parent;
};

typedef struct NodeRB NodeRB;

void insert(NodeRB** root, int data);

void fixViolation(NodeRB** root, NodeRB* node);

void rotateLeft(NodeRB** root, NodeRB* node);

void rotateRight(NodeRB** root, NodeRB* node);

void swapColors(NodeRB* node1, NodeRB* node2);

void printTree(NodeRB* root);