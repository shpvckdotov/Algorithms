#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_functions.h"
#include "hash_table.h"

size_t HashTableSize(HashTable* table) {
    if (!table) {
        return 0;
    }
    return table->size;
}

 double LoadFactor(HashTable* ht) {
    return (double)ht->size / (double)ht->capacity;
} 

Node* NodeCTOR(int key) {
    Node* node = (Node*) calloc(1, sizeof(Node));
    node->key = key;
    return node;
}

ListNode FindList(Node* head, int key) {
    Node* cur = head;
    Node* prev = NULL;
    ListNode node;
    
    while (cur) {

        if (key == cur->key) {
            node.node = cur;
            node.prev = prev;
            return node;
        }
        prev = cur;
        cur = cur->next;
    }
    node.node = cur;
    node.prev = prev;
    return node;
}
void HashTableReHash(HashTable* table) {
    
    Node** cur = (Node**) calloc(table->capacity * 2, sizeof(Node*));

    for (size_t i = 0; i < table->capacity; ++i) {
        Node* tmp = table->buckets[i];
        size_t new_cap = table->capacity * 2;
        while (tmp) {
            size_t hash = table->hash_func(tmp->key) % (new_cap);
            Node* next = cur[hash];
            cur[hash] = NodeCTOR(tmp->key);
            cur[hash]->next = next;

            Node* prev = tmp;
            tmp = tmp->next;
            free(prev);
        }
    }
    free(table->buckets);
    table->capacity = table->capacity * 2;
    table->buckets = cur;
}
ListNode FindListNode(HashTable* table, int key) {
    size_t hash = table->hash_func(key) % table->capacity;
    return FindList(table->buckets[hash], key);
}

HashTable* HashTableCTOR(size_t (*hash_func)(hash_elem_t string)) {
    HashTable* tmp = (HashTable*) calloc(1, sizeof(HashTable));
    tmp->buckets = (Node**) calloc(INIT_CAP, sizeof(Node*));
    tmp->hash_func = hash_func;
    tmp->size = 0;
    tmp->capacity = INIT_CAP;
    return tmp;
}

HashTable* HashTableInsert(HashTable* table, int key) {
    if (LoadFactor(table) > 0.7) {
        HashTableReHash(table);
    }
    struct ListNode res = FindListNode(table, key);
    if (res.node == NULL) {
        Node* cur = NodeCTOR(key);
        if (res.prev == NULL) {
            size_t hash = table->hash_func(key) % table->capacity;
            table->buckets[hash] = cur;
        } 
        else {
            res.prev->next = cur;
        }
        ++table->size;
        return table;
    }

    return table;
}

int HashTableExists(HashTable* table, int key) {
    ListNode res = FindListNode(table, key);
    if (res.node != NULL) {
        return 1;
    }
    return 0;
}

HashTable* HashTableRemove(HashTable* table, int key) {
    ListNode node = FindListNode(table, key);
    if (node.node) {
        if (!node.prev) {
            size_t hash = table->hash_func(key) % table->capacity;
            table->buckets[hash] = node.node->next;
        } 
        else {
            node.prev->next = node.node->next;
        }
        
        free(node.node);
        --table->size;
    }

    return table;
}
