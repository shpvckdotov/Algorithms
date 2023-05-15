#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define _INITIAL_CAPACITY_ 100
#define _MAX_ELEMENT_SIZE 1000000
#define _MAX_ELEMENT_MUL_SIZE 1000000000000
#define _MAX_STACK_SIZE_ 10000000000
#define _RESIZE_CONST_ 2
#define _REALLOC_CONST_ 4
#define _MAX_LENGTH_OF_REQUEST_ 256
#define OK 1
#define ERROR 0

const char* pushString = "push";
const char* popString = "pop";
const char* backString = "back";
const char* sizeString = "size";
const char* clearString = "clear";
const char* exitString = "exit";
typedef int data;

struct Stack {
	size_t capacity;
	size_t size;
	data* array;
};

struct Stack* stack_ctr(size_t size, size_t element_size) {
	if (size * element_size > _MAX_ELEMENT_MUL_SIZE) {
		return NULL;
	}
	if (element_size > _MAX_ELEMENT_SIZE) {
		return NULL;
	}
	if (size > _MAX_STACK_SIZE_) {
		return NULL;
	}
	struct Stack* stack;
	if (size <= _INITIAL_CAPACITY_) {
		stack = (struct stack*)malloc(sizeof(struct Stack));
		if (stack == NULL) {
			return NULL;
		}
		stack->array = (data*)malloc(_INITIAL_CAPACITY_ * element_size);
		if (stack->array == NULL) {
			return NULL;
		}
		stack->size = 0;
		stack->capacity = _INITIAL_CAPACITY_;
		return stack;
	}
	else {
		stack = (struct stack*)malloc(sizeof(struct Stack));
		if (stack == NULL) {

		}
		stack->array = (data*)malloc((size * _RESIZE_CONST_) * element_size);
		if (stack->array == NULL) {

		}
		stack->size = 0;
		stack->capacity = size * _RESIZE_CONST_;
		return stack;
	}
}

int push(struct Stack* st, data* buffer) {
	if (st == NULL) {
		return ERROR;
	}
	if (isOverflowed(st->capacity, st->size)) {
		data* tmp;
		tmp = realloc(st->array, (st->capacity * _RESIZE_CONST_) * sizeof(data));
		if (tmp == NULL) {
			return ERROR;
		}
		else {
			st->array = tmp;
			tmp = NULL;
			st->array[st->size] = *buffer;
			st->size++;
			st->capacity = st->capacity * _RESIZE_CONST_;
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
	if (st->size < st->capacity / _REALLOC_CONST_ && st->capacity / _RESIZE_CONST_ < _INITIAL_CAPACITY_) {
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
	if (st->size < st->capacity / _REALLOC_CONST_ && st->capacity / _RESIZE_CONST_ > _INITIAL_CAPACITY_) {
		data* tmp;
		tmp = realloc(st->array, (st->capacity / _RESIZE_CONST_) * sizeof(data));
		if (tmp == NULL) {
			return ERROR;
		}
		else {
			st->array = tmp;
			tmp = NULL;
			st->capacity = st->capacity / _RESIZE_CONST_;
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


int solution(Stack* stack) {
	char requests[_MAX_LENGTH_OF_REQUEST_];
	if (scanf("%s", requests) == 1) {

	}
	else {

	}
	if (!strcmp(requests, pushString)) {
		int n;
		if (scanf("%d", &n) == 1) {

		}
		push(n, stack);
	}
	if (!strcmp(requests, popString)) {
		pop(stack);
	}
	if (!strcmp(requests, backString)) {
		int number;
		top(stack, &number);
		printf("%d", number);
	}
	if (!strcmp(requests, sizeString)) {
		printf("%d", sizeOf(stack));
	}
	if (!strcmp(requests, clearString)) {
		stack_dtr(stack);
		printf("ok\n");
	}
	if (!strcmp(requests, exitString)) {
		stack_dtr(stack);
		printf("bye");
		return -1;
	}
}

typedef struct Stack Stack;

int sizeOf(Stack* stack) {
	return stack->size;
}

int main() {
	Stack* stack;
	stack = stack_ctr(1, 4);
	stack.size = 0;
	while (1) {
		if (solution(stack) == -1) {
			return 0;
		}
	}
}



