#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
typedef long long ll;

enum _ToDo {
    nothing,
    assigns,
    add,
    next_permutation,
    previous_permutation,
    reverse
};



void swap(ll* first, ll* second) {
    ll tmp = *first;
    *first = *second;
    *second = tmp;
}



typedef enum _ToDo ToDo;

struct _Node {
    struct _Node* left;
    struct _Node* right;
    ll priority;
    ll subtree_size;
    ll key;
    ll subtreeSum;
    ll subtreeLeftmost;
    ll subtreeRightmost;
    ll toAssign;
    ll toAdd;
    ll longestAscedingPrefixLength;
    ll longestDescedingPrefixLength;
    ll longestAscedingSuffixLength;
    ll longestDescedingSuffixLength;
    char isReversed;
    ToDo toDo;
};


typedef struct _Node Node;


struct _Pair {
    Node* first;
    Node* second;

};


struct _Treap {
    Node* root;
};


typedef struct _Pair Pair;


typedef struct _Treap Treap;

void swapPointers(Node** first, Node** second) {
    Node* tmp = *first;
    *first = *second;
    *second = tmp;
}

void update(Node** node);
void push(Node** node);
void updateSubtreeSize(Node** node);
void updateSubtreeSum(Node** node);
void updateSubtreeLeftmost(Node** node);
void updateSubtreeRightmost(Node** node);
void updateLongestAscedingPrefix(Node** node);
void updateLongestDescedingPrefix(Node** node);
void updateLongestAscedingSuffix(Node** node);
void updateLongestDescedingSuffix(Node** node);
ll getNextInAscedingSegment(Node** node, ll value);
ll getNextInDescedingSegment(Node** node, ll value);
void initNode(Node** node, ll key, ll priority);
Node* copy(Node** node);
void clear(Node** node);
Node* insert(Node** node, Node* new_node, ll pos);
Node* erase(Node** node, ll pos);
Node* segmentChange(Node** node, ll query_left, ll query_right, ToDo change_type, ll value);
ll getSum(Node** node, ll query_left, ll query_right);
void assignment(Node** node, ll value);
void addition(Node** node, ll value);
Node* getNextPermutation(Node** node);
Node* getPreviousPermutation(Node** node);
void reversal(Node** node);
void print(Node** node);
Pair split(Node* node, ll pos);
Node* merge(Node* left, Node* right);
void clearTreap(Treap* treap);
void insertTreap(Treap* treap, ll key, ll pos);
void eraseTreap(Treap* treap, ll pos);
void assignmentTreap(Treap* treap, ll query_left, ll query_right, ll value);
void additionTreap(Treap* treap, ll query_left, ll query_right, ll value);
void nextPermutation(Treap* treap, ll query_left, ll query_right);
void previousPermutation(Treap* treap, ll query_left, ll query_right);
void printTreap(Treap* treap);
ll getSumTreap(Treap* treap, ll query_left, ll query_right);

void update(Node** node) {
    push(node);

    if ((**node).left != NULL) {
        push(&(**node).left);
    }
    if ((**node).right != NULL) {
        push(&(**node).right);
    }
    updateSubtreeSize(node);
    updateSubtreeSum(node);
    updateSubtreeLeftmost(node);
    updateSubtreeRightmost(node);
    updateLongestAscedingPrefix(node);
    updateLongestDescedingPrefix(node);
    updateLongestAscedingSuffix(node);
    updateLongestDescedingSuffix(node);
}

