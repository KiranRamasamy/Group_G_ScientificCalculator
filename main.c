#include <stdio.h>
#include <string.h>

#define bool char
#define true 1
#define false 0
#define MAXPRECISION 20

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



int main()
{    
    

	char* str = NULL;
	
	str = getDataConsole(stdin);
	printf("%s",str);
        while(str != NULL && strcmp(str, "quit") != 0)
	{
		if (strlen(str) == 0)
		{
		str = getDataFile(fp);
		printf("%s",str);
		}
	}



	free(str);
	str = NULL;
	return EXIT_SUCCESS;
}