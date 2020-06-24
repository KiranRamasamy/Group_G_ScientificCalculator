/**
 * @file main.c
 *
 * @brief It handles all the calculator operations
 * 
 * @author Indu Guduru - induguduru@cmail.carleton.ca
 * @author Kiran Ramasamy- kiranramasamy@cmail.carleton.ca
 * @author Tejaswini Tummala- tejaswinitummala@cmail.carleton.ca
 * @author Vinoth Kumar Baskaran -vinothkumarbaskaran@cmail.carleton.ca
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 
#include "../include/stack.h"
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

typedef enum
{
	divZero,
	overflow,
	parenMismatch,
	inputMissing,
} Error;

void throw_err(Error err)
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

inline unsigned int toDigit(char ch)
{
	return ch - '0';
}

number construct_num(token str)
{
	number result = 0;
	result = strtod(str, NULL); /*strtod for string to float (double)*/
	return result;
}

token number_to_string(number num)
{
	int len = 0;
	int precision = MAXPRECISION;
	if (prefs.precision >= 0 && prefs.precision < precision)
            {
		precision = prefs.precision;
            }
	token str = (token)malloc(prefs.maxtokenlength*sizeof(char));
	len = snprintf(str, prefs.maxtokenlength-1, "%.*f", precision, num); /* snprintf() formats and stores a series of characters and values in the array buffer */
	if (prefs.precision == -1)
	{
		while (str[len-1] == '0')
		{
			len = snprintf(str, prefs.maxtokenlength-1, "%.*f", --precision, num);
		}
	}

	return str;
}

number convert_to_rad(number degrees)
{
	return degrees * PI / 180.0;
}

number convert_to_deg(number radians)
{
	return radians * 180.0 / PI;
}

int perform_funcs(Stack *s, token function)
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
	number counter = 0;

	if(strncmp(function, "abs", 3) == 0)
		result = fabs(num);
	else if(strncmp(function, "floor", 5) == 0)
		result = floor(num);
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
else if(strncmp(function, "min", 3) == 0)
	{
		while (stackSize(s) > 0 && strcmp(stackTop(s), FUNCTIONSEPARATOR) != 0)
		{
			input = (token)stackPop(s);
			num = construct_num(input);
			if (num < result)
				result = num;
		}
	}
	else if(strncmp(function, "max", 3) == 0)
	{
		while (stackSize(s) > 0 && strcmp(stackTop(s), FUNCTIONSEPARATOR) != 0)
		{
			input = (token)stackPop(s);
			num = construct_num(input);
			if (num > result)
				result = num;
		}
	}
	else if(strncmp(function, "sum", 3) == 0)
	{
		while (stackSize(s) > 0  && strcmp(stackTop(s), FUNCTIONSEPARATOR) != 0)
		{
			input = (token)stackPop(s);
			num = construct_num(input);
			result += num;
		}
	}
	else if(strncmp(function, "avg", 3) == 0 ||
			strncmp(function, "mean", 4) == 0)
	{
		counter = 1;
		while (stackSize(s) > 0  && strcmp(stackTop(s), FUNCTIONSEPARATOR) != 0)
		{
			input = (token)stackPop(s);
			num = construct_num(input);
			result += num;
			counter++;
		}
		result /= counter;
	}
	else if(strncmp(function, "median", 6) == 0)
	{
		Stack tmp, safe;
		counter = 1;
		stackInit(&tmp, (stackSize(s) > 0 ? stackSize(s) : 1));
		stackInit(&safe, (stackSize(s) > 0 ? stackSize(s) : 1));
		stackPush(&tmp, input);
		while (stackSize(s) > 0  && strcmp(stackTop(s), FUNCTIONSEPARATOR) != 0)
		{
			input = (token)stackPop(s);
			num = construct_num(input);
			while (stackSize(&tmp) > 0 && construct_num(stackTop(&tmp)) < num)
			{
				stackPush(&safe, stackPop(&tmp));
			}
			stackPush(&tmp, input);
			while (stackSize(&safe) > 0)
			{
				stackPush(&tmp, stackPop(&safe));
			}
			counter++;
		}
		stackFree(&safe);
		counter = (number)(((int)counter+1)/2);
		while (counter > 1)
		{
			stackPop(&tmp);
			counter--;
		}
		result = construct_num(stackPop(&tmp));
		while (stackSize(&tmp) > 0)
		{
			stackPop(&tmp);
		}
		stackFree(&tmp);
	}	
	else if(strncmp(function, "var", 3) == 0)
	{
		Stack tmp;
		counter = 1;
		stackInit(&tmp, (stackSize(s) > 0 ? stackSize(s) : 1));
		stackPush(&tmp, input);
		number mean = result;
		while (stackSize(s) > 0  && strcmp(stackTop(s), FUNCTIONSEPARATOR) != 0)
		{
			input = (token)stackPop(s);
			stackPush(&tmp, input);
			num = construct_num(input);
			mean += num;
			counter++;
		}
		mean /= counter;
		result = 0;
		while (stackSize(&tmp) > 0)
		{
			input = (token)stackPop(&tmp);
			num = construct_num(input)-mean;
			result += pow(num,2);
		}
		result /= counter;
		stackFree(&tmp);
	}
	if (strcmp(stackTop(s), FUNCTIONSEPARATOR) == 0)
		stackPop(s);
	stackPush(s, number_to_string(result));
	return 0;
}	