void push(Node** node) {
    if ((**node).isReversed) {
        swapPointers(&(**node).left, &(**node).right);
        swap(&(**node).subtreeLeftmost, &(**node).subtreeRightmost);
        swap(&(**node).longestAscedingPrefixLength, &(**node).longestDescedingSuffixLength);
        swap(&(**node).longestAscedingSuffixLength, &(**node).longestDescedingPrefixLength);
        (**node).isReversed = 0;
        if ((**node).left != NULL) {
            reversal(&(**node).left);
        }
        if ((**node).right != NULL) {
            reversal(&(**node).right);
        }
    }
    switch ((**node).toDo) {
    case nothing:
        break;
    case assigns:
        if ((**node).left != NULL) {
            (**node).left->toAssign = (**node).toAssign;
            (**node).left->toDo = assigns;
        }
        if ((**node).right != NULL) {
            (**node).right->toAssign = (**node).toAssign;
            (**node).right->toDo = assigns;
        }

        (**node).key = (**node).toAssign;
        (**node).subtreeSum = (**node).toAssign * (**node).subtree_size;
        (**node).subtreeLeftmost = (**node).toAssign;
        (**node).subtreeRightmost = (**node).toAssign;
        (**node).toAssign = 0;
        (**node).longestAscedingPrefixLength = (**node).subtree_size;
        (**node).longestDescedingPrefixLength = (**node).subtree_size;
        (**node).longestAscedingSuffixLength = (**node).subtree_size;
        (**node).longestDescedingSuffixLength = (**node).subtree_size;
        break;
    case add:
        if ((**node).left != NULL) {
            switch ((**node).left->toDo) {
            case nothing:
                (**node).left->toAdd = (**node).toAdd;
                (**node).left->toDo = add;
                break;
            case assigns:
                (**node).left->toAssign += (**node).toAdd;
                break;
            case add:
                (**node).left->toAdd += (**node).toAdd;
                break;
            }
        }
        if ((**node).right != NULL) {
            switch ((**node).right->toDo) {
            case nothing:
                (**node).right->toAdd = (**node).toAdd;
                (**node).right->toDo = add;
                break;
            case assigns:
                (**node).right->toAssign += (**node).toAdd;
                break;
            case add:
                (**node).right->toAdd += (**node).toAdd;
                break;
            }
        }
        (**node).key += (**node).toAdd;
        (**node).subtreeSum += (**node).toAdd * (**node).subtree_size;
        (**node).subtreeLeftmost += (**node).toAdd;
        (**node).subtreeRightmost += (**node).toAdd;
        (**node).toAdd = 0;
        break;
    }

    (**node).toDo = nothing;
}

void updateSubtreeSize(Node** node) {
    (**node).subtree_size = (((**node).left == NULL) ? 0 : (**node).left->subtree_size) +
        (((**node).right == NULL) ? 0 : (**node).right->subtree_size) + 1;
}

void updateSubtreeSum(Node** node) {
    (**node).subtreeSum = (((**node).left == NULL) ? 0 : (**node).left->subtreeSum) + (((**node).right == NULL) ? 0 : (**node).right->subtreeSum) + (**node).key;
}

void updateSubtreeLeftmost(Node** node) {
    if ((**node).left != NULL) {
        (**node).subtreeLeftmost = (**node).left->subtreeLeftmost;
    }
    else {
        (**node).subtreeLeftmost = (**node).key;
    }
}

void updateSubtreeRightmost(Node** node) {
    if ((**node).right != NULL) {
        (**node).subtreeRightmost = (**node).right->subtreeRightmost;
    }
    else {
        (**node).subtreeRightmost = (**node).key;
    }
}

void updateLongestAscedingPrefix(Node** node) {
    if ((**node).left == NULL) {
        (**node).longestAscedingPrefixLength = 1;
    }
    else {
        (**node).longestAscedingPrefixLength = (**node).left->longestAscedingPrefixLength;
        if ((**node).left->longestAscedingPrefixLength != (**node).left->subtree_size ||
            (**node).left->subtreeRightmost > (**node).key) {
            return;
        }
        else {
            ++(**node).longestAscedingPrefixLength;
        }
    }
    if ((**node).right != NULL && (**node).key <= (**node).right->subtreeLeftmost) {
        (**node).longestAscedingPrefixLength += (**node).right->longestAscedingPrefixLength;
    }
}

void updateLongestDescedingPrefix(Node** node) {
    if ((**node).left == NULL) {
        (**node).longestDescedingPrefixLength = 1;
    }
    else {
        (**node).longestDescedingPrefixLength = (**node).left->longestDescedingPrefixLength;
        if ((**node).left->longestDescedingPrefixLength != (**node).left->subtree_size ||
            (**node).left->subtreeRightmost < (**node).key) {
            return;
        }
        else {
            ++(**node).longestDescedingPrefixLength;
        }
    }
    if ((**node).right != NULL && (**node).key >= (**node).right->subtreeLeftmost) {
        (**node).longestDescedingPrefixLength += (**node).right->longestDescedingPrefixLength;
    }
}

