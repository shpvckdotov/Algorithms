#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "skip_list.h"

#define MAX_LEVEL 5


Node* newnode(int value, int level) {
    Node *node = (Node *) malloc(sizeof(Node));
     node->value = value;
       node->next = (Node **) calloc(level, sizeof(Node *));
    return node;
}


SkipList* newlist() {
  SkipList *list = (SkipList *) malloc(sizeof(SkipList));
  list->size = 0;
  list->level = 1;
  list->head = new_node(INT_MIN, MAX_LEVEL);
  return list;
}


void freenode(Node *node) {
  free(node->next);
  free(node);
}

Node* find_node(SkipList *list, int value) {
  Node *node = list->head;
  int i;
  for (i = list->level - 1; i >= 0; i--) {
    while (node->next[i] != NULL && node->next[i]->value < value) {
      node = node->next[i];
    }
  }
  node = node->next[0];
  if (node != NULL && node->value == value) {
    return node;
  } else {
    return NULL;
  }
}


void insert(SkipList *list, int value) {
  Node *node = list->head;
  Node *update[MAX_LEVEL];
  int i, new_level;
  for (i = list->level - 1; i >= 0; i--) {
    while (node->next[i] != NULL && node->next[i]->value < value) {
      node = node->next[i];
    }
    update[i] = node;
  }
  node = node->next[0];
  if (node == NULL || node->value != value) {
    new_level = 1;
    while (rand() < RAND_MAX / 2 && new_level < MAX_LEVEL) {
      new_level++;
    }
    if (new_level > list->level) {
      for (i = list->level; i < new_level; i++) {
        update[i] = list->head;
      }
      list->level = new_level;
    }
    node = new_node(value, new_level);
    for (i = 0; i < new_level; i++) {
      node->next[i] = update[i]->next[i];
      update[i]->next[i] = node;
    }
    list->size++;
  }
}
void del(SkipList *list, int value) {
  Node *node = list->head;
  Node *update[MAX_LEVEL];
  int i;
  for (i = list->level - 1; i >= 0; i--) {
    while (node->next[i] != NULL && node->next[i]->value < value) {
      node = node->next[i];
    }
    update[i] = node;
  }
  node = node->next[0];
  if (node != NULL && node->value == value) {
    for (i = 0; i < list->level; i++) {
      if (update[i]->next[i] != node) {
        break;
      }
      update[i]->next[i] = node->next[i];
    }
    free_node(node);
    while (list->level > 1 && list->head->next[list->level - 1] == NULL) {
      list->level--;
    }
    list->size--;
  }
}



void dtrlst(Node* node, int i)
{

    if (node == NULL)
    {

        return;

    }

    dtrlst(node->next[i], i);
    free(node);

}


void dtr(SkipList* list)
{

    dtrlst(list->head, list->level - 1);
    free(list);
    

}

void printlist(SkipList *list) {
  Node *node = list->head->next[0];
  while (node != NULL) {
    printf("%d ", node->value);
    node = node->next[0];
  }
  printf("\n");
}
