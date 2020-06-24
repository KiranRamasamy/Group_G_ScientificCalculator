/**
 * @file typeoftoken_test.c
 *
 * @brief This is the test cases for type_of_token function 
 * 
 * @author Kiran Ramasamy- kiranramasamy@cmail.carleton.ca
 **/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"./include/typeoftoken_test.h"

/**
* @brief The function decides the type token
* @details The function returns the following types: 
* -addop
* -multop
* -expop 
* -lparen
* -rparen
* -decimal
* -space
* -argsep
* -digit
* -text
* -invalid
*/


Symbol find_type(char ch)
{
	Symbol result;
	switch(ch)
	{
		case '+':
		case '-':
			result = addop;
                        printf("in multop:%s",result);

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
        printf("\nResult of find_type function:%d",result);
	return result;
}

/**
* @brief The function decides whether the token is a function 
* @details The function returns 0 if itb encounters the following types: 
* -abs
* -floor
* -ceil 
* -sin
* -cos
* -tan
* -arcsin
* -arccos
* -arctan
* -asin
* -acos
* -atan
* -sqrt
* -cbrt
* -log
* -min
* -max
* -sum
* -avg
* -mean
* -median
* -var
* -exp
*/

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


/**
* @brief The function decides whether the token is a special value 
* @details The function returns 0 if the token is:
* -nan
* -inf
*/

bool if_is_specialval(token tk)
{
	return (strncmp(tk, "nan", 3) == 0 || strncmp(tk, "inf", 3) == 0);
} 
      

/**
 * @brief Automated unit testing for type of token functions
 *
 * @details Automatically tests the all the general categories in the function
 * 
 */
        
Symbol testing_type_of_token(token tk)
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
				ret = testing_type_of_token(tk+1);
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
 
/*main function has test cases same as described in the assignment*/

int main()
{
        Symbol res1,res2,res3,res4,res5,res6,res7,res8,res9,res10,res11,res12;
        token tk1="$";
        token tk2="log(20)";
        token tk3="nan";
        token tk4="6";
        token tk5="A";
        token tk6="+";
        token tk7="*";
        token tk8="^";
        token tk9=" ";
	token tk10=",";
	token tk11="(";
	token tk12=")";
        res1=testing_type_of_token(tk1);
        res2=testing_type_of_token(tk2);
        res3=testing_type_of_token(tk3);
        res4=testing_type_of_token(tk4);
        res5=testing_type_of_token(tk5);
        res6=testing_type_of_token(tk6);
        res7=testing_type_of_token(tk7);
        res8=testing_type_of_token(tk8);
        res9=testing_type_of_token(tk9);
        res10=testing_type_of_token(tk10);
        res11=testing_type_of_token(tk11);
        res12=testing_type_of_token(tk12);
        printf("\n\nTokens given:");
        printf("\n\n Token 1: $\n Token 2:log(20)\n Token 3:nan\n Token 4: 6\n Token 5: A\n Token 6: +\n Token 7: *\n Token 8: ^\n Token 9: " "(space)\n Token 10: ,\n Token 11: ( \n Token 12: )");
        
        printf("\n\nNumbers assigned for the token types:");
        printf("\n\n 0-addop\n 1-multop\n 2-expop\n 3-lparen\n 4-rparen\n 5-digit\n 6-value\n 7-decimal\n 8-space\n 9-text\n 10-function\n 11-identifier\n 12-argsep\n 13-invalid");
        
        printf("\n\nResults:");        
        printf("\n\n type_of_token 1:%d",res1);
	printf("\n type_of_token 2:%d",res2);
	printf("\n type_of_token 3:%d",res3);
        printf("\n type_of_token 4:%d",res4);
	printf("\n type_of_token 5:%d",res5);
	printf("\n type_of_token 6:%d",res6);
        printf("\n type_of_token 7:%d",res7);
	printf("\n type_of_token 8:%d",res8);
	printf("\n type_of_token 9:%d",res9);
        printf("\n type_of_token 10:%d",res10);
	printf("\n type_of_token 11:%d",res11);
	printf("\n type_of_token 12:%d",res12);
	getchar();

    return 1;
	
}