void updateLongestAscedingSuffix(Node** node) {
    if ((**node).right == NULL) {
        (**node).longestAscedingSuffixLength = 1;
    }
    else {
        (**node).longestAscedingSuffixLength = (**node).right->longestAscedingSuffixLength;
        if ((**node).right->longestAscedingSuffixLength != (**node).right->subtree_size ||
            (**node).right->subtreeLeftmost < (**node).key) {
            return;
        }
        else {
            ++(**node).longestAscedingSuffixLength;
        }
    }
    if ((**node).left != NULL && (**node).key >= (**node).left->subtreeRightmost) {
        (**node).longestAscedingSuffixLength += (**node).left->longestAscedingSuffixLength;
    }
}

void updateLongestDescedingSuffix(Node** node) {
    if ((**node).right == NULL) {
        (**node).longestDescedingSuffixLength = 1;
    }
    else {
        (**node).longestDescedingSuffixLength = (**node).right->longestDescedingSuffixLength;
        if ((**node).right->longestDescedingSuffixLength != (**node).right->subtree_size ||
            (**node).right->subtreeLeftmost > (**node).key) {
            return;
        }
        else {
            ++(**node).longestDescedingSuffixLength;
        }
    }
    if ((**node).left != NULL && (**node).key <= (**node).left->subtreeRightmost) {
        (**node).longestDescedingSuffixLength += (**node).left->longestDescedingSuffixLength;
    }
}

ll getNextInAscedingSegment(Node** node, ll value) {
    push(node);
    if ((**node).key < value) {
        return (((**node).left == NULL) ? 0 : (**node).left->subtree_size) + 1 +
            (((**node).right == NULL) ? 0 : getNextInAscedingSegment(&(**node).right, value));
    }
    else {
        return (((**node).left == NULL) ? 0 : getNextInAscedingSegment(&(**node).left, value));
    }
}

ll getNextInDescedingSegment(Node** node, ll value) {
    push(node);
    if ((**node).key > value) {
        return (((**node).left == NULL) ? 0 : (**node).left->subtree_size) + 1 +
            (((**node).right == NULL) ? 0 : getNextInDescedingSegment(&(**node).right, value));
    }
    else {
        return (((**node).left == NULL) ? 0 : getNextInDescedingSegment(&(**node).left, value));
    }
}

void initNode(Node** node, ll key, ll priority) {
    (**node).key = key;
    (**node).priority = priority;
    (**node).left = NULL;
    (**node).right = NULL;
    (**node).subtree_size = 1;
    (**node).toAssign = 0;
    (**node).toAdd = 0;
    (**node).subtreeSum = key;
    (**node).longestAscedingPrefixLength = 1;
    (**node).longestDescedingPrefixLength = 1;
    (**node).longestAscedingSuffixLength = 1;
    (**node).longestDescedingSuffixLength = 1;
    (**node).isReversed = 0;
    (**node).toDo = nothing;
}

Node* copy(Node** node) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    initNode(&new_node, (**node).key, (**node).priority);
    if ((**node).left != NULL) {
        new_node->left = copy(&(**node).left);
    }
    if ((**node).right != NULL) {
        new_node->right = copy(&(**node).right);
    }
    return new_node;
}

void clear(Node** node) {
    if ((**node).left != NULL) {
        clear(&(**node).left);
    }
    if ((**node).right != NULL) {
        clear(&(**node).right);
    }
    free(*node);
}

Node* insert(Node** node, Node* new_node, ll pos) {
    push(node);
    Pair split_result = split(*node, pos);
    Node* left_treap = split_result.first, * right_treap = split_result.second;

    return merge(left_treap, merge(new_node, right_treap));
}

Node* erase(Node** node, ll pos) {
    if ((**node).subtree_size > 1) {
        push(node);

        Pair split_result;
        split_result.first = NULL;
        split_result.second = NULL;

        split_result = split(*node, pos + 1);
        Node* left_treap = split_result.first, * right_treap = split_result.second;

        split_result = split(left_treap, pos);
        left_treap = split_result.first;
        Node* node_to_delete = split_result.second;

        free(node_to_delete);

        return merge(left_treap, right_treap);
    }
    else {
        free(*node);
        return NULL;
    }
}

