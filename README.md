# Scientific Calculator

The purpose of the calculator is to evaluate all lines of expressions from an input file that involves arithmetic operations and scientific functions and will return the output in the same file. Since the calculator evaluates all the expressions present in the file in a single execution, user saves lot of time. This calculator comes up with a different way of taking inputs and providing outputs to the user.


# Authors

- Indu Guduru - induguduru@cmail.carleton.ca - Carleton University
- Kiran Ramasamy - kiranramasamy@cmail.carleton.ca - Carleton University
- Tejaswini Tummala - tejaswinitummala@cmail.carleton.ca - Carleton University
- Vinoth Kumar Baskaran - vinothkumarbaskaran@cmail.carleton.ca - Carleton University

# Installation

Installation steps are mentioned in [install.md](https://github.com/tejaswinitummala/Group_G_ScientificCalculator/blob/master/install.md)

# Usage

To run, you must first install it. Then you can follow instructions mentioned in
[User_Manual.md](https://github.com/tejaswinitummala/Group_G_ScientificCalculator/blob/master/doc/user_manual.md).

# File Structure

The correct file structure (after installing GSL library should be follow and run the binary)

```
├── doc    	-> Usage file
           ├── Developer_Manual.md
           ├── User_Manual.md
├── install.md 	-> Installation Guide
├── install.sh 	-> Installation script
├── LICENSE 	-> License file
├── Makefile 	-> Makefile
├── README.md 	-> Readme file
├── bin 	           -> Binary directory
├── include 	-> Header files
          ├── stack.h
		  ├── main.h
├── ScientificCalculator_config.cfg -> Doxygen Configuration files
├── src 	-> Source files 
│       ├── main.c
│       ├── stack.c
└── test
          ├── include  -> Header files for unit test
                     ├── performops_test.h
                     ├── postfix_test.h
                     ├── typeoftoken_test.h
					  ├──test.h
					 
          ├── performops_test.c
          ├── postfix_test.c
          ├── stack_testing.c
          ├── typeoftoken_test.c
		  ├── test.c
                     
```

# For Developers

The developer manual is available [here](https://github.com/tejaswinitummala/Group_G_ScientificCalculator/blob/master/doc/developer_manual.md).

# License

This project is licensed under the GPL 3.0 License - see the [LICENSE.md](https://github.com/tejaswinitummala/Group_G_ScientificCalculator/blob/master/LICENSE) file for details

# Acknowledgements

Thank to Dr. Cristina Ruiz Martin for providing guidance on how to develop the software.