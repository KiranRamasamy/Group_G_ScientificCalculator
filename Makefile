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

stack_test: $(OBJDIR)/stack.o $(SRCTESTDIR)/stack_test.c
	$(CC) $(LFLAGS) -o $(BINDIR)/stack_test $(SRCTESTDIR)/stack_test.c $(SRCDIR)/stack.c $(LIBS)

$(OBJDIR)/stack.o: $(SRCDIR)/stack.c $(INCDIR)/stack.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(SRCDIR)/stack.c $(LIBS)

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/calculator $(BINDIR)/stack_test

.PHONY: $(BINDIR)/calculator