Node* segmentChange(Node** node, ll query_left, ll query_right,
    ToDo change_type, ll value) {
    Pair split_result;
    split_result.first = NULL;
    split_result.second = NULL;

    split_result = split(*node, query_left);
    Node* left_treap = split_result.first, * right_treap = split_result.second;

    split_result = split(right_treap, query_right - (query_left - 1) + 1);
    Node* query_treap = split_result.first;
    right_treap = split_result.second;

    switch (change_type) {
    case assigns:
        assignment(&query_treap, value);
        break;
    case add:
        addition(&query_treap, value);
        break;
    case next_permutation:
        getNextPermutation(&query_treap);
        break;
    case previous_permutation:
        getPreviousPermutation(&query_treap);
        break;
    case reverse:
        reversal(&query_treap);
        break;
    }
    return merge(left_treap, merge(query_treap, right_treap));
}

ll getSum(Node** node, ll query_left, ll query_right) {
    push(node);
    Pair split_result;
    split_result.first = NULL;
    split_result.second = NULL;
    split_result = split(*node, query_left);
    Node* left_treap = split_result.first, * right_treap = split_result.second;
    split_result = split(right_treap, query_right - (query_left - 1) + 1);
    Node* middle_treap = split_result.first;
    right_treap = split_result.second;
    ll ans = ((middle_treap == NULL) ? 0 : middle_treap->subtreeSum);
    merge(left_treap, merge(middle_treap, right_treap));
    return ans;
}


void assignment(Node** node, ll value) {
    push(node);
    (**node).toDo = assigns;
    (**node).toAssign = value;
}

void addition(Node** node, ll value) {
    push(node);
    (**node).toDo = add;
    (**node).toAdd = value;
}

Node* getNextPermutation(Node** node) {
    push(node);
    if ((**node).longestDescedingSuffixLength == (**node).subtree_size) {
        reversal(node);
        return *node;
    }
    else {
        Pair split_result;
        split_result.first = NULL;
        split_result.second = NULL;
        split_result = split(*node, (**node).subtree_size - (**node).longestDescedingSuffixLength + 1);
        Node* left_treap = split_result.first, * right_treap = split_result.second;
        split_result = split(left_treap, left_treap->subtree_size);
        left_treap = split_result.first;
        Node* rightmost_node = split_result.second;
        ll pos_to_swap = getNextInDescedingSegment(&right_treap, rightmost_node->key);
        split_result = split(right_treap, pos_to_swap);
        Node* middle_treap = split_result.first;
        right_treap = split_result.second;
        split_result = split(right_treap, 2);
        Node* leftmost_node = split_result.first;
        right_treap = split_result.second;
        right_treap = merge(rightmost_node, right_treap);
        right_treap = merge(middle_treap, right_treap);
        reversal(&right_treap);
        right_treap = merge(leftmost_node, right_treap);
        return merge(left_treap, right_treap);
    }
}

Node* getPreviousPermutation(Node** node) {
    push(node);
    if ((**node).longestAscedingSuffixLength == (**node).subtree_size) {
        reversal(node);
        return *node;
    }
    else {
        Pair split_result;
        split_result.first = NULL;
        split_result.second = NULL;
        split_result = split(*node, (**node).subtree_size - (**node).longestAscedingSuffixLength + 1);
        Node* left_treap = split_result.first, * right_treap = split_result.second;
        split_result = split(left_treap, left_treap->subtree_size);
        left_treap = split_result.first;
        Node* rightmost_node = split_result.second;
        ll pos_to_swap = getNextInAscedingSegment(&right_treap, rightmost_node->key);
        split_result = split(right_treap, pos_to_swap);
        Node* middle_treap = split_result.first;
        right_treap = split_result.second;
        split_result = split(right_treap, 2);
        Node* leftmost_node = split_result.first;
        right_treap = split_result.second;
        right_treap = merge(rightmost_node, right_treap);
        right_treap = merge(middle_treap, right_treap);
        reversal(&right_treap);
        right_treap = merge(leftmost_node, right_treap);
        return merge(left_treap, right_treap);
    }
}

void reversal(Node** node) {
    (**node).isReversed = ((**node).isReversed + 1) % 2;
}


void print(Node** node) {
    push(node);
    if ((**node).left != NULL) {
        print(&(**node).left);
    }
    printf("%lld ", (**node).key);
    if ((**node).right != NULL) {
        print(&(**node).right);
    }
}




