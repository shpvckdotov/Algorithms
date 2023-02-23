#ifndef STACK_H
#define STACK_H


#include <stdlib.h>
#include <stddef.h>

#define _INITIAL_CAPACITY_ 100



#define OK 1
#define ERROR 0

typedef int data;

struct Stack {
	size_t capacity;
	size_t size;
	data* array;
};


struct Stack* stack_ctr(size_t size, size_t element_size); //создает массив заданного размера, который потом будет измен€тьс€ в ходе исполнени€(только дл€ массива)

int push(struct Stack* st, data* buffer); //ƒобавл€ет элемент в конец контейнера, возвращает 1 если добавление успешно, 0 - не успешно

int top(struct Stack* st, data* buffer); //¬озвращает последний элемент

int pop(struct Stack* st); //”дал€ет последний элемент, не возвраща€ его, возвращает 1 - если успех, 0 - если ошибка

struct Stack* stack_dtr(struct Stack* st); //”ничтожает контейнер, освобожда€ пам€ть, возвращает nullptr

int isOverflowed(size_t capacity, size_t size);


#endif // STACK_H