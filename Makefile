# Thanks to https://www.youtube.com/watch?v=DtGrdB8wQ_8 for instructions.
# Also https://www.youtube.com/watch?v=20GC9mYoFGs explains Auto Variables.

# My Github : https://github.com/jims-git/cpp

# STEP 1: Name of application
BINARY=myApp

# STEP 2: for c files use gcc, for c++ use g++
CC=g++

# Nothing to modify below this line
# ---------------------------------

# Use c or cpp file extentions
ifeq ($(CC), gcc)
 $(info Makefile for C program)
 EXTEN=c
 STD=
else
 $(info Makefile for C++ program)
 EXTEN=cpp
 STD=-std=c++20
endif

# Look in these directories for src files
CODEDIRS=. lib

# Look in these directories for .h files
INCDIRS=. ./include/ # can be list

OPT=-O0

# generate files that encode make rules for the .h dependencies
DEPFLAGS=-MP -MD

# automatically add the -I onto each include directory
CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(STD) $(OPT) $(DEPFLAGS)

# for-style iteration (foreach) and regular expression completions (wildcard)
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.$(EXTEN)))

# regular expression replacement
OBJECTS=$(patsubst %.$(EXTEN),%.o,$(CFILES))
DEPFILES=$(patsubst %.$(EXTEN),%.d,$(CFILES))

all: $(BINARY)

# Automatic Variables
# -------------------																																
# $@ = Target Name (LEFT side of the :)
#
# ie:
#	mymain:main.o lib.o
#		g++ -o mymain main.o lib.o
#			can be written as
#		g++ -o $@ main.o lib.o


# Automatic Variables
# -------------------																																
# $^ = The name of the all prerequisites (RIGHT side of the :)
#
# ie:
#	mymain:main.o lib.o
#		g++ -o mymain main.o lib.o
#			can be written as
#		g++ -o $@ $^
$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^


# only want the .c file dependency here, thus $< instead of $^.
#
# Automatic Variables
# -------------------																																
# $< = The name of the FIRST prerequisite (RIGHT side of the :)
#
# ie:
#	mymain:main.o lib.o
#		g++ -o mymain main.o lib.o
#			can be written as
#		g++ -o $@ $< lib.o
%.o:%.$(EXTEN)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) dist.tgz

# shell commands are a set of keystrokes away
distribute: clean
	tar zcvf dist.tgz *

# @ silences the printing of the command
# $(info ...) prints output
diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

# include the dependencies
-include $(DEPFILES)

# add .PHONY so that the non-targetfile - rules work even if a file with the same name exists.
.PHONY: all clean distribute diff

# RECAP
# Automatic Variables
# -------------------
# 
# $@ = Target Name (LEFT side of the :)
# $< = The name of the FIRST prerequisite (RIGHT side of the :)
# $^ = The name of the all prerequisites (RIGHT side of the :)																														
# % = use the TARGET name (TARGET=main so main.o:main.c is %.o:%.c)
#
# ie:
#	.PHONY: all clean
#	all: main

#	main: main.o lib.o
#		gcc -o $@ $^
#
# Compile all of the .o files from the .c files
#	%.o:%.c
#		gcc -c $< -o $@
#
#	clean:
#		rm -f *.o main

