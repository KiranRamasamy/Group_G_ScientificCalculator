# Introduction

The purpose of this calculator is to evaluate all lines of expressions from an input file that involves arithmetic operations and scientific functions and will return the output in the same file. Since the calculator evaluates all the expressions present in the file in a single execution, user saves lot of time. This calculator comes up with a different way of taking inputs and providing outputs to the user. 

# Installation


# Usage

The user gives expressions as inputs using “Files”. The expression in the file can be entered in the standard infix syntax, with the parantheses denoting non-standard order of operations. The file given by the user is read, analyzed, evaluated and the results are given back in the same file. User needs the calculator to perform below operations and functions.

The different operations are as follows:


 
Addition

Subtraction

Multiplication

Division

Modulus

Exponent


The functions are as follows:

Absolute Value

Sine

Cosine

Tangent

Logarithm

Exponent

Average

Mean

Median

Variance

Square root

Cube root

Minimum value

Maximum value

Floor

Ceiling

Arcsine

Arccosine

Arctangent

Summation

# How to write the input file

The input file should be saved in.txt format.

The input file should contain minimum of two operands and one operator to evaluate the expression. 

Every single expression should be written in a single line

The input expression should have the functions mentioned in the “operations and functions”. It should not contain the special characters such as @, # , $, !, ~, &

The input file should have the “quit” statement at the end of the file if not the program will enter the infinite loop.

The input file should be placed in the same folder where the source code is located.

Sample input file:

Ex : input.txt

2+3

3*log(10)+(sin(45)*tan(45))

(900/20)^3

Quit


# Error codes:

divZero – if the denominator is zero while performing ‘ / ’ or ‘ % ’ function (DivideByZero Error)

parenMismatch-  if the right parenthesis in not available in the stack

inputMissing – if a input is missing while performing the operation


# Cases where the program will not work properly

If the file name is saved in any other format other than .txt format.

If the input file name given in the program doesn’t exist

If the expressions in the input file contains special characters like @, # , $, !, ~, &

If the input file is kept in the different folder rather than the folder that contains the source code.

If the EOF statement is not “Quit”.

