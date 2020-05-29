#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	void **content;
	int size;
	int top;
} Stack;

void stackInit(Stack *stack, int size);

void stackPush(Stack *s, String);

void* stackPop(Stack *s);

void* stackTop(Stack *s);

void stackFree(Stack *s);

int stackSize(Stack *s);

void stackPush(Stack *s, String val)
{
	(s->top)++;
	s->content[s->top] = val;
}

void* stackPop(Stack *s)
{
	void *ret = NULL;
	if(s->top >= 0 && s->content != NULL)
		ret = s->content[(s->top)--];
	return ret;
}

void* stackTop(Stack *s)
{
	void *ret = NULL;
	if(s->top >= 0 && s->content != NULL)
		ret = s->content[s->top];
	return ret;
}

void stackFree(Stack *s)
{
	if (s->content)
		free(s->content);
	s->content = NULL;
	s->size = 0;
	s->top = -1;
}

int stackSize(Stack *s)
{
	return s->top + 1;
}