int perform_ops(Stack *s, token op)
{
	int err = 0;
	token roperand = (token)stackPop(s);
	token loperand = (token)stackPop(s);
	number lside = construct_num(loperand);
	number rside = construct_num(roperand);
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
					throw_err(divZero);
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
					throw_err(divZero);
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
	stackPush(s, number_to_string(ret));
	return err;
}

/*Release 1 code*/
/*char* get_data_console(FILE* stream)
{
	unsigned int maxlen = 128, size = 128;
	char* bufferMemory = (char*)malloc(maxlen);

	if(bufferMemory != NULL) 
	{
		char ch = EOF;
		int pos = 0;

		
		while((ch = getchar()) != EOF && ch != '\n')
		{
			bufferMemory[pos++] = ch;
			if(pos == size) 
			{
				size = pos + maxlen;
				bufferMemory = (char*)realloc(bufferMemory, size);
			}
		}
		bufferMemory[pos] = '\0'; 
	}
	return bufferMemory;
}*/

/*Release 2 code*/

char* get_data_file(FILE* stream)
{
	unsigned int maxlen = 128, size = 128;
	char* bufferMemory = (char*)malloc(maxlen);

	if(bufferMemory != NULL) /* NULL if malloc() fails */
	{
		char ch = EOF;
		int pos = 0;

		/* Read input characters one by one and resizing the buffer as necessary*/
		while((ch = fgetc(stream)) != EOF && ch != '\n')
		{
			bufferMemory[pos++] = ch;
			if(pos == size) 
			{
				size = pos + maxlen;
				bufferMemory = (char*)realloc(bufferMemory, size);
			}
		}
		bufferMemory[pos] = '\0'; /*Null-terminate the completed string */
	}
	return bufferMemory;
}


Symbol find_type(char ch)
{
	Symbol result;
	switch(ch)
	{
		case '+':
		case '-':
			result = addop;
			break;
		case '*':
		case '/':
		case '%':
			result = multop;
			break;
		case '^':
			result = expop;
			break;
		case '(':
			result = lparen;
			break;
		case ')':
			result = rparen;
			break;
		case '.':
			result = decimal;
			break;
		case ' ':
			result = space;
			break;
		case ',':
			result = argsep;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			result = digit;
			break;
                case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			result = text;
			break;

		default:
			result = invalid;
			break;
	}
	return result;
}

