# Introduction

This a scientific calculator written in C language which evaluates the expressions given in a file supporting standard mathematical operations and a set of functions. 
In our project we are developing a Scientific calculator which evaluate all lines of expressions from an input file that involves arithmetic operations and scientific functions and will return the output in the same file. Since the calculator evaluates all the expressions present in the file in a single execution, user saves lot of time. This calculator comes up with a different way of taking inputs and providing outputs to the user.

# Requirements

The client gives expressions as inputs using “Files”. The file given by the client is read, analyzed, evaluated and the results are given back in the same file. The client requirements are as follows:

1.The system should perform arithmetic operations such as Addition, Subtraction, Multiplication, Division, Modulus, Exponent.

2.The system should perform basic math function such as Absolute value, Square root, Cube root, Log value.

3.The system should perform trigonometric functions such as Sine, Cosine, Tangent , Arcsine, Arccos and Arctan.

4.The system should perform statistical function such as Average, Mean, Median, Variance, Minimum value, and maximum value.

5.The system should perform other function such as floor , ceil, e^x and summation.

6.The system should be able to read a complex expression which includes many operations and functions.

7.The system should follow the order of operations -BODMAS while evaluating the expression.

8.The system should be able to take a file as input.

9.The system should be able to read all the expressions given in the file ( given by the user as input).

10.The system should write the evaluated output to the same file which was given as input.

# How our software works

Computation of the expression begins with the tokenization of the input string, maintaining original infix order. They are then converted to postfix notation for evaluation using the shunting-yard algorithm. As operators are pushed onto the postfix stack, terms are evaluated.

# Shunting yard algorithm

The shunting-yard algorithm is a method for parsing mathematical expressions specified in infix notation by producing a postfix notation string. For the conversion there are two main components, the operator stack and the output queue. The operator stack acts as storage structure to hold the operators and they are not added to the output queue until both of its operands have appeared. The algorithm assigns to each operator its correct operands, taking into account the order of precedence.
During this process the program reads each symbol in order and does something based on that symbol i.e., All numbers are pushed to the output queue when they are read and at the end of reading the expression, it pops all operators off the operator stack and onto the output queue. The final number on the output queue is the result.

# Main Features of the software

Early evaluation

• There is no separate evaluation step. Elements are evaluated on the postfix stack as soon as all terms are available. Due to the nature of the shunting-yard algorithm, as soon as an operator is pushed, it can be evaluated.

• When our StackPushAssesss() function sees an operator, rather than pushing , it pops its operands, runs the computation, and pushes the result.

• This means that once the input expression has been converted to postfix notation, the only element on the postfix stack is the result of the calculation.

# Program Flow

![flow chart](https://user-images.githubusercontent.com/65427344/85090426-16eb4080-b1b3-11ea-8878-5fa4f53d2555.PNG)

1.	The above flowchart describes the complete flow of our program which supports standard mathematical operations and a set of functions. 

2.	The user enters the ‘n’ number of expressions in a file. The expressions to be evaluated can be entered in standard infix syntax, with parentheses denoting nonstandard order of operations. 

3.	The expressions are converted to tokens and are evaluated using the shunting yard algorithm. 

4.	If the incoming token is a digit, push it to the output queue. 

5.	If the incoming token is a left parenthesis, push it on the operator stack. 

6.	If the incoming token is a right parenthesis: discard the right parenthesis, pop the stack tokens until we find a left parenthesis. Pop the left parenthesis and discard it. 

7.	If the incoming token is an operator and the stack is empty or contains a left parenthesis on top, push the incoming operator onto the stack. 

8.	If the incoming token is an operator and has either higher precedence than the operator on the top of the stack, or has the same precedence as the operator on the top of the stack and is right associative then push it on the stack. 

9.	If the incoming token is an operator and has either lower precedence than the operator on the top of the stack, or has the same precedence as the operator on the top of the stack and is left associative then continue to pop the stack until this is not true. Then, push the incoming operator. 

10.	At the end of the expression, pop all operators on the stack and push it to the output queue (No parentheses should remain). 

11.	Finally, the evaluated result of each expression is written on the same file and given as output to the user.

