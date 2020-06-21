#include <stdio.h>
#include <stdlib.h>
#include "stack.c"

#define STACKSIZE 150

int main()
{
	Stack strs;
	Stack ints;
	char* str = NULL;

	stackInit(&strs, STACKSIZE);
	stackInit(&ints, STACKSIZE);

	/* To test strings, we are pushing some text into stack and printing*/
	printf("Testing strings strategy:\n");

	str = "This";
	printf("Pushing \"%s\"\n", str);
	stackPush(&strs, str);
	printf("Top of stack: \"%s\"\n", (char*)stackTop(&strs));
	str = "is";
	printf("Pushing \"%s\"\n", str);
	stackPush(&strs, str);
	printf("Top of stack: \"%s\"\n", (char*)stackTop(&strs));
	str = "our";
	printf("Pushing \"%s\"\n", str);
	stackPush(&strs, str);
	printf("Top of stack: \"%s\"\n", (char*)stackTop(&strs));
	str = "calculator";
	printf("Pushing \"%s\"\n", str);
	stackPush(&strs, str);
	printf("Top of stack: \"%s\"\n", (char*)stackTop(&strs));
	str = "program";
	printf("Pushing \"%s\"\n", str);
	stackPush(&strs, str);
	printf("Top of stack: \"%s\"\n", (char*)stackTop(&strs));


	stackFree(&strs);

	return 0;
}