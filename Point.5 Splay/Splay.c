#include "Splay.h"

 NodeS* GetParent(NodeS* node) {
    return node ? node->parent : NULL;
}

 NodeS* GetGrandParent(NodeS* node) {
    return GetParent(GetParent(node));
}

 int IsLeftChild(NodeS* node) {
    return GetParent(node) && node == node->parent->left;
}

 IsRightChild(NodeS* node) {
    return GetParent(node) && node == node->parent->right;
}


 NodeS* RotateLeft(NodeS* node) {
    NodeS* tmp = node->left;
    node->right = tmp->left;

    if (node->right) {
        node->right->parent = node;
    }
    if (IsLeftChild(node)) {
        node->parent->left = tmp;
    }
    if (IsRightChild(node)) {
        node->parent->right = tmp;
    }

    tmp->parent = node->parent;
    tmp->left = node;
    node->parent = tmp;

    return tmp;
}

 NodeS* RotateRight(NodeS* node) {
    NodeS* tmp = node->right;
    node->left = tmp->right;
    if (node->left) {
        node->left->parent = node;
    }
    if (IsLeftChild(node)) {
        node->parent->left = tmp;
    }
    if (IsRightChild(node)) {
        node->parent->right = tmp;
    }

    tmp->parent = node->parent;
    tmp->right = node;
    node->parent = tmp;

    return tmp;
}

 void ZigZig(NodeS* parent, NodeS* grandparent) {
    if (IsLeftChild(parent)) {
        grandparent = RotateRight(grandparent);
        parent = RotateRight(parent);
    }
    else {
        grandparent = RotateLeft(grandparent);
        parent = RotateLeft(parent);
    }
}

 void ZigZag(NodeS* parent, NodeS* grandparent) {
    if (IsLeftChild(parent)) {
        parent = RotateLeft(parent);
        grandparent = RotateRight(grandparent);
    }
    else {
        parent = RotateRight(parent);
        grandparent = RotateLeft(grandparent);
    }
}

 void SplayNode(NodeS* node) {
    NodeS* grandparent = NULL;
    NodeS* parent = NULL;
    while (grandparent == GetGrandParent(node)) {
        parent = node->parent;
        if (IsLeftChild(node) == IsLeftChild(parent)) {
            ZigZig(parent, grandparent);
        }
        else {
            ZigZag(parent, grandparent);
        }
    }

    if (IsLeftChild(node)) {
        RotateRight(node->parent);
    }
    if (IsRightChild(node)) {
        RotateLeft(node->parent);
    }
}

 NodeS* NewNode(int key) {
    NodeS* cur = (NodeS*)calloc(1, sizeof(NodeS));
    cur->key = key;
    cur->left = cur->right = cur->parent = NULL;
    return cur;
}


NodeS* SplayTreeInsert(NodeS* root, int key) {
    if (root == NULL) {
        return NewNode(key);
    }

    SplayNode(root);


    if (root->key == key) {
        return root;
    }


    NodeS* cur = NewNode(key);

    if (root->key > key) {
        cur->parent = GetParent(root);
        cur->right = root;
        cur->left = root->left;
        root->left = NULL;
    }
    else {
        cur->parent = GetParent(root);
        cur->left = root;
        cur->right = root->right;
        root->right = NULL;
    }

    return cur;
}

NodeS* SplayTreeSearch(NodeS* root, int key) {
    if (!root) {
        return NULL;
    }
    if (key == root->key) {
        return root;
    }
    if (key < root->key) {
        return SplayTreeSearch(root->left, key);
    }
    else {
        return SplayTreeSearch(root->right, key);
    }
}

void SplayTreeRemove(NodeS* root, int key) {
    NodeS* cur = SplayTreeSearch(root, key);
    if (!cur) {
        return;
    }
    SplayNode(cur);

    NodeS* left = cur->left;
    NodeS* right = cur->right;

    free(cur);
    if (left) {
        left->parent = NULL;
    }
    if (right) {
        right->parent = NULL;
    }

    if (!left) {
        root = right;
        return;
    }
    if (!right) {
        root = left;
        return;
    }

    NodeS* max_left_node = left;

    while (max_left_node->right) {
        max_left_node = max_left_node->right;
    }

    SplayNode(max_left_node);
    max_left_node->right = right;
    right->parent = max_left_node;

    root = max_left_node;
}

void SplayTreeDTOR(NodeS* root) {
    if (!root) {
        return;
    }
    if (root->right) {
        SplayTreeDTOR(root->right);
    }
    if (root->left) {
        SplayTreeDTOR(root->left);
    }

    free(root);
}

