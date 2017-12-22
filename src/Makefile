# C compiler to use
CC=gcc
# Compiler flags
CFLAGS=-c -Wall -Wextra -Wpedantic -std=c99 -g
# Linker flags (e.g. -L)
LDFLAGS=
# Linker library flags (e.g. -l)
LDLIBS=
# Source files to compile
SOURCES=example.c simple_showworld.c
# Object files derived from source files (replace .c with .o)
OBJECTS=$(SOURCES:%.c=%.o)
# Name of executable
EXECUTABLE=example

# This rule depends on all targets
all: $(EXECUTABLE)

# Rule to generate executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Rule to generate objects
$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# This rule cleans all compiled (objects) and linked (executable) files
clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
