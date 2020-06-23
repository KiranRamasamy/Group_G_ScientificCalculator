/*
 * @file typeoftoken_test.h
 *
 * @brief Collections of declaration function of automated unit tests for type_of_token function
 *
 * @author Kiran Ramasamy - kiranramasamy@cmail.carleton.ca
 */

#ifndef TEST_K
#define TEST_K

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define bool char
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

Symbol find_type(char ch); 


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

bool if_is_func(token tk);

/**
* @brief The function decides whether the token is a special value 
* @details The function returns 0 if the token is:
* -nan
* -inf
*/

bool if_is_specialval(token tk);

/**
 * @brief Automated unit testing for type of token functions
 *
 * @details Automatically tests the all the general categories in the function
 * 
 */

Symbol testing_type_of_token(token tk);



#endif
