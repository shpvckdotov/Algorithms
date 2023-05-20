#include "Naive.h"

NodeN* newNode(int key) {
    NodeN* node = (NodeN*)malloc(sizeof(NodeN));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

NodeN* insert(NodeN* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

NodeN* search(NodeN* node, int key) {
    if (node == NULL || node->key == key)
        return node;
    if (key < node->key)
        return search(node->left, key);
    else
        return search(node->right, key);
}

NodeN* delete(NodeN* node, int key) {
    if (node == NULL) return node;
    if (key < node->key)
        node->left = delete(node->left, key);
    else if (key > node->key)
        node->right = delete(node->right, key);
    else {
        if (node->left == NULL) {
            NodeN* temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL) {
            NodeN* temp = node->left;
            free(node);
            return temp;
        }
        NodeN* temp = node->right;
        while (temp && temp->left != NULL)
            temp = temp->left;

        node->key = temp->key;

        node->right = delete(node->right, temp->key);
    }
    return node;
}