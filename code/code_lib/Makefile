###
### First part of a Makefile:
### Define required variables
###

### Variables used by implicit rules:
### https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html

# C compiler to use
CC=gcc
# Compiler flags
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -g
# Linker library location flags (e.g. -L)
LDFLAGS=`pkg-config --libs-only-L allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_acodec-5.0`

# Linker library flags (e.g. -l)
LDLIBS=`pkg-config --libs-only-l allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_acodec-5.0`

### Regular variables

# Name of program
PROGRAM=jogo

###
### Second part of a Makefile:
### Rules to build our example
###

# Rule to generate executable program - by default first target in the makefile
# is generated when "make" is executed. Because no explicit recipe is given,
# the "make" program will use the implicit rule for linking all object files
# into an executable program.
$(PROGRAM): $(PROGRAM).o showworld_simple.o shuffle.o coordinates.o\
 movement.o

# Rule to generate program object. Again, because no explicit recipe is given,
# "make" will use an implicit rule for properly compiling $(PROGRAM).o.
$(PROGRAM).o: $(PROGRAM).c showworld.h jogo.h

# Rule to generate showworld_simple.o object. Again, because no explicit recipe
# is given, "make" will use an implicit rule for properly compiling
# showworld_simple.o.
showworld_simple.o: showworld_simple.c showworld.h
shuffle.o: shuffle.c shuffle.h
coordinates.o: coordinates.c coordinates.h
movement.o: movement.c movement.h

# The following rule cleans all compiled (objects) and linked (executable
# program) files. Because "clean" is not actually the name of a file, it is
# good practice to specify it as a "phony" target (avoiding conflict with a
# file of the same name and improving performance). In this case, an explicit
# recipe is given, so make will not try to determine an implicit one.
.PHONY: clean
clean:
	rm -f $(PROGRAM) *.o
