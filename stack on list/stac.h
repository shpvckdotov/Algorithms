#ifndef STACK_H
#define STACK_H


#include <stdlib.h>
#include <stddef.h>


typedef int data;
#define MAX_CAPACITY 1000000000
#define OK 1
#define ERROR 0

struct Node {
	data item;
	struct Node* next;
};

struct Stack {
	struct Node* top;
	size_t capacity;
	size_t size;
};


struct Stack* stack_ctr(size_t size, size_t element_size); //������� ������ ��������� �������, ������� ����� ����� ���������� � ���� ����������(������ ��� �������)

int push(struct Stack* st, data* buffer); //��������� ������� � ����� ����������, ���������� 1 ���� ���������� �������, 0 - �� �������

int top(struct Stack* st, data* buffer); //���������� ��������� �������

int pop(struct Stack* st); //������� ��������� �������, �� ��������� ���, ���������� 1 - ���� �����, 0 - ���� ������

struct Stack* stack_dtr(struct Stack* st); //���������� ���������, ���������� ������, ���������� nullptr

void freeMemory(struct Stack* st);


#endif // STACK_H