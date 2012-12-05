###################################
# Makefile
# Final Project
# CS571 - Fall 2012
# Jim Counts
###################################
CC = g++                                            # use g++ for compiling c++ code or gcc for c code
CFLAGS = -O2 -Wall                                  # compilation flags: -g for debugging. Change to -O or -O2 for optimized code.
PROG = mc                                           # target executable (output)
HDRS = Program.h Test.h TestFramework.h Move.h
SRCS = main.cpp                                     # .c or .cpp source files.  
OBJ = $(SRCS:.cpp=.o)                               # object files for the target. Add more to this and next lines if there are more than one source files.

test: $(PROG)
	./mc TEST

$(PROG): $(SRCS) $(HDRS) 
	$(CC) $(SRCS) -o $(PROG) $(CFLAGS)

# cleanup
clean:
	rm -f core $(PROG) $(OBJS)

# DO NOT DELETE