bool if_is_func(token tk)
{
	return (strncmp(tk, "abs", 3) == 0
		|| strncmp(tk, "floor", 5) == 0
		|| strncmp(tk, "ceil", 4) == 0
		|| strncmp(tk, "sin", 3) == 0
		|| strncmp(tk, "cos", 3) == 0
		|| strncmp(tk, "tan", 3) == 0
		|| strncmp(tk, "arcsin", 6) == 0
		|| strncmp(tk, "arccos", 6) == 0
		|| strncmp(tk, "arctan", 6) == 0
		|| strncmp(tk, "asin", 4) == 0
		|| strncmp(tk, "acos", 4) == 0
		|| strncmp(tk, "atan", 4) == 0
		|| strncmp(tk, "sqrt", 4) == 0
		|| strncmp(tk, "cbrt", 4) == 0
		|| strncmp(tk, "log", 3) == 0
		|| strncmp(tk, "min", 3) == 0
		|| strncmp(tk, "max", 3) == 0
		|| strncmp(tk, "sum", 3) == 0
		|| strncmp(tk, "avg", 3) == 0
		|| strncmp(tk, "mean", 4) == 0
		|| strncmp(tk, "median", 6) == 0
		|| strncmp(tk, "var", 3) == 0
		|| strncmp(tk, "exp", 3) == 0);
}

bool if_is_specialval(token tk)
{
	return (strncmp(tk, "nan", 3) == 0 || strncmp(tk, "inf", 3) == 0);
}

Symbol type_of_token(token tk)
{
	if (!tk)
         {
		return invalid;
         }
	Symbol ret = find_type(*tk);
	switch(ret)
	{
		case text:
			if(if_is_func(tk))
                         {
				ret = function;
                         }
			else if(if_is_specialval(tk))
                         {
				ret = value;
                         }
			else
                         {
				ret = identifier;
                         }
			break;
		case addop:
			if(*tk == '-' && strlen(tk) > 1)
                          {
				ret = type_of_token(tk+1);
                          }
			break;
		case decimal:
		case digit:
			ret = value;
			break;
		default:
			break;
	}
	return ret;
}

