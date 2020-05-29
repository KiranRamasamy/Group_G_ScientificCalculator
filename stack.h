typedef struct
{
	void **content;
	int size;
	int top;
} Stack;

void stackPush(Stack *s, String);

void stackFree(Stack *s);

void stackPush(Stack *s, String val)
{
	(s->top)++;
	s->content[s->top] = val;
}


void stackFree(Stack *s)
{
	if (s->content)
		free(s->content);
	s->content = NULL;
	s->size = 0;
	s->top = -1;
}