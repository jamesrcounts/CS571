###################################
# Makefile
# Assignment 2
# CS433 - Spring 2012
# Josh Pantarotto and Jim Counts
###################################
CC = g++			# use g++ for compiling c++ code or gcc for c code
CFLAGS = -O2 -Wall			# compilation flags: -g for debugging. Change to -O or -O2 for optimized code.
PROG = assignment2		# target executable (output)
HDRS = mysh.h
SRCS = main.cpp mysh.cpp		# .c or .cpp source files.  
OBJ = $(SRCS:.cpp=.o)		# object files for the target. Add more to this and next lines if there are more than one source files.

$(PROG): $(SRCS) $(HDRS) 
	$(CC) $(SRCS) -o $(PROG) $(CFLAGS)


# cleanup
clean:
	rm -f core $(PROG) $(OBJS)

# DO NOT DELETE