int convert_to_tokens(char *str, char *(**tokensRef))
{
	int i = 0;
	char** tokens = NULL;
    char ** tmp = NULL;
	char* ptr = str;
	char ch = '\0';
	int numTokens = 0;
	char* tmpToken = malloc((prefs.maxtokenlength+1) * sizeof(char));
	if (!tmpToken)
	{
		fprintf(stderr, "Malloc of temporary buffer failed\n");
		return 0;
	}
	while((ch = *ptr++))
	{
		if(find_type(ch) == invalid) /* Stop tokenizing when we encounter an invalid character */
			break;

		token newToken = NULL;
		tmpToken[0] = '\0';
		switch(find_type(ch))
		{
			case addop:
                               {
                                      /* Check if this is a negative */
					if(ch == '-'
						&& (numTokens == 0
							|| (type_of_token(tokens[numTokens-1]) == addop
								|| type_of_token(tokens[numTokens-1]) == multop
								|| type_of_token(tokens[numTokens-1]) == expop
								|| type_of_token(tokens[numTokens-1]) == lparen
								|| type_of_token(tokens[numTokens-1]) == argsep)))
					{
                                                /* Assemble an n-character (plus null-terminator) number token */
						{
							int len = 1;
							bool hasDecimal = false;
							bool hasExponent = false;

							if(find_type(ch) == decimal) /* Allow numbers to start with decimal */
							{
								//printf("Decimal\n");
								hasDecimal = true;
								len++;
								tmpToken[0] = '0';
								tmpToken[1] = '.';
							}
							else  /* Numbers that do not start with decimal */
							{
								tmpToken[len-1] = ch;
							}

							/* Assemble rest of number */
							for(; /* Don't change len */
								*ptr /* There is a next character and it is not null */
								&& len <= prefs.maxtokenlength
								&& (find_type(*ptr) == digit /* The next character is a digit */
								 	|| ((find_type(*ptr) == decimal /* Or the next character is a decimal */
								 		&& hasDecimal == 0)) /* But we have not added a decimal */
								 	|| ((*ptr == 'E' || *ptr == 'e') /* Or the next character is an exponent */
								 		&& hasExponent == false) /* But we have not added an exponent yet */
								|| ((*ptr == '+' || *ptr == '-') && hasExponent == true)); /* Exponent with sign */
								++len)
							{
								if(find_type(*ptr) == decimal)
									hasDecimal = true;
								else if(*ptr == 'E' || *ptr == 'e')
									hasExponent = true;
								tmpToken[len] = *ptr++;
							}

                                                        /* Append null-terminator */
							tmpToken[len] = '\0';
						}
						break;
					}
                                      /* If it's not part of a number, it's an op - fall through */
				}
                        
                        case multop:
			case expop:
			case lparen:
			case rparen:
			case argsep:
                                 /*Assemble a single-character (plus null-terminator) operation token*/
				{
					tmpToken[0] = ch;
					tmpToken[1] = '\0';
				}
				break;
                        
                        case digit:
			case decimal:
                                  /* Assemble an n-character (plus null-terminator) number token */
				{
					int len = 1;
					bool hasDecimal = false;
					bool hasExponent = false;

					if(find_type(ch) == decimal) /* Allow numbers to start with decimal */
					{
						/* printf("Decimal\n"); */
						hasDecimal = true;
						len++;
						tmpToken[0] = '0';
						tmpToken[1] = '.';
					}
					else /* Numbers that do not start with decimal */
					{
						tmpToken[len-1] = ch;
					}

					/* Assemble rest of number */
					for(; /* Don't change len */
						*ptr /* There is a next character and it is not null */
						&& len <= prefs.maxtokenlength
						&& (find_type(*ptr) == digit /* The next character is a digit */
						 	|| ((find_type(*ptr) == decimal /* Or the next character is a decimal */
						 		&& hasDecimal == 0)) /* But we have not added a decimal */
						 	|| ((*ptr == 'E' || *ptr == 'e') /* Or the next character is an exponent */
						 		&& hasExponent == false) /* But we have not added an exponent yet */
						 	|| ((*ptr == '+' || *ptr == '-') && hasExponent == true)); /* Exponent with sign */
						++len)
					{
						if(find_type(*ptr) == decimal)
							hasDecimal = true;
						else if(*ptr == 'E' || *ptr == 'e')
							hasExponent = true;
						tmpToken[len] = *ptr++;
					}

					/* Append null-terminator */
					tmpToken[len] = '\0';
				}
				break;
                        
                        case text:
                              /* Assemble an n-character (plus null-terminator) text token */
				{
					int len = 1;
					tmpToken[0] = ch;
					for(len = 1; *ptr && find_type(*ptr) == text && len <= prefs.maxtokenlength; ++len)
					{
						tmpToken[len] = *ptr++;
					}
					tmpToken[len] = '\0';
				}
				break;
                        
                        default:
                             break;
                }
             /* Add to list of tokens */
             if(tmpToken[0] != '\0' && strlen(tmpToken) > 0)
		{
			numTokens++;
			/*if(tokens == NULL)- First allocation
				tokens = (char**)malloc(numTokens * sizeof(char*));
			else*/
			newToken = malloc((strlen(tmpToken)+1) * sizeof(char));
			if (!newToken)
			{
				numTokens--;
				break;
			}
			strcpy(newToken, tmpToken);
			newToken[strlen(tmpToken)] = '\0';
			tmp = (char**)realloc(tokens, numTokens * sizeof(char*));
			if (tmp == NULL)
			{
				if (tokens != NULL)
				{
					for(i=0;i<numTokens-1;i++)
					{
						if (tokens[i] != NULL)
							free(tokens[i]);
					}
					free(tokens);
				}
				*tokensRef = NULL;
				free(newToken);
				free(tmpToken);
				return 0;
			}
			tokens = tmp;
			tmp = NULL;
			tokens[numTokens - 1] = newToken;
		}
	}
	*tokensRef = tokens; /* Send back out */
	free(tmpToken);
	tmpToken = NULL;
	return numTokens;
}

bool left_associative(token op)
{
	bool ret = false;
	switch(type_of_token(op))
	{
		case addop:
		case multop:

			ret = true;
			break;
		case function:
		case expop:
			ret = false;
			break;
		default:
			break;
	}
	return ret;
}


int decide_precedence(token op1, token op2)
{
	int ret = 0;

	if (op2 == NULL)
        {
		ret = 1;
	}
	else if(type_of_token(op1) == type_of_token(op2)) 
	{
		ret = 0;
	 }  
	else if(type_of_token(op1) == addop
			&& (type_of_token(op2) == multop || type_of_token(op2) == expop)) 
	{
		ret = -1;
	}
	else if(type_of_token(op2) == addop
			&& (type_of_token(op1) == multop || type_of_token(op1) == expop)) 
	{
		ret = 1;
	}
	else if(type_of_token(op1) == multop
			&& type_of_token(op2) == expop) 
	{
		ret = -1;
	}
	else if(type_of_token(op1) == expop
			&& type_of_token(op2) == multop) 
	{
		ret = 1;
	}
	else if (type_of_token(op1) == function
			&& (type_of_token(op2) == addop || type_of_token(op2) == multop || type_of_token(op2) == expop || type_of_token(op2) == lparen))
	{
		ret = 1;
	}
	else if ((type_of_token(op1) == addop || type_of_token(op1) == multop || type_of_token(op1) == expop)
			&& type_of_token(op2) == function)
	{
		ret = -1;
	}
	return ret;
}

void stack_push_assess(Stack *s, token val)
{
	if(prefs.display.postfix)
		printf("\t%s\n", val);

	switch(type_of_token(val))
	{
		case function:
			{
				if (perform_funcs(s, val) < 0)
					return;
			}
			break;
		case expop:
		case multop:
		case addop:
			{
				if(stackSize(s) >= 2)
				{				
					if (perform_ops(s, val) < 0)
						return;
								
				}
				else
				{
					stackPush(s, val);
				}
			}
			break;
		case value:
			{
				stackPush(s, val);
			}
			break;
		default:
			break;
	}
}


