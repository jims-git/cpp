# https://www.youtube.com/watch?v=20GC9mYoFGs
# Makefile myprogram.cpp myfunctions.cpp myfunctions.h

# The compiler: gcc for C program, define as g++ for C++
CC = g++
 
# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -g -Wall
 
# The application name
TARGET = myprogram

# Make will launch the first Target, in this case all:
# all: depends upon the "myprogram" target
# .PHONY will make the "all" & "clean" be targets,
# in case there are actual files named all or clean.
.PHONY: all
all: $(TARGET)

# Automatic Variable $@ = filename of the target of the rule.
# Notice in the command line, "myprogram" is replaced with $@
#myprogram: myprogram.o myfunctions.o
#	g++ -o myprogram myprogram.o myfunctions.o
#              ---------
$(TARGET): myprogram.o myfunctions.o
	$(CC) $(CFLAGS) -o $@ $^
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean	
clean:
	rm -f $(TARGET) *.out *.o
