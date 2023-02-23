#ifndef STAC_H
#define STAC_H

#include <stdlib.h>
#include <stddef.h>
#include "stac.h"




struct Stack* stack_ctr(size_t size, size_t element_size) {
	struct Stack* stack;
	stack = (struct stack*)malloc(sizeof(struct Stack));
	if (stack == NULL) {
		return NULL;
	}
	stack->top = NULL;
	stack->size = 0;
}

int push(struct Stack* st, data* buffer) {
	if (st == NULL) {
		return ERROR;
	}
	if (st->size == MAX_CAPACITY) {
		return ERROR;
	}
	if (st->size == 0) {
		struct Node* n = malloc(sizeof(struct Node));
		if (n == NULL) {
			return ERROR;
		}
		n->item = *buffer;
		n->next = NULL;
		st->top = n;
		st->size++;
		return OK;
	}
	else {
		struct Node* n = malloc(sizeof(struct Node));
		if (n == NULL) {
			return ERROR;
		}
		n->item = *buffer;
		n->next = st->top;
		st->top = n;
		st->size++;
		return OK;
	}
}

void freeMemory(struct Stack* st) {
	if (st == NULL) {
		return;
	}
	struct Node* p;
	struct Node* p2;

	p = st->top;

	while (p != NULL)
	{
		p2 = p;
		p = p->next;
		free(p2);
	}
	st->top = NULL;
	st->size = 0;
}

int top(struct Stack* st, data* buffer) {
	if (st == NULL) {
		return ERROR;
	}
	if (st->size == 0) {
		return ERROR;
	}
	else {
		*buffer = st->top->item;
		return OK;
	}
}
int pop(struct Stack* st) {
	if (st == NULL) {
		return ERROR;
	}
	if (st->size > 0) {
		struct Node* tmp;
		tmp = st->top;
		st->top = st->top->next;
		st->size--;
		free(tmp);
		return OK;
	}
	else {
		return ERROR;
	}
}


struct Stack* stack_dtr(struct Stack* st) {
	if (st == NULL) {
		return NULL;
	}
	freeMemory(st);
	free(st);
	return NULL;
}



#endif // STAC_H