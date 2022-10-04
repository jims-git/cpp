# Playground to learn Makefile
Just using this to learn the voodoo that is Makefile.

Thanks to https://www.youtube.com/watch?v=DtGrdB8wQ_8 for instructions.<br>
Also https://www.youtube.com/watch?v=20GC9mYoFGs explains Auto Variables.

My Github : https://github.com/jims-git/cpp

This is my attempt to build a "one-size-fits-all" Makefile.

First step is to setup all the variables, the second step is to
create all the targets. 
<br>
By default MAKE will run the first TARGET it finds, therefore it is
standard practice to name the first TARGET "all".
<br>
TARGETS are defined as:<br>
<pre><code><b>
targetName : dependency
	(tab) commands
</b></code></pre>
<br>
Once all of the dependencies are satisfied, then the commands will be executed.
<br>
# STEP 1: Name of application
<pre><code>
<b>BINARY=myApp</b>
</code></pre>
<br>
# STEP 2: for c files use gcc, for c++ use g++
<br>
<pre><code>
<b>CC=g++</b>
</code></pre>
<br>
<br>
# Nothing to modify below this line<br>
<hr>
If CC == gcc then this will be a C program, so set EXTEN=c to search for .c files.<br>
else<br>
this will be a C++ program, so set EXTEN=cpp to search for .cpp files, and<br>
set the flag -std=c++20.<br>
<br>
EXTEN == c or cpp file extensions<br>
<br>
<pre><code><b>ifeq ($(CC), gcc)
	$(info Makefile to build C program $(BINARY).)
 	EXTEN=c
 	STD=
else
 	$(info Makefile to build C++ program $(BINARY).)
 	EXTEN=cpp
 	STD=-std=c++20
endif
</code></pre>
<br>
# Project Structure
<hr>
<pre><code>
 ├── include<br>
 │   └── myfunctions.h<br>
 ├── lib<br>
 │   └── myfunctions.cpp<br>
 ├── main.c<br>
 ├── Makefile<br>
 ├── myprogram.cpp<br>
 └── README.md<br>
 </code></pre>
<br>
Look in these directories for .cpp files<br>
<b>CODEDIRS=. lib</b><br>
<br>
Look in these directories for .h files<br>
<b>INCDIRS=. ./include/ # can be list</b><br>
<br>
Not sure what this argument is used for.<br>
<b>OPT=-O0</b><br>
<br>
Magic argument to generate files that encode make rules for the .h dependencies.<br>
It will read the source files, looking for #include .h files, and if these<br>
files are changed, the source file will be recompiled.<br>
<b>DEPFLAGS=-MP -MD</b><br>
<br>
automatically add the -I onto each include directory<br>
<b>CFLAGS=-Wall -Wextra -g $(foreach D,$(INCDIRS),-I$(D)) $(STD) $(OPT) $(DEPFLAGS)</b><br>
<br>
for-style iteration (foreach) and regular expression completions (wildcard)<br>
For each D in $(CODEDIRS)<br>
find all the .cpp files (or if gcc then all the .c files)<br>
<br>
ie: CFILES=./myprogram.cpp ./lib/myfunctions.cpp<br>
<b>CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.$(EXTEN)))</b><br>
<br>
# Regular Expression replacement.
This is a little difficult to read.<br>
To create a LIST of OBJECTS (.o), we are pattern substituting<br> 
any .cpp files in $(CFILES) into .o files.<br>
ie: OBJECTS=./myprogram.o ./lib/myfunctions.o<br>
To create a LIST of DEPFILES (.d), we are pattern substituting<br> 
any .cpp files in $(CFILES) into .d files.<br>
ie: DEPFILES=./myprogram.d ./lib/myfunctions.d<br>
<b>OBJECTS=$(patsubst %.$(EXTEN),%.o,$(CFILES))</b><br>
<b>DEPFILES=$(patsubst %.$(EXTEN),%.d,$(CFILES))</b><br>
<br>
# Begin TARGETS
<br>
Default first target is called 'all'.<br>
It has a dependency target called $(BINARY) aka myApp<br>
<b>all: $(BINARY)</b><br>
<br>
Automatic Variables<br>
-------------------<br>																	<br>															
$@ = Target Name (LEFT side of the :)<br>
ie:<br>
mymain:main.o lib.o<br>
	g++ -o mymain main.o lib.o<br>
		can be written as<br>
	g++ -o $@ main.o lib.o<br>
<br>
<br>
Automatic Variables<br>
-------------------<br>																	<br>															
$^ = The name of the all prerequisites (RIGHT side of the :)<br>
<br>
ie:<br>
mymain:main.o lib.o<br>
	g++ -o mymain main.o lib.o<br>
		can be written as<br>
	g++ -o $@ $^<br>
<br>
Second TARGET is called $(BINARY) aka myApp and has a<br> 
dependency of all the .o files.<br>
for each item in OBJECTS, it will look for %.o TARGET and build the .o<br>
Once all the .o's are built, then it will compile the final binary.<br>
<b>$(BINARY): $(OBJECTS)</b><br>
<b>	$(CC) -o $@ $^</b><br>
<br>
<br>
only want the .c file dependency here, thus $< instead of $^.<br>
<br>
Automatic Variables<br>
-------------------<br>														
$< = The name of the FIRST prerequisite (RIGHT side of the :)<br>
<br>
ie:<br>
mymain:main.o lib.o<br>
	g++ -o mymain main.o lib.o<br>
		can be written as<br>
	g++ -o $@ $< lib.o<br>
<br>
This is the third TARGET. It will build all the .o files from the .cpp<br>
% = use the TARGET name (TARGET=main so main.o:main.c is %.o:%.c)<br>
<b>%.o:%.$(EXTEN)</b><br>
<b>	$(CC) $(CFLAGS) -c -o $@ $<</b><br>
<br>
<b>clean:</b><br>
<b>	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES) dist.tgz</b><br>
<br>
shell commands are a set of keystrokes away.<br>
This target will first run make clean, and then tarball the directory.<br>
<b>distribute: clean</b><br>
<b>	tar zcvf dist.tgz *</b><br>
<br>
@ silences the printing of the command<br>
$(info <user_defined_message>) prints output<br>
<b>diff:</b><br>
<b>	$(info The status of the repository, and the volume of per-file changes:)</b><br>
<b>	@git status</b><br>
<b>	@git diff --stat</b><br>
<br>
include the dependencies<br>
<b>-include $(DEPFILES)</b><br>
<br>
If there was a file called 'clean' and you tried to 'make clean'<br>
you would be told that 'clean' is up to date, so nothing to do.<br>
Add .PHONY so that the non-targetfile - rules work even if <br>
a file with the same name exists.<br>
<b>.PHONY: all clean distribute diff</b><br>
<br>
# RECAP
Automatic Variables<br>
-------------------<br>
 <br>
$@ = Target Name (LEFT side of the :)<br>
$< = The name of the FIRST prerequisite (RIGHT side of the :)<br>
$^ = The name of the all prerequisites (RIGHT side of the :)<br>											
% = use the TARGET name (TARGET=main so main.o:main.c is %.o:%.c)<br>
<br>
ie:<br>
	.PHONY: all clean<br>
	all: main<br>
<br>
	main: main.o lib.o<br>
		gcc -o $@ $^<br>
<br>
Compile all of the .o files from the .c files<br>
	%.o:%.c<br>
		gcc -c $< -o $@<br>
<br>
	clean:<br>
		rm -f *.o main<br>
<br>
<br>
