#include "RedBlack.h"

void insert(NodeRB** root, int data) {
    NodeRB* node = (NodeRB*)malloc(sizeof(NodeRB));
    node->data = data;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    NodeRB* parent = NULL;
    NodeRB* current = *root;

    while (current != NULL) {
        parent = current;
        if (node->data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    node->parent = parent;
    if (parent == NULL)
        *root = node;
    else if (node->data < parent->data)
        parent->left = node;
    else
        parent->right = node;
    fix(root, node);
}

void fix(NodeRB** root, NodeRB* node) {
    while (node != *root && node->parent->color == RED) {
        NodeRB* parent = node->parent;
        NodeRB* grandparent = parent->parent;
        if (parent == grandparent->left) {
            NodeRB* uncle = grandparent->right;
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }
            else {
                if (node == parent->right) {
                    rotateLeft(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(root, grandparent);
                swapColors(parent, grandparent);
                node = parent;
            }
        }
        else {
            NodeRB* uncle = grandparent->left;
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            }
            else {
                if (node == parent->left) {
                    rotateRight(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(root, grandparent);
                swapColors(parent, grandparent);
                node = parent;
            }
        }
    }
    (*root)->color = BLACK;
}

void rotateLeft(NodeRB** root, NodeRB* node) {
    NodeRB* y = node->right;
    node->right = y->left;
    if (y->left != NULL)
        y->left->parent = node;
    y->parent = node->parent;
    if (node->parent == NULL)
        *root = y;
    else if (node == node->parent->left)
        node->parent->left = y;
    else
        node->parent->right = y;
    y->left = node;
    node->parent = y;
}

void rotateRight(NodeRB** root, NodeRB* node) {
    NodeRB* y = node->left;
    node->left = y->right;
    if (y->right != NULL)
        y->right->parent = node;
    y->parent = node->parent;
    if (node->parent == NULL)
        *root = y;
    else if (node == node->parent->right)
        node->parent->right = y;
    else
        node->parent->left = y;
    y->right = node;
    node->parent = y;
}

void swapColors(NodeRB* x, NodeRB* y) {
    int temp = x->color;
    x->color = y->color;
    y->color = temp;
}
