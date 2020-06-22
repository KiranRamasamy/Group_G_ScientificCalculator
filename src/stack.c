#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"

void stackInit(Stack *s, int size)
{
	s->content = malloc(size * sizeof(void*));
	s->size = size;
	s->top = -1;
}

void stackPush(Stack *s, void* val)
{
	
	(s->top)++;
	s->content[s->top] = val;
}

void* stackTop(Stack *s)
{
	void *ret = NULL;
	if(s->top >= 0 && s->content != NULL)
		ret = s->content[s->top];
	return ret;
}

void* stackPop(Stack *s)
{
	void *ret = NULL;
	if(s->top >= 0 && s->content != NULL)
		ret = s->content[(s->top)--];
	return ret;
}

int stackSize(Stack *s)
{
	return s->top + 1;
}

void stackFree(Stack *s)
{
	if (s->content)
		free(s->content);
	s->content = NULL;
	s->size = 0;
	s->top = -1;
}

