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

void* stackTop(Stack *s);

void stackFree(Stack *s);



void stackPush(Stack *s, String val)
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


void stackFree(Stack *s)
{
	if (s->content)
		free(s->content);
	s->content = NULL;
	s->size = 0;
	s->top = -1;
}