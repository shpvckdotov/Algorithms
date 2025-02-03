#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef long long ll;

struct _Container {
	int first;
	int second;
};

typedef struct _Container Container;

struct _Stack {
	int size;
	Container array[200001];
};

typedef struct _Stack Stack;
Stack left;
Stack right;

Container back(Stack* stack) {
	Container fa = (stack->array[stack->size - 1]);
	return fa;
}

void push(int a, Stack* stack) {
	int minimal = (left.size == 0) ? a : min(a, back(&left).second);
	stack->size++;
	stack->array[stack->size - 1].first = a;
	stack->array[stack->size - 1].second = minimal;
}

void pushCool(int a, int m, Stack* stack) {
	stack->size++;
	stack->array[stack->size - 1].first = a;
	stack->array[stack->size - 1].second = m;
}

int pop(Stack* stack) {
	stack->size--;
	return stack->array[stack->size].first;
}

void sizeOf(Stack* stack) {
	printf("%d\n", stack->size);
}

void clear(Stack* stack) {
	stack->size = 0;
	printf("ok\n");
}


int popQueue() {
	if (right.size != 0) {
		return pop(&right);
	}
	else {
		while (left.size != 0) {
			int el = (back(&left)).first;
			pop(&left);
			int minimal = (right.size == 0) ? el : min(el, back(&right).second);
			pushCool(el, minimal, &right);

		}
		return pop(&right);
	}
}


void pushQueue(int a) {
	int minimal = (left.size == 0) ? a : min(a, back(&left).second);
	pushCool(a, minimal, &left);
}


int front() {
	if (right.size != 0) {
		return back(&right).first;
	}
	else {
		while (left.size != 0) {
			int el = back(&left).first;
			pop(&left);
			int minimal = (right.size == 0) ? el : min(el, back(&right).second);
			pushCool(el, minimal, &right);
		}
		return back(&right).first;
	}
}

void clearQueue() {
	right.size = 0;
	left.size = 0;
}


int minimum() {
	if (right.size == 0 || left.size == 0) {
		return (left.size == 0) ? back(&right).second : back(&left).second;
	}
	else {
		return min(back(&right).second, back(&left).second);
	}
}


int queueSize() {
	return left.size + right.size;
}

int main() {
	int m;
	if (scanf("%d", &m) == 1) {

	}

	right.size = 0;
	left.size = 0;


	for (int i = 0; i < m; i++) {
		char requests[256];
		if (scanf("%s", requests) == 1) {

		}
		if (!strcmp(requests, "enqueue")) {
			int n;
			if (scanf("%d", &n)) {

			}
			pushQueue(n);
			printf("ok\n");
		}
		if (!strcmp(requests, "dequeue")) {
			if (queueSize() == 0) {
				printf("error\n");
				continue;
			}
			int a = popQueue();
			printf("%d\n", a);
		}
		if (!strcmp(requests, "front")) {
			if (queueSize() == 0) {
				printf("error\n");
				continue;
			}
			int a = front();
			printf("%d\n", a);
		}
		if (!strcmp(requests, "size")) {
			int size = queueSize();
			printf("%d\n", size);
		}
		if (!strcmp(requests, "clear")) {
			clearQueue();
			printf("ok\n");
		}
		if (!strcmp(requests, "min")) {
			if (queueSize() == 0) {
				printf("error\n");
				continue;
			}
			int a = minimum();
			printf("%d\n", a);
		}
	}
}