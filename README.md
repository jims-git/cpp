# Playground to learn Makefile
Just using this to learn the voodoo that is Makefile.

Thanks to https://www.youtube.com/watch?v=DtGrdB8wQ_8 for instructions.
Also https://www.youtube.com/watch?v=20GC9mYoFGs explains Auto Variables.

My Github : https://github.com/jims-git/cpp

This is my attempt to build a "one-size-fits-all" Makefile.

First step is to setup all the variables, the second step is to
create all the targets. 

By default MAKE will run the first TARGET it finds, therefore it is
standard practice to name the first TARGET "all".

TARGETS are defined as:
						targetName : dependency
						(tab)		commands

Once all of the dependencies are satisfied, then the commandsvwill be executed.

# STEP 1: Name of application
BINARY=myApp

# STEP 2: for c files use gcc, for c++ use g++
CC=g++

# Nothing to modify below this line
# ---------------------------------

If CC == gcc then this will be a C program, so set EXTEN=c to search for .c files.
else
this will be a C++ program, so set EXTEN=cpp to search for .cpp files, and
set the flag -std=c++20.

EXTEN == c or cpp file extensions

ifeq ($(CC), gcc)
 $(info Makefile to build C program $(BINARY).)
 EXTEN=c
 STD=
else
 $(info Makefile to build C++ program $(BINARY).)
 EXTEN=cpp
 STD=-std=c++20
endif

Project Structure
-----------------
 ├── include
 │   └── myfunctions.h
 ├── lib
 │   └── myfunctions.cpp
 ├── main.c
 ├── Makefile
 ├── myprogram.cpp
 └── README.md

# Look in these directories for .cpp files
CODEDIRS=. lib

# Look in these directories for .h files
INCDIRS=. ./include/ # can be list

# Not sure what this argument is used for.
OPT=-O0

# Magic argument to generate files that encode make rules for the .h dependencies.
# It will read the source files, looking for #include .h files, and if these
# files are changed, the source file will be recompiled.
DEPFLAGS=-MP -MD

# automatically add the -I onto each include directory
CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(STD) $(OPT) $(DEPFLAGS)

# for-style iteration (foreach) and regular expression completions (wildcard)
# For each D in $(CODEDIRS)
# find all the .cpp files (or if gcc then all the .c files)
#
# ie: CFILES=./myprogram.cpp ./lib/myfunctions.cpp
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.$(EXTEN)))

# Regular Expression replacement.
# This is a little difficult to read.
# To create a LIST of OBJECTS (.o), we are pattern substituting 
# any .cpp files in $(CFILES) into .o files.
# ie: OBJECTS=./myprogram.o ./lib/myfunctions.o
# To create a LIST of DEPFILES (.d), we are pattern substituting 
# any .cpp files in $(CFILES) into .d files.
# ie: DEPFILES=./myprogram.d ./lib/myfunctions.d
OBJECTS=$(patsubst %.$(EXTEN),%.o,$(CFILES))
DEPFILES=$(patsubst %.$(EXTEN),%.d,$(CFILES))

# Begin TARGETS
# -------------

# Default first target is called 'all'.
# It has a dependency target called $(BINARY) aka myApp
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

# Second TARGET is called $(BINARY) aka myApp and has a 
# dependency of all the .o files.
# for each item in OBJECTS, it will look for %.o TARGET and build the .o
# Once all the .o's are built, then it will compile the final binary.
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

# This is the third TARGET. It will build all the .o files from the .cpp
# % = use the TARGET name (TARGET=main so main.o:main.c is %.o:%.c)
%.o:%.$(EXTEN)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) dist.tgz

# shell commands are a set of keystrokes away.
# This target will first run make clean, and then tarball the directory.
distribute: clean
	tar zcvf dist.tgz *

# @ silences the printing of the command
# $(info <user_defined_message>) prints output
diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

# include the dependencies
-include $(DEPFILES)

# If there was a file called 'clean' and you tried to 'make clean'
# you would be told that 'clean' is up to date, so nothing to do.
# Add .PHONY so that the non-targetfile - rules work even if 
# a file with the same name exists.
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

