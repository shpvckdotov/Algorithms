#pragma once

#define INIT_CAP 16

struct Node {
    struct Node* next;
    int key;
};

typedef struct Node Node;

struct HashTable { 
    size_t size;
    size_t capacity;
    Node** buckets;
    size_t (*hash_func)(char* string);
};

typedef struct HashTable HashTable;

struct ListNode {
    Node* node;
    Node* prev;
};

typedef struct ListNode ListNode;

typedef char* hash_elem_t;

HashTable* HashTableCTOR(size_t (*hash_func)(hash_elem_t string));

HashTable* HashTableInsert(HashTable* table, int key);

void HashTableExists(HashTable* table, int key);

HashTable* HashTableRemove(HashTable* table, int key);
