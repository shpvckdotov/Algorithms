#include "stack.h"



struct Stack* stack_ctr(size_t size, size_t element_size) {
	if (size * element_size > 1000000000000) {
		return NULL;
	}
	if (element_size > 1000000) {
		return NULL;
	}
	if (size > 10000000000) {
		return NULL;
	}
	struct Stack* stack;
	if (size <= _INITIAL_CAPACITY_) {
		stack = (struct stack*)malloc(sizeof(struct Stack));
		stack->array = (data*)malloc( _INITIAL_CAPACITY_ * element_size);
		stack->size = 0;
		stack->capacity = _INITIAL_CAPACITY_;
		return stack;
	} 
	else {
		stack = (struct stack*)malloc(sizeof(struct Stack));
		stack->array = (data*)malloc( (size * 2) * element_size);
		stack->size = 0;
		stack->capacity = size * 2;
		return stack;
	}

}

int push(struct Stack* st, data* buffer) {
	if (st == NULL) {
		return ERROR;
	}
	if (isOverflowed(st->capacity,st->size)) {
		data* tmp;
		tmp = realloc(st->array, (st->capacity * 2) * sizeof(data));
		if (tmp == NULL) {
			return ERROR;
		}
		else {
			st->array = tmp;
			tmp = NULL;
			st->array[st->size] = *buffer;
			st->size++;
			st->capacity = st->capacity * 2;
			return OK;
		}
	}
	st->array[st->size] = *buffer;
	st->size++;
	return OK;
}

int top(struct Stack* st, data* buffer) {
	if (st == NULL) {
		return ERROR;
	}
	if (st->size == 0) {
		return ERROR;
	}
	if (st == NULL) {
		return ERROR;
	}
	*buffer = st->array[st->size - 1];
	return OK;
}

int pop(struct Stack* st) {
	if (st == NULL) {
		return ERROR;
	}
	if (st->size < st->capacity / 4 && st->capacity / 2 < _INITIAL_CAPACITY_) {
		data* tmp;
		tmp = realloc(st->array, (_INITIAL_CAPACITY_) * sizeof(data));
		if (tmp == NULL) {
			return ERROR;
		}
		else {
			st->array = tmp;
			tmp = NULL;
			st->capacity = _INITIAL_CAPACITY_;
			return OK;
		}
	}
	if (st->size < st->capacity / 4 && st->capacity / 2 > _INITIAL_CAPACITY_) {
		data* tmp;
		tmp = realloc(st->array, (st->capacity / 2) * sizeof(data));
		if (tmp == NULL) {
			return ERROR;
		}
		else {
			st->array = tmp;
			tmp = NULL;
			st->capacity = st->capacity / 2;
			return OK;
		}
	}
	if (st->size > 0) {
		st->size--;
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
	free(st->array);
	free(st);
	return NULL;
}


int isOverflowed(size_t capacity, size_t size) {
	if (capacity <= size) {
		return OK;
	}
	else {
		return ERROR;
	}
}