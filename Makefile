
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

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/calculator $(BINDIR)/stack_testing

.PHONY: $(BINDIR)/calculator
