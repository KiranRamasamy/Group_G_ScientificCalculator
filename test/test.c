#include <assert.h>
#include<stdio.h>
#include<stdlib.h>
// #include<conio.h>

#include<string.h>
#include<windows.h>
#include<time.h>
#include <errno.h>
#include "./include/test.h"
#include "../include/main.h"
#include "../include/stack.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 
#include "../include/stack.h"
#include "../test/include/test.h"
#include <getopt.h>
#include <unistd.h>



#define bool char
#define true 1
#define false 0
#define MAXPRECISION 20
#define MAXTOKENLENGTH 512
#define DEFAULTPRECISION 5
#define FUNCTIONSEPARATOR "|"
#define PI 3.141592653589793


#ifndef NAN
#define NAN (0.0/0.0)
#endif

#ifndef INFINITY
#define INFINITY (1.0/0.0)
#endif

typedef double number;
typedef char* token;

typedef enum
{
	addop,
	multop,
	expop,
	lparen,
	rparen,
	digit,
	value,
	decimal,
	space,
	text,
	function,
	identifier,
	argsep,
	invalid
} Symbol;

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




#define ASSERT_TEST(x)                        \
    {                                         \
        if (x)                                \
        {                                     \
            printf("PASSED\n");               \
        }                                     \
        else                                  \
        {                                     \
            printf("%s: FAILED\n", __func__); \
        }                                     \
    }

int perform_func(Stack *s, token function)
{


if (stackSize(s) == 0)
	{
		//throwErr here with missing input
		stackPush(s, number_to_string(NAN));
	
		return -1;
	}
	else if (stackSize(s) == 1 && strcmp(stackTop(s), FUNCTIONSEPARATOR) == 0)
	{
		stackPop(s);
		//throwErr here with missing input
		stackPush(s, number_to_string(NAN));
	
		return -1;
	}
	
	token input = (token)stackPop(s);

	number num = construct_num(input);

	number result = num;
	

	if(strncmp(function, "abs", 3) == 0)
		result = fabs(num);
	else if(strncmp(function, "floor", 5) == 0)
	{
		
		result = floor(num);

	}
		
	else if(strncmp(function, "ceil", 4) == 0)
		result = ceil(num);
	else if(strncmp(function, "sin", 3) == 0)
		result = !prefs.mode.degrees ? sin(num) : sin(convert_to_rad(num));
	else if(strncmp(function, "cos", 3) == 0)
		result = !prefs.mode.degrees ? cos(num) : cos(convert_to_rad(num));
	else if(strncmp(function, "tan", 3) == 0)
		result = !prefs.mode.degrees ? tan(num) : tan(convert_to_rad(num));
	else if(strncmp(function, "arcsin", 6) == 0
		 || strncmp(function, "asin", 4) == 0)
		result = !prefs.mode.degrees ? asin(num) : convert_to_deg(asin(num));
	else if(strncmp(function, "arccos", 6) == 0
		 || strncmp(function, "acos", 4) == 0)
		result = !prefs.mode.degrees ? acos(num) : convert_to_deg(acos(num));
	else if(strncmp(function, "arctan", 6) == 0
		 || strncmp(function, "atan", 4) == 0)
		result = !prefs.mode.degrees ? atan(num) : convert_to_deg(atan(num));
	else if(strncmp(function, "sqrt", 4) == 0)
		result = sqrt(num);
	else if(strncmp(function, "cbrt", 4) == 0)
		result = cbrt(num);
	else if(strncmp(function, "log", 3) == 0)
		result = log(num);
	else if(strncmp(function, "exp", 3) == 0)
		result = exp(num);




	
	return result;
}	





    void automated_perform_functions_test(){
        Stack s;
        stackInit(&s,8);

        
        

		puts("Testing Ceil 4.3, Answer should be 5\n");
		stackPush(&s,"4.3");
		int result = perform_func(&s,"ceil");
		printf("Answer is %d\n",result);
        if(result==5)
        {
            ASSERT_TEST(1);
        }
        else{
            ASSERT_TEST(0);
        }

		//stackPop(&s);
		stackPush(&s,"4.3");
		puts("Testing floor 4.3, result should be 4\n");

			 result = perform_func(&s,"floor");
		printf("Answer is %d\n",result);

 		if(result==4)
        {
            ASSERT_TEST(1);
        }
        else{
            ASSERT_TEST(0);
        }

	

        getchar();
    }