Pair split(Node* node, ll pos) {
    Pair result;
    result.first = NULL;
    result.second = NULL;
    if (node != NULL) {
        push(&node);
        if (((node->left == NULL) ? 0 : node->left->subtree_size) + 1 >= pos) {
            Pair split_result = split(node->left, pos);
            node->left = split_result.second;
            update(&node);
            result.first = split_result.first;
            result.second = node;
        }
        else {
            Pair split_result = split(node->right, pos -
                ((node->left == NULL) ? 0 : node->left->subtree_size) - 1);
            node->right = split_result.first;
            update(&node);
            result.second = split_result.second;
            result.first = node;
        }
    }
    return result;
}

Node* merge(Node* left, Node* right) {
    Node* result = NULL;
    if (left == NULL) {
        result = right;
    }
    else if (right == NULL) {
        result = left;
    }
    else {
        push(&left);
        push(&right);
        if (left->priority < right->priority) {
            left->right = merge(left->right, right);
            result = left;
        }
        else {
            right->left = merge(left, right->left);
            result = right;
        }
    }
    update(&result);
    return result;
}



void clearTreap(Treap* treap) {
    clear(&treap->root);
}

void insertTreap(Treap* treap, ll key, ll pos) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    initNode(&new_node, key, ((long long)rand() * 100 + (long long)rand()));
    if (treap->root == NULL) {
        treap->root = new_node;
    }
    else {
        treap->root = insert(&treap->root, new_node, pos);
    }
}

void eraseTreap(Treap* treap, ll pos) {
    treap->root = erase(&treap->root, pos);
}

void assignmentTreap(Treap* treap, ll query_left, ll query_right, ll value) {
    treap->root = segmentChange(&treap->root, query_left, query_right, assigns, value);
}

void additionTreap(Treap* treap, ll query_left, ll query_right, ll value) {
    treap->root = segmentChange(&treap->root, query_left, query_right, add, value);
}

void nextPermutation(Treap* treap, ll query_left, ll query_right) {
    treap->root = segmentChange(&treap->root, query_left, query_right, next_permutation, 0);
}

void previousPermutation(Treap* treap, ll query_left, ll query_right) {
    treap->root = segmentChange(&treap->root, query_left, query_right, previous_permutation, 0);
}

void printTreap(Treap* treap) {
    if (treap->root != NULL) {
        print(&treap->root);
        printf("\n");
    }
}

ll getSumTreap(Treap* treap, ll query_left, ll query_right) {
    return getSum(&treap->root, query_left, query_right);
}

int main() {
    ll n;
    if (scanf("%lld", &n)) {

    }
    Treap treap;
    treap.root = NULL;
    for (ll pos = 1; pos <= n; ++pos) {
        ll value;
        if (scanf("%lld", &value)) {

        }
        insertTreap(&treap, value, pos);
    }
    ll q;
    if (scanf("%lld", &q)) {

    }
    while (q-- > 0) {
        ll query_type;
        if (scanf("%lld", &query_type)) {

        }
        switch (query_type) {
        case 1: {
            ll l, r;
            if (scanf("%lld%lld", &l, &r)) {

            }
            ++l, ++r;
            printf("%lld\n", getSumTreap(&treap, l, r));
            break;
        }
        case 2: {
            ll value;
            ll pos;
            if (scanf("%lld%lld", &value, &pos)) {

            }
            ++pos;
            insertTreap(&treap, value, pos);
            break;
        }
        case 3: {
            ll pos;
            if (scanf("%lld", &pos)) {

            }
            ++pos;
            eraseTreap(&treap, pos);
            break;
        }
        case 4: {
            ll l, r;
            ll value;
            if (scanf("%lld%lld%lld", &value, &l, &r)) {

            }
            ++l, ++r;
            assignmentTreap(&treap, l, r, value);
            break;
        }
        case 5: {
            ll l, r;
            ll value;
            if (scanf("%lld%lld%lld", &value, &l, &r)) {

            }
            ++l, ++r;
            additionTreap(&treap, l, r, value);
            break;
        }
        case 6: {
            ll l, r;
            if (scanf("%lld%lld", &l, &r)) {

            }
            ++l, ++r;
            nextPermutation(&treap, l, r);
            break;
        }
        case 7: {
            ll l, r;
            if (scanf("%lld%lld", &l, &r)) {

            }
            ++l, ++r;
            previousPermutation(&treap, l, r);
            break;
        }
        }
    }
    printTreap(&treap);
}