bool postfix(token *tokens, int numTokens, Stack *output)
{
	Stack operators, intermediate;
	int i;
	bool err = false;
	stackInit(&operators, numTokens);
	stackInit(&intermediate, numTokens);
for(i = 0; i < numTokens; i++)
	{
		/*Shunting yard algorithm concept is used*/
		switch(type_of_token(tokens[i]))
		{
			case value:
				{
					/*If the token is a number or value, then add it to the output queue*/
					stack_push_assess(output, tokens[i]); 
				}
				break;
			case function:
				{
					/*If the token is a function token, then push it onto the stack*/
					while(stackSize(&operators) > 0
						&& (type_of_token(tokens[i]) != lparen)
						&& ((decide_precedence(tokens[i], (char*)stackTop(&operators)) <= 0)))
					{
						stack_push_assess(output, stackPop(&operators));
						stackPush(&intermediate, stackTop(output));
					}

					stackPush(&operators, tokens[i]);
				}
				break;
				case argsep:
				{
					/*If the token is a function argument separator such as comma, until the token at the top of the stack is a left
					 paren, pop operators off the stack onto the output queue. If no left paren encountered, either separator
					 was misplaced or parens mismatched and error will be thrown*/
					 
					while(stackSize(&operators) > 0
						&& type_of_token((token)stackTop(&operators)) != lparen
						&& stackSize(&operators) > 1)
					{
						
						stack_push_assess(output, stackPop(&operators));//popping all operators onto output queue till top is left paren
						stackPush(&intermediate, stackTop(output));
					}
					
				}
				break;
			case addop:
			case multop:
			case expop:
				{
					
					/*If the token is an operator, op1, then, while there is an operator token, op2, at the top of the stack, and
					 either op1 is left-associative and its Precedence is less than or equal to that of op2, or op1 is right-associative
					 and its Precedence is less than that of op2, pop op2 off the stack, onto the output queue and push op1 onto the stack*/
	
					while(stackSize(&operators) > 0
						&& (type_of_token((char*)stackTop(&operators)) == addop || type_of_token((char*)stackTop(&operators)) == multop || type_of_token((char*)stackTop(&operators)) == expop)
						&& ((left_associative(tokens[i]) && decide_precedence(tokens[i], (char*)stackTop(&operators)) <= 0)
							|| (!left_associative(tokens[i]) && decide_precedence(tokens[i], (char*)stackTop(&operators)) < 0)))
					{
						
						stack_push_assess(output, stackPop(&operators));
						stackPush(&intermediate, stackTop(output));
					}
					
					stackPush(&operators, tokens[i]);
				}
				break;
			case lparen:
				{
					/*If the token is a left paren, then push it onto the stack*/
					if (type_of_token(stackTop(&operators)) == function)
						stackPush(output, FUNCTIONSEPARATOR);
					stackPush(&operators, tokens[i]);
				}
				break;
			case rparen:
				{
					/*If the token is a right paren, until the token at the top of the stack is a left paren, pop operators off the stack onto the output 
					queue, pop the left paren from the stack, but not onto the output queue and if the stack runs out without finding a left paren, 
					then there are mismatched parens and error will be thrown*/

					while(stackSize(&operators) > 0
						&& type_of_token((token)stackTop(&operators)) != lparen
						&& stackSize(&operators) > 1)
					{
						
						stack_push_assess(output, stackPop(&operators));
						stackPush(&intermediate, stackTop(output));
					}
					if(stackSize(&operators) > 0
						&& type_of_token((token)stackTop(&operators)) != lparen)
					{
						err = true;
						throw_err(parenMismatch);
					}
					
					stackPop(&operators); 
					while (stackSize(&operators) > 0 && type_of_token((token)stackTop(&operators)) == function)
					{
						stack_push_assess(output, stackPop(&operators));
						stackPush(&intermediate, stackTop(output));
					}
				}
				break;
			default:
				break;
		}
	}
	
	/*When there are no more tokens to read, while there are still operator tokens on the stack, if the operator token on the top of the stack is a paren, 
	then there are mismatched parens which gives error and pop the operator onto the output queue*/
	
	while(stackSize(&operators) > 0)
	{
		if(type_of_token((token)stackTop(&operators)) == lparen)
		{
			throw_err(parenMismatch);
			err = true;
		}
		
		stack_push_assess(output, stackPop(&operators));
		stackPush(&intermediate, stackTop(output));
	}
	/*popping result from intermediate stack*/
	stackPop(&intermediate);
	/*free remaining intermediate results*/
	
	while (stackSize(&intermediate) > 0)
	{
		token s = stackPop(&intermediate);
		free(s);
	}
	if (err == true)
	{
		while (stackSize(&operators) > 0)
		{
			token s = stackPop(&operators);
			free(s);
		}
	}
	stackFree(&intermediate);
	stackFree(&operators);
	return err;

}


int main(int argc, char *argv[])
{    
        FILE *fp, *fpoutput;
	char fname[30];
        char an[100] = "Answers: ";
        printf("\n**************************************************************************************************************************************************************************************************************\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\tSCIENTIFIC CALCULATOR");
        printf("\n**************************************************************************************************************************************************************************************************************\n");

	printf("\n\n\n\t\t\t\t\t\t\t\t\t\t  <<- OPERATIONS THAT CAN BE PERFORMED ->>");
        printf("\n\t\t\t\t\t\t\t  ------------------------------------------------------------------------------------------- ");
        printf("\n\t\t\t\t\t\t\t | 1.Addition +               | 2.Subtraction -             | 3.Multiplication *             |");
        printf("\n\t\t\t\t\t\t\t | 4.Division /               | 5.Modulus                   | 6.Exponent ^                   |");
        printf("\n\t\t\t\t\t\t\t | 7.Absolute Value- abs()    | 8.sine sin()                | 9.cosin cos()                  |");
        printf("\n\t\t\t\t\t\t\t | 10.tangent tan()           | 11.Logorithm log()          | 12.Average avg()               |");
        printf("\n\t\t\t\t\t\t\t | 13.Mean mean()             | 14.Median median()          | 15.Variance var()              |");
        printf("\n\t\t\t\t\t\t\t | 16.Squart Root sqrt()      | 17.Cube Root cbrt()         | 18.e^x                         |");
        printf("\n\t\t\t\t\t\t\t | 19.Minimum Value min()     | 20.Maximum value max()      | 21. Floor floor()              |");
        printf("\n\t\t\t\t\t\t\t | 22.Ceil ceil()             | 23.Arcsine asin()or arcsin()| 24. Arccos acos() or acrccos() |");
        printf("\n\t\t\t\t\t\t\t | 25.Arctan atan()or arctan()| 26.Summation sum()          | 27. quit                       |");
        printf("\n\t\t\t\t\t\t\t  --------------------------------------------------------------------------------------------");

	printf("\nExample filename:\"abc.txt\" \n");
	printf("\nEnter the filename:");
        scanf("%s",fname);
        char* filename = fname;
	char* str = NULL;	
	char* output = malloc(128);

	token* tokens = NULL;
	int numTokens = 0;
	Stack expr;
	int i;
	int ch, rflag = 0;
	prefs.precision = DEFAULTPRECISION;
	prefs.maxtokenlength = MAXTOKENLENGTH;


        while ((ch = getopt(argc, argv, "rm:")) != -1) 
         {
          switch (ch) 
                   {
                case 'r':
                    rflag = 1;
                    break;
                case 'm':
                    prefs.maxtokenlength = atoi(optarg);
                    }
          }

        
        		
	fp = fopen(filename, "r");
        fpoutput = fopen(filename, "a");
        fprintf(fpoutput," \n \n %s",an);
        fclose(fpoutput);
		
		    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
	
	str = get_data_file(fp);
	//str = get_data_console(stdin); /* Release 1 code */
	printf("%s",str);
        while(str != NULL && strcmp(str, "quit") != 0)
	{
		if (strlen(str) == 0){
			goto get_new_string;
		}
		
			numTokens = convert_to_tokens(str, &tokens);
			free(str);
			str = NULL;
            
            /*Convert to postfix*/

			stackInit(&expr, numTokens);
			
			postfix(tokens, numTokens, &expr);
			
			if(stackSize(&expr) != 1)
			{
				printf("\tError evaluating expression\n");
			}
                          
                         else
			{
			if (!rflag)
			printf("\t= ");

			
                        output = (char*)stackTop(&expr);
                        fpoutput = fopen(filename, "a");
                        fprintf(fpoutput," \n %s",output);
                        fclose(fpoutput);
                        printf("%s\n", (char*)stackTop(&expr));

			for (i=0; i< numTokens; i++)
			{
			if (tokens[i] == stackTop(&expr))
			tokens[i] = NULL;
			}
			free(stackPop(&expr));
			}

			for(i = 0; i < numTokens; i++)
			{
			if (tokens[i] != NULL)
			free(tokens[i]);
			}
			free(tokens);
			tokens = NULL;
			numTokens = 0;
			stackFree(&expr);	
			
	get_new_string:
		
		str = get_data_file(fp);
		//str = get_data_console(stdin); /*release 1 code*/
     int index, i;

    /* Set default index */
    index = -1;

    /* Find last index of non-white space character */
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }

        i++;
    }

    /* Mark next character to last non-white space character as NULL */
       str[index + 1] = '\0';
       sleep(1);
       printf("%s",str);
		
	}
	free(str);
	str = NULL;
        printf("\n\n***\tOpen your file:\"%s\" for answers\t***\n\n",fname);
	return EXIT_SUCCESS;
}