/*
 * @file postfix_test.h
 *
 * @brief Collections of different variables needed for automated unit tests for postfix function
 *
 * @author Tejaswini Tummala - tejaswinitummala@cmail.carleton.ca
 */

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "../../include/stack.h"
#include "../../src/stack.c"

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

#endif
