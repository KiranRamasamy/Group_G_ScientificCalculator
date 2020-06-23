/**
 * @file performops_test.c
 *
 * @brief This is the test cases for performops_test function 
 * 
 * @author Vinoth Kumar Baskaran- vinothkumarbaskaran@cmail.carleton.ca
 **/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "performops_test.h"

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

void throwErr(Error err)
{
	char* msg;
	switch(err)
	{
		case divZero:
			msg = "Divide by zero";
			break;
		case overflow:
			msg = "Overflow";
			break;
		case parenMismatch:
			msg = "Parentheses Mismatch";
			break;
		case inputMissing:
			msg = "Input of function missing";
			break;
	}
	printf("\tError: %s\n", msg);
}

number constructNum(token str)
{
	number result = 0;
	result = strtod(str, NULL);
	return result;
}

token numbertoString(number num)
{
	int len = 0;
	int precision = MAXPRECISION;
	if (prefs.precision >= 0 && prefs.precision < precision)
		precision = prefs.precision;
	token str = (token)malloc(prefs.maxtokenlength*sizeof(char));
	len = snprintf(str, prefs.maxtokenlength-1, "%.*f", precision, num);
	if (prefs.precision == -1)
	{
		while (str[len-1] == '0')
		{
			len = snprintf(str, prefs.maxtokenlength-1, "%.*f", --precision, num);
		}
	}

	return str;
}

/**
* @brief This function is used to evaluate a postfix expression.
* It performs the arithmetic operations for the operands in the expression
* @details This function pops two operands from the stack and
*  performs the respective arithmetic operation given in the expression.
*  The value obtained after performing the operation on the operands is pushed onto the stack.
*/

int performOps(Stack *s, token op)
{
	int err = 0;
	token roperand = (token)stackPop(s);
	token loperand = (token)stackPop(s);
	number lside = constructNum(loperand);
	number rside = constructNum(roperand);
	number ret;
	switch(*op)
	{
		case '^':
			{
				ret = pow(lside, rside);
			}
			break;
		case '*':
			{
				ret = lside * rside;
			}
			break;
		case '/':
			{
				if(rside == 0)
				{
					throwErr(divZero);
					if (lside == 0)
						ret = NAN;
					else
						ret = INFINITY;
					err = -1;
				}
				else
					ret = lside / rside;
			}
			break;
		case '%':
			{
				if(rside == 0)
				{
					throwErr(divZero);
					if (lside == 0)
						ret = NAN;
					else
						ret = INFINITY;
					err = -1;
				}
				else
				{
					ret = (int)(lside / rside);
					ret = lside - (ret * rside);
				}
			}
			break;
		case '+':
			{
				ret = lside + rside;
			}
			break;
		case '-':
			{
				ret = lside - rside;
			}
			break;
	}
	stackPush(s, numbertoString(ret));
	return err;
}


int main()
{
    Stack strs1;
    Stack strs2;
    char *str = NULL;
    token op1="*";
    token op2="/";

	int errnum=0;

	stackInit(&strs1, STACKSIZE);
    stackInit(&strs2, STACKSIZE);

/* Two operands (7 & 8) is pushed into stack and '*' operation is performed on the operands and the resultant value is pushed into stack*/

	printf("Pushing values to stack1:\n");

	str = "7";
	printf("Pushing \"%s\"\n", str);
	stackPush(&strs1, str);
	printf("Top of stack1: \"%s\"\n", (char *)stackTop(&strs1));
	str = "8";
	printf("Pushing \"%s\"\n", str);
	stackPush(&strs1, str);
	printf("Top of stack1: \"%s\"\n", (char *)stackTop(&strs1));
	printf("The operator 1 is: %s\n",op1);
    errnum=performOps(&strs1, op1);
    printf("error value:%d",errnum);
    printf("\nTop of stack1: \"%s\"\n", (char *)stackTop(&strs1));



/*Two operands (5,0) is pushed into stack and '/' operation is performed on the operands,since the denominator is zero it throws an error and infinity value is pushed onto the stack*/


	printf("\nPushing values to stack2:\n");

	str = "5";
	printf("\nPushing \"%s\"\n", str);
	stackPush(&strs2, str);
	printf("Top of stack2: \"%s\"\n", (char *)stackTop(&strs2));
	str = "0";
	printf("Pushing \"%s\"\n", str);
	stackPush(&strs2, str);
	printf("Top of stack2: \"%s\"\n", (char *)stackTop(&strs2));
   	printf("The operator 2 is: %s\n",op2);
    errnum=performOps(&strs2, op2);
    printf("error value:%d",errnum);
    printf("\nTop of stack2: \"%s\"\n", (char *)stackTop(&strs2));
}
