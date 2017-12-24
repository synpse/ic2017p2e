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

# Folder where I have source code
SRCDIR=src
# Folder where I'll put object files
OBJDIR=obj
# Folder where I'll put my executable program
BINDIR=bin

# Source files to compile
SOURCES=$(wildcard $(SRCDIR)/*.c)
# Object files derived from source files (replace .c with .o)
OBJECTS=$(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
# Name of program
PROGRAM=example

###
### Rules to build our example
###

# Rule to generate executable program - by default first target in the makefile
# is generated when "make" is executed
$(BINDIR)/$(PROGRAM): $(OBJECTS) $(BINDIR)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

# Rule to generate objects
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create binary directory if it does not exist
$(BINDIR):
	mkdir -p $(BINDIR)

# Rule to create object directory if it does not exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# This rule cleans all compiled (objects) and linked (executable program) files
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)
