#ifndef STACK_H
#define STACK_H


#include <stdlib.h>
#include <stddef.h>

#define _INITIAL_CAPACITY_ 100
#define _MAX_ELEMENT_SIZE 1000000
#define _MAX_ELEMENT_MUL_SIZE 1000000000000
#define _MAX_STACK_SIZE_ 10000000000
#define _RESIZE_CONST_ 2
#define _REALLOC_CONST_ 4



#define OK 1
#define ERROR 0

typedef int data;

struct Stack {
	size_t capacity;
	size_t size;
	data* array;
};


struct Stack* stack_ctr(size_t size, size_t element_size); //������� ������ ��������� �������, ������� ����� ����� ���������� � ���� ����������(������ ��� �������)

int push(struct Stack* st, data* buffer); //��������� ������� � ����� ����������, ���������� 1 ���� ���������� �������, 0 - �� �������

int top(struct Stack* st, data* buffer); //���������� ��������� �������

int pop(struct Stack* st); //������� ��������� �������, �� ��������� ���, ���������� 1 - ���� �����, 0 - ���� ������

struct Stack* stack_dtr(struct Stack* st); //���������� ���������, ���������� ������, ���������� nullptr

int isOverflowed(size_t capacity, size_t size);


#endif // STACK_H