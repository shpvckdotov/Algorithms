#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef long long ll;

struct _Stack {
	int size;
	int array[10000];

};

typedef struct _Stack Stack;





void push(int a, Stack* stack) {
	stack->size++;
	stack->array[stack->size - 1] = a;
	printf("ok\n");
}




void pop(Stack* stack) {
	if (stack->size != 0) {
		printf("%d\n", stack->array[stack->size - 1]);
		stack->size--;
	}
	else {
		printf("error\n");
	}
}


void back(Stack* stack) {
	if (stack->size != 0) {
		printf("%d\n", stack->array[stack->size - 1]);
	}
	else {
		printf("error\n");
	}
}


void sizeOf(Stack* stack) {
	printf("%d\n", stack->size);
}


void clear(Stack* stack) {
	stack->size = 0;
	printf("ok\n");
}

#define true 1;
int main() {
	Stack stack;
	stack.size = 0;
	const char* pushString = "push";
	const char* popString = "pop";
	const char* backString = "back";
	const char* sizeString = "size";
	const char* clearString = "clear";
	const char* exitString = "exit";

	while (1) {
		char requests[256];
		if (scanf("%s", requests) == 1) {

		}
		else {

		}
		if (!strcmp(requests, pushString)) {
			int n;
			if (scanf("%d", &n) == 1) {

			}
			push(n, &stack);
		}
		if (!strcmp(requests, popString)) {
			pop(&stack);
		}
		if (!strcmp(requests, backString)) {
			back(&stack);
		}
		if (!strcmp(requests, sizeString)) {
			sizeOf(&stack);
		}
		if (!strcmp(requests, clearString)) {
			clear(&stack);
		}
		if (!strcmp(requests, exitString)) {
			printf("bye");
			return 0;
		}
	}
}



