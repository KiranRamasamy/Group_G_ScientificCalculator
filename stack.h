typedef struct
{
	void **content;
	int size;
	int top;
} Stack;


void stackFree(Stack *s);

void stackFree(Stack *s)
{
	if (s->content)
		free(s->content);
	s->content = NULL;
	s->size = 0;
	s->top = -1;
}