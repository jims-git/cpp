# Thanks to https://www.youtube.com/watch?v=DtGrdB8wQ_8 for instructions.

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
else
 $(info Makefile for C++ program)
 EXTEN=cpp
endif

# Look in these directories for src files
CODEDIRS=. lib

# Look in these directories for .h files
INCDIRS=. ./include/ # can be list

OPT=-O0

# generate files that encode make rules for the .h dependencies
DEPFLAGS=-MP -MD

# automatically add the -I onto each include directory
CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)

# for-style iteration (foreach) and regular expression completions (wildcard)
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.$(EXTEN)))

# regular expression replacement
OBJECTS=$(patsubst %.$(EXTEN),%.o,$(CFILES))
DEPFILES=$(patsubst %.$(EXTEN),%.d,$(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

# only want the .c file dependency here, thus $< instead of $^.
#
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

