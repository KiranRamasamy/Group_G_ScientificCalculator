
#  @file make file
 
#   @brief make file is used to compile and link multiple source files.
#   @author Indu Guduru - induguduru@cmail.carleton.ca
#   @author Kiran Ramasamy- kiranramasamy@cmail.carleton.ca
#   @author Tejaswini Tummala- tejaswinitummala@cmail.carleton.ca
#   @author Vinoth Kumar Baskaran -vinothkumarbaskaran@cmail.carleton.ca
 
 # change these to proper directories where each file should be
SRCDIR       = src
SRCTESTDIR   = test
OBJDIR       = obj
BINDIR       = bin
INCDIR       = include
INCDIRTEST	 = test/include




CC = gcc
CFLAGS = -c -Wall
LFLAGS = -Wall
LIBS = -lm

$(BINDIR)/calculator: $(OBJDIR)/stack.o $(SRCDIR)/main.c
	@mkdir -p $(BINDIR)
	$(CC) $(LFLAGS) -o $(BINDIR)/calculator $(SRCDIR)/main.c $(SRCDIR)/stack.c $(LIBS)

stack_test: $(OBJDIR)/stack.o $(SRCTESTDIR)/stack_testing.c
	$(CC) $(LFLAGS) -o $(BINDIR)/stack_testing $(SRCTESTDIR)/stack_testing.c $(SRCDIR)/stack.c $(LIBS)

$(OBJDIR)/stack.o: $(SRCDIR)/stack.c $(INCDIR)/stack.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(SRCDIR)/stack.c $(LIBS)

postfix_test: 
	$(CC) $(LFLAGS) -o $(BINDIR)/postfix_test  $(SRCTESTDIR)/postfix_test.c  $(LIBS)

typeoftoken_test: 
	$(CC) $(LFLAGS) -o $(BINDIR)/typeoftoken_test  $(SRCTESTDIR)/typeoftoken_test.c  $(LIBS)	

performops_test: 
	$(CC) $(LFLAGS) -o $(BINDIR)/performops_test  $(SRCTESTDIR)/performops_test.c  $(LIBS)
	
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/calculator $(BINDIR)/stack_testing $(BINDIR)/postfix_test $(BINDIR)/typeoftoken_test $(BINDIR)/performops_test 

.PHONY: $(BINDIR)/calculator
