/**
 * @file stack.h
 *
 * @brief This is the main file from where all the funtions will be handled by the system.
 * 
 * @author Indu Guduru - induguduru@cmail.carleton.ca
 * @author Kiran Ramasamy- kiranramasamy@cmail.carleton.ca
 * @author Tejaswini Tummala- tejaswinitummala@cmail.carleton.ca
 * @author Vinoth Kumar Baskaran -vinothkumarbaskaran@cmail.carleton.ca
 * */
 
#ifndef STACK_H
#define STACK_H

#include<stdio.h>

typedef struct
{
	void **content;
	int size;
	int top;
} Stack;

/**
 * @brief This function is used initialize the stack.
 * 
 * @details  This function initializes the stack and sets the stackpointer to -1.
 * 
 * @return There is no return value for this function.
 *
 */ 

void stackInit(Stack *s, int size);

/**
 * @brief This function is used to push the tokens to the stack.
 * 
 * @details used to push tokens to the stack.
 * 
 * 
 * @return There is no return value for this function.
 *
 */ 

void stackPush(Stack *s, void* val);

/**
 * @brief This function is used to remove elements and tokens from stack.
 * 
 * @details This  function  removes elements and tokens from stack.
 * 
 * @return There is no return value for this function.
 *
 */ 

void* stackPop(Stack *s);

 /**
 * @brief This function is used to fetch the top most element from the stack.
 * 
 * @details this function takes the top most element of stack.
 * 
 * @return There is no return value for this function.
 *
 */ 

void* stackTop(Stack *s);
/**
 * @brief This function is used to know the size of stack.
 * 
 * @details This function is used to know the size of stack at any point.
 * 
 * @return The return value for this function is integer
 *
 */ 

int stackSize(Stack *s);

/**
 * @brief This function is used to clear the stack memory from system
 * 
 * @details This function is used to clear the stack memory from system
 * 
 * @return There is no return value for this function. 
 *
 */ 

void stackFree(Stack *s);

#endif