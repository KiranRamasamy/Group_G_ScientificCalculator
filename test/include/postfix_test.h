/*
 * @file postfix_test.h
 *
 * @brief 
 *
 * @author 
 */

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "../../include/stack.h"
#include "../../src/stack.c"
#define bool char
#define false 0
#define true 1
#define FUNCTIONSEPARATOR "|"

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

 typedef enum
{
	divZero,
	overflow,
	parenMismatch,
	inputMissing,
} Error;

#endif