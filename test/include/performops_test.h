*
 * @file performops_test.h
 *
 * @brief Collections of declaration function of automated unit tests for performops function
 *
 * @author Vinoth Kumar Baskaran - vinothkumarbaskaran@cmail.carleton.ca
 */

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>


#define bool char
#define STACKSIZE 150
#define MAXPRECISION 20
#ifndef NAN
#define NAN (0.0/0.0)
#endif

#ifndef INFINITY
#define INFINITY (1.0/0.0)
#endif

typedef enum
{
	divZero,
	overflow,
	parenMismatch,
	inputMissing,
} Error;
typedef char* token;

typedef double number;

typedef struct
{
	void **content;
	int size;
	int top;
} Stack;


struct Preferences
{
	struct Display
	{
		bool tokens;
		bool postfix;
	} display;
	struct Mode
	{
		bool degrees;
	} mode;
	int precision;
	int maxtokenlength;
} prefs;


void throwErr(Error err);

number constructNum(token str);

token numbertoString(number num);

int performOps(Stack *s, token op);



#endif


