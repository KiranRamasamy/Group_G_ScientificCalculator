#include<stdio.h>

typedef struct
{
	void **content;
	int size;
	int top;
} Stack;

void stackInit(Stack *s, int size);

void stackPush(Stack *s, void* val);

void* stackPop(Stack *s);

void* stackTop(Stack *s);

int stackSize(Stack *s);

void stackFree(Stack *s);

