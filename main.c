#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 
#include <getopt.h>
#include "stack.h"

#define bool char
#define true 1
#define false 0
#define MAXPRECISION 20
#define MAXTOKENLENGTH 512
#define DEFAULTPRECISION 5
#define FUNCTIONSEPARATOR "|"

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


char* getDataConsole(FILE* stream)
{
	unsigned int maxlen = 128, size = 128;
	char* bufferMemory = (char*)malloc(maxlen);

	if(bufferMemory != NULL) /* NULL if malloc() fails */
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
}

number constructNum(token str)
{
	number result = 0;
	result = strtod(str, NULL); //strtod for string to float (double)
	return result;
}


void stackPushAssess(Stack *s, token val)
{
	if(prefs.display.postfix)
		printf("\t%s\n", val);

	switch(typeOfToken(val))
	{
		case function:
			{
				if (performFuncs(s, val) < 0)
					return;
			}
			break;
		case expop:
		case multop:
		case addop:
			{
				if(stackSize(s) >= 2)
				{				
					if (performOps(s, val) < 0)
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


Symbol findType(char ch)
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

token numbertoString(number num)
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

bool ifIsFunc(token tk)
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

bool ifIsSpecialVal(token tk)
{
	return (strncmp(tk, "nan", 3) == 0 || strncmp(tk, "inf", 3) == 0);
}

int performFuncs(Stack *s, token function)
{
if (stackSize(s) == 0)
	{
		//throwErr here with missing input
		stackPush(s, numbertoString(NAN));
		return -1;
	}
	else if (stackSize(s) == 1 && strcmp(stackTop(s), FUNCTIONSEPARATOR) == 0)
	{
		stackPop(s);
		//throwErr here with missing input
		stackPush(s, numbertoString(NAN));
		return -1;
	}
	
	token input = (token)stackPop(s);
	number num = constructNum(input);
	number result = num;
	number counter = 0;

	if(strncmp(function, "abs", 3) == 0)
		result = fabs(num);
	else if(strncmp(function, "floor", 5) == 0)
		result = floor(num);
	else if(strncmp(function, "ceil", 4) == 0)
		result = ceil(num);
	else if(strncmp(function, "sin", 3) == 0)
		result = !prefs.mode.degrees ? sin(num) : sin(convertToRad(num));
	else if(strncmp(function, "cos", 3) == 0)
		result = !prefs.mode.degrees ? cos(num) : cos(convertToRad(num));
	else if(strncmp(function, "tan", 3) == 0)
		result = !prefs.mode.degrees ? tan(num) : tan(convertToRad(num));
	else if(strncmp(function, "arcsin", 6) == 0
		 || strncmp(function, "asin", 4) == 0)
		result = !prefs.mode.degrees ? asin(num) : convertToDeg(asin(num));
	else if(strncmp(function, "arccos", 6) == 0
		 || strncmp(function, "acos", 4) == 0)
		result = !prefs.mode.degrees ? acos(num) : convertToDeg(acos(num));
	else if(strncmp(function, "arctan", 6) == 0
		 || strncmp(function, "atan", 4) == 0)
		result = !prefs.mode.degrees ? atan(num) : convertToDeg(atan(num));
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
			num = constructNum(input);
			if (num < result)
				result = num;
		}
	}
	else if(strncmp(function, "max", 3) == 0)
	{
		while (stackSize(s) > 0 && strcmp(stackTop(s), FUNCTIONSEPARATOR) != 0)
		{
			input = (token)stackPop(s);
			num = constructNum(input);
			if (num > result)
				result = num;
		}
	}
	else if(strncmp(function, "sum", 3) == 0)
	{
		while (stackSize(s) > 0  && strcmp(stackTop(s), FUNCTIONSEPARATOR) != 0)
		{
			input = (token)stackPop(s);
			num = constructNum(input);
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
			num = constructNum(input);
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
			num = constructNum(input);
			while (stackSize(&tmp) > 0 && constructNum(stackTop(&tmp)) < num)
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
		result = constructNum(stackPop(&tmp));
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
			num = constructNum(input);
			mean += num;
			counter++;
		}
		mean /= counter;
		result = 0;
		while (stackSize(&tmp) > 0)
		{
			input = (token)stackPop(&tmp);
			num = constructNum(input)-mean;
			result += pow(num,2);
		}
		result /= counter;
		stackFree(&tmp);
	}
	if (strcmp(stackTop(s), FUNCTIONSEPARATOR) == 0)
		stackPop(s);
	stackPush(s, numbertoString(result));
	return 0;
}	
}
Symbol typeOfToken(token tk)
{
	if (!tk)
         {
		return invalid;
         }
	Symbol ret = findType(*tk);
	switch(ret)
	{
		case text:
			if(ifIsFunc(tk))
                         {
				ret = function;
                         }
			else if(ifIsSpecialVal(tk))
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
				ret = typeOfToken(tk+1);
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

int convertToTokens(char *str, char *(**tokensRef))
{
	int i = 0;
	char** tokens = NULL;
        char ** temp = NULL;
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
		if(findType(ch) == invalid) /* Stop tokenizing when we encounter an invalid character */
			break;

		token newToken = NULL;
		tmpToken[0] = '\0';
		switch(findType(ch))
		{
			case addop:
                               {
                                      /* Check if this is a negative */
					if(ch == '-'
						&& (numTokens == 0
							|| (typeOfToken(tokens[numTokens-1]) == addop
								|| typeOfToken(tokens[numTokens-1]) == multop
								|| typeOfToken(tokens[numTokens-1]) == expop
								|| typeOfToken(tokens[numTokens-1]) == lparen
								|| typeOfToken(tokens[numTokens-1]) == argsep)))
					{
                                                /* Assemble an n-character (plus null-terminator) number token */
						{
							int len = 1;
							bool hasDecimal = false;
							bool hasExponent = false;

							if(findType(ch) == decimal) /* Allow numbers to start with decimal */
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
								&& (findType(*ptr) == digit /* The next character is a digit */
								 	|| ((findType(*ptr) == decimal /* Or the next character is a decimal */
								 		&& hasDecimal == 0)) /* But we have not added a decimal */
								 	|| ((*ptr == 'E' || *ptr == 'e') /* Or the next character is an exponent 
								 		&& hasExponent == false) /* But we have not added an exponent yet */
								|| ((*ptr == '+' || *ptr == '-') && hasExponent == true)); /* Exponent with sign */
								++len)
							{
								if(findType(*ptr) == decimal)
									hasDecimal = true;
								else if(*ptr == 'E' || *ptr == 'e')
									hasExponent = true;
								tmpToken[len] = *ptr++;
							}


							tmpToken[len] = '\0';
						}
						break;
					}
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

					if(findType(ch) == decimal) /* Allow numbers to start with decimal */
					{
						//printf("Decimal\n");
						hasDecimal = true;
						len++;
						tmpToken[0] = '0';
						tmpToken[1] = '.';
					}
					else /* Numbers that do not start with decimal */
					{
						tmpToken[len-1] = ch;
					}

					// Assemble rest of number
					for(; // Don't change len
						*ptr /* There is a next character and it is not null */
						&& len <= prefs.maxtokenlength
						&& (findType(*ptr) == digit /* The next character is a digit */
						 	|| ((findType(*ptr) == decimal /* Or the next character is a decimal */
						 		&& hasDecimal == 0)) /* But we have not added a decimal */
						 	|| ((*ptr == 'E' || *ptr == 'e') /* Or the next character is an exponent */
						 		&& hasExponent == false) /* But we have not added an exponent yet */
						 	|| ((*ptr == '+' || *ptr == '-') && hasExponent == true)); /* Exponent with sign */
						++len)
					{
						if(findType(*ptr) == decimal)
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
					for(len = 1; *ptr && findType(*ptr) == text && len <= prefs.maxtokenlength; ++len)
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


int decidePrecedence(token op1, token op2)
{
	int ret = 0;

	if (op2 == NULL)
        {
		ret = 1;
	}
	else if(typeOfToken(op1) == typeOfToken(op2)) 
	{
		ret = 0;
	 }  
	else if(typeOfToken(op1) == addop
			&& (typeOfToken(op2) == multop || typeOfToken(op2) == expop)) 
	{
		ret = -1;
	}
	else if(typeOfToken(op2) == addop
			&& (typeOfToken(op1) == multop || typeOfToken(op1) == expop)) 
	{
		ret = 1;
	}
	else if(typeOfToken(op1) == multop
			&& typeOfToken(op2) == expop) 
	{
		ret = -1;
	}
	else if(typeOfToken(op1) == expop
			&& typeOfToken(op2) == multop) 
	{
		ret = 1;
	}
	else if (typeOfToken(op1) == function
			&& (typeOfToken(op2) == addop || typeOfToken(op2) == multop || typeOfToken(op2) == expop || typeOfToken(op2) == lparen))
	{
		ret = 1;
	}
	else if ((typeOfToken(op1) == addop || typeOfToken(op1) == multop || typeOfToken(op1) == expop)
			&& typeOfToken(op2) == function)
	{
		ret = -1;
	}
	return ret;
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
		switch(typeOfToken(tokens[i]))
		{
			case value:
				{
					stackPushAssess(output, tokens[i]); //adding to stack if token is number
				}
				break;
			case function:
				{
					while(stackSize(&operators) > 0
						&& (typeOfToken(tokens[i]) != lparen)
						&& ((decidePrecedence(tokens[i], (char*)stackTop(&operators)) <= 0)))
					{
						stackPushAssess(output, stackPop(&operators));
						stackPush(&intermediate, stackTop(output));
					}

					stackPush(&operators, tokens[i]);//token is function token
				}
				break;
				case argsep:
				{
					while(stackSize(&operators) > 0
						&& typeOfToken((token)stackTop(&operators)) != lparen
						&& stackSize(&operators) > 1)
					{
						
						stackPushAssess(output, stackPop(&operators));//popping all operators onto output queue till top is left paren
						stackPush(&intermediate, stackTop(output));
					}
					
				}
				break;
			case addop:
			case multop:
			case expop:
				{
	
					while(stackSize(&operators) > 0
						&& (typeOfToken((char*)stackTop(&operators)) == addop || typeOfToken((char*)stackTop(&operators)) == multop || typeOfToken((char*)stackTop(&operators)) == expop)
						&& ((leftAssociative(tokens[i]) && decidePrecedence(tokens[i], (char*)stackTop(&operators)) <= 0)
							|| (!leftAssociative(tokens[i]) && decidePrecedence(tokens[i], (char*)stackTop(&operators)) < 0)))
					{
						
						stackPushAssess(output, stackPop(&operators));
						stackPush(&intermediate, stackTop(output));
					}
					
					stackPush(&operators, tokens[i]);
				}
				break;
			case lparen:
				{

					if (typeOfToken(stackTop(&operators)) == function)
						stackPush(output, FUNCTIONSEPARATOR);
					stackPush(&operators, tokens[i]);
				}
				break;
			case rparen:
				{
					
					while(stackSize(&operators) > 0
						&& typeOfToken((token)stackTop(&operators)) != lparen
						&& stackSize(&operators) > 1)
					{
						
						stackPushAssess(output, stackPop(&operators));
						stackPush(&intermediate, stackTop(output));
					}
					if(stackSize(&operators) > 0
						&& typeOfToken((token)stackTop(&operators)) != lparen)
					{
						err = true;
						throwErr(parenMismatch);
					}
					
					stackPop(&operators); 
					while (stackSize(&operators) > 0 && typeOfToken((token)stackTop(&operators)) == function)
					{
						stackPushAssess(output, stackPop(&operators));
						stackPush(&intermediate, stackTop(output));
					}
				}
				break;
			default:
				break;
		}
	}
	while(stackSize(&operators) > 0)
	{
		if(typeOfToken((token)stackTop(&operators)) == lparen)
		{
			throwErr(parenMismatch);
			err = true;
		}
		
		stackPushAssess(output, stackPop(&operators));
		stackPush(&intermediate, stackTop(output));
	}
	stackPop(&intermediate);
	// free remaining intermediate results
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

bool leftAssociative(token op)
{
	bool ret = false;
	switch(typeOfToken(op))
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

int main(int argc, char *argv[])
{    
    
	char* str = NULL;	
	char* prev_output = malloc(128);

	token* tokens = NULL;
	int numTokens = 0;
	Stack expr;
	int i;
	int ch, rflag = 0;
	prefs.precision = DEFAULTPRECISION;
	prefs.maxtokenlength = MAXTOKENLENGTH;
	
	str = getDataConsole(stdin);
	printf("%s",str);
        while(str != NULL && strcmp(str, "quit") != 0)
	{
		if (strlen(str) == 0)
			goto get_new_string;
		
		
			numTokens = convertToTokens(str, &tokens);
			free(str);
			str = NULL;	
			
	get_new_string:
		
		str = getDataConsole(stdin);
		printf("%s",str);
		
	}



	free(str);
	str = NULL;
	return EXIT_SUCCESS;
}