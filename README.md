# Playground to learn Makefile

Just using this to learn the voodoo that is Makefile.

Thanks to https://www.youtube.com/watch?v=DtGrdB8wQ_8 for instructions.

Also https://www.youtube.com/watch?v=20GC9mYoFGs explains Auto Variables.

My Github : https://github.com/jims-git/cpp

This is my attempt to build a "one-size-fits-all" Makefile.


First step is to setup all the variables, the second step is to create all the targets. 
By default MAKE will run the first TARGET it finds, therefore it is standard practice to name the first TARGET "all". 

TARGETS are defined as:

targetName :  prerequisites<br>
  (tab) commands

Once all of the prerequisites are satisfied, then the commands will be executed. 

### STEP 1: Name of application
<pre><code>BINARY=myApp</code></pre>


### STEP 2: For c files use gcc, for c++ use g++
<pre><code>CC=g++</code></pre>



### Nothing to modify below this line

If CC == gcc then this will be a C program, so set EXTEN=c to search for .c files.

else

this will be a C++ program, so set EXTEN=cpp to search for .cpp files, and

set the flag -std=c++20.

EXTEN == c or cpp file extensions
<pre><code>
ifeq ($(CC), gcc)
        $(info Makefile to build C program $(BINARY).)
        EXTEN=c
        STD=
else
        $(info Makefile to build C++ program $(BINARY).)
        EXTEN=cpp
        STD=-std=c++20
endif
</code></pre>


### Project Structure
<pre>
 ├── include
 │   └── myfunctions.h
 ├── lib
 │   └── myfunctions.cpp
 ├── main.c
 ├── Makefile
 ├── myprogram.cpp
 └── README.md</pre>

Look in these directories for .cpp files

<pre><code>CODEDIRS=. lib</code></pre>


Look in these directories for .h files

<pre><code>INCDIRS=. ./include/ # can be list</code></pre>


### Optimization

There are seven -O settings: -O0, -O1, -O2, -O3, -Os, -Og, and -Ofast. Only use one of them in /etc/portage/make.conf.

With the exception of -O0, the -O settings each activate several additional flags, so be sure to read the GCC manual's chapter on optimization options to learn which flags are activated at each -O level, as well as some explanations as to what they do.

Let us examine each optimization level:

-O0: This level (that is the letter "O" followed by a zero) turns off optimization entirely and is the default if no -O level is specified in CFLAGS or CXXFLAGS. This reduces compilation time and can improve debugging info, but some applications will not work properly without optimization enabled. This option is not recommended except for debugging purposes.

-O1: the most basic optimization level. The compiler will try to produce faster, smaller code without taking much compilation time. It is basic, but it should get the job done all the time.

-O2: A step up from -O1. The recommended level of optimization unless the system has special needs. -O2 will activate a few more flags in addition to the ones activated by -O1. With -O2, the compiler will attempt to increase code performance without compromising on size, and without taking too much compilation time. SSE or AVX may be utilized at this level but no YMM registers will be used unless -ftree-vectorize is also enabled.

-O3: the highest level of optimization possible. It enables optimizations that are expensive in terms of compile time and memory usage. Compiling with -O3 is not a guaranteed way to improve performance, and in fact, in many cases, can slow down a system due to larger binaries and increased memory usage. -O3 is also known to break several packages. Using -O3 is not recommended. However, it also enables -ftree-vectorize so that loops in the code get vectorized and will use AVX YMM registers.

-Os: optimizes code for size. It activates all -O2 options that do not increase the size of the generated code. It can be useful for machines that have extremely limited disk storage space and/or CPUs with small cache sizes.

-Og: In GCC 4.8, a new general optimization level, -Og, has been introduced. It addresses the need for fast compilation and a superior debugging experience while providing a reasonable level of runtime performance. Overall experience for development should be better than the default optimization level -O0. Note that -Og does not imply -g, it simply disables optimizations that may interfere with debugging.

-Ofast: New in GCC 4.7, consists of -O3 plus -ffast-math, -fno-protect-parens, and -fstack-arrays. This option breaks strict standards compliance, and is not recommended for use.

As previously mentioned, -O2 is the recommended optimization level. If package compilation fails and while not using -O2, try rebuilding with that option. As a fallback option, try setting the CFLAGS and CXXFLAGS to a lower optimization level, such as -O1 or even -O0 -g2 -ggdb (for error reporting and checking for possible problems). 

<pre><code>OPT=-O0</code></pre>



Magic argument to generate files that encode make rules for the .h dependencies.

It will read the source files, looking for #include .h files, and if these

files are changed, the source file will be recompiled.

<pre><code>DEPFLAGS=-MP -MD</code></pre>



automatically add the -I onto each include directory
<pre><code>CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(STD) $(OPT) $(DEPFLAGS)</code></pre>



for-style iteration (foreach) and regular expression completions (wildcard)

For each D in $(CODEDIRS)

find all the .cpp files (or if gcc then all the .c files)

ie: CFILES=./myprogram.cpp ./lib/myfunctions.cpp

<pre><code>CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.$(EXTEN)))</code></pre>





### Regular Expression replacement.

This is a little difficult to read.

To create a LIST of OBJECTS (.o), we are pattern substituting

any .cpp files in $(CFILES) into .o files.

ie: OBJECTS=./myprogram.o ./lib/myfunctions.o

To create a LIST of DEPFILES (.d), we are pattern substituting

any .cpp files in $(CFILES) into .d files.

ie: DEPFILES=./myprogram.d ./lib/myfunctions.d

<pre><code>OBJECTS=$(patsubst %.$(EXTEN),%.o,$(CFILES))
DEPFILES=$(patsubst %.$(EXTEN),%.d,$(CFILES))</code></pre>


### Begin TARGETS

#### Default first target is called 'all'.

It has a prerequisite target called $(BINARY) aka myApp
<pre><code>all: $(BINARY)</code></pre>



#### Second TARGET is called $(BINARY) aka myApp and has a

prerequisite of all the .o files.

for each item in OBJECTS, it will look for %.o TARGET and build the .o

Once all the .o's are built, then it will compile the final binary.
<pre><code>$(BINARY): $(OBJECTS)
        $(CC) -o $@ $^</code></pre>



#### This is the third TARGET. It will build all the .o files from the .cpp

% = use the TARGET name (TARGET=main so main.o:main.c is %.o:%.c)

<pre><code>%.o:%.$(EXTEN)
        $(CC) $(CFLAGS) -c -o $@ $<</code></pre>



#### Clean TARGET removes any generated files, leaving the SOURCE code.

<pre><code>clean:
        rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) dist.tgz</code></pre>

#### This target will first run make clean, and then tarball the directory.

<pre><code>distribute: clean
        tar zcvf dist.tgz *</code></pre>



@ silences the printing of the command

$(info ) prints output
<pre><code>diff:
        $(info The status of the repository, and the volume of per-file changes:)
        @git status
        @git diff --stat</code></pre>



include the dependencies
<pre><code>-include $(DEPFILES)</code></pre>



If there was a file called 'clean' and you tried to 'make clean'

you would be told that 'clean' is up to date, so nothing to do.

Add .PHONY so that the non-targetfile - rules work even if 

a file with the same name exists.
<pre><code>
.PHONY: all clean distribute diff
</code></pre>


### End of Makefile Code. RECAP Automatic Variables

$@ = Target Name (LEFT side of the :)

$< = The name of the FIRST prerequisite (RIGHT side of the :)

$^ = The name of the all prerequisites (RIGHT side of the :)

% = use the TARGET name (TARGET=main so main.o:main.c is %.o:%.c)
<pre>
.PHONY: all clean
all: main

main: main.o lib.o
	gcc -o $@ $^

%.o:%.c
	gcc -c $< -o $@

clean:
	rm -f *.o main
	
================================================================

$< = The name of the FIRST prerequisite (RIGHT side of the :)
ie:
mymain:main.o lib.o
	g++ -o mymain main.o lib.o
		can be written as
	g++ -o $@ $< lib.o

$@ = Target Name (LEFT side of the :)
ie:
mymain:main.o lib.o
	g++ -o mymain main.o lib.o
		can be written as
	g++ -o $@ main.o lib.o

================================================================

$^ = The name of the all prerequisites (RIGHT side of the :)
ie:
mymain:main.o lib.o
	g++ -o mymain main.o lib.o
		can be written as
	g++ -o $@ $^
</pre>
