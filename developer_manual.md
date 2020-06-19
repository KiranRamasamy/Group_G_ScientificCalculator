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

