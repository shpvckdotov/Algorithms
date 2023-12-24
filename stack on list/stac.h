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


struct Stack* stack_ctr(size_t size, size_t element_size); //создает массив заданного размера, который потом будет измен€тьс€ в ходе исполнени€(только дл€ массива)

int push(struct Stack* st, data* buffer); //ƒобавл€ет элемент в конец контейнера, возвращает 1 если добавление успешно, 0 - не успешно

int top(struct Stack* st, data* buffer); //¬озвращает последний элемент

int pop(struct Stack* st); //”дал€ет последний элемент, не возвраща€ его, возвращает 1 - если успех, 0 - если ошибка

struct Stack* stack_dtr(struct Stack* st); //”ничтожает контейнер, освобожда€ пам€ть, возвращает nullptr

void freeMemory(struct Stack* st);


#endif // STACK_H