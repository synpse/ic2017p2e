###
### Implicit variables:
### https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html
###

# C compiler to use
CC=gcc
# Compiler flags
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -g
# Linker library location flags (e.g. -L)
LDFLAGS=
# Linker library flags (e.g. -l)
LDLIBS=

###
### Regular variables
###

# Name of program
PROGRAM=example

###
### Rules to build our example
###

# Rule to generate executable program - by default first target in the makefile
# is generated when "make" is executed
$(PROGRAM): $(PROGRAM).o simple_showworld.o

# Rule to generate program object
$(PROGRAM).o: $(PROGRAM).c $(PROGRAM).h simple_showworld.h showworld.h

# Rule to generate simple_showworld.o object
simple_showworld.o: simple_showworld.c simple_showworld.h

# This rule cleans all compiled (objects) and linked (executable program) files
clean:
	rm -f $(PROGRAM) *.o
