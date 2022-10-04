# Thanks to https://www.youtube.com/watch?v=DtGrdB8wQ_8 for instructions.
# Also https://www.youtube.com/watch?v=20GC9mYoFGs explains Auto Variables.
# My Github : https://github.com/jims-git/cpp

BINARY=myApp
CC=g++

ifeq ($(CC), gcc)
 $(info Makefile to build C program $(BINARY).)
 EXTEN=c
 STD=
else
 $(info Makefile to build C++ program $(BINARY).)
 EXTEN=cpp
 STD=-std=c++20
endif

# Look in these directories for .cpp files
CODEDIRS=. lib

# Look in these directories for .h files
INCDIRS=. ./include/ # can be list

# Optimization
OPT=-O0

# Magic argument to generate files that encode make rules for the .h dependencies.
# It will read the source files, looking for #include .h files, and if these
# files are changed, the source file will be recompiled.
DEPFLAGS=-MP -MD

# automatically add the -I onto each include directory
CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(STD) $(OPT) $(DEPFLAGS)


# find all the .cpp files (or if gcc then all the .c files)
# ie: CFILES=./myprogram.cpp ./lib/myfunctions.cpp
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.$(EXTEN)))

# Regular Expression replacement.
OBJECTS=$(patsubst %.$(EXTEN),%.o,$(CFILES))
DEPFILES=$(patsubst %.$(EXTEN),%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.$(EXTEN)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) dist.tgz

distribute: clean
	tar zcvf dist.tgz *

diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

# include the dependencies
-include $(DEPFILES)

.PHONY: all clean distribute diff

