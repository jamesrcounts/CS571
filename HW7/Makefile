###################################
# Makefile
# HW7
# CS571 - Fall 2012
# Jim Counts
###################################
CC = clisp

# .clisp source files
SRCS = interleave.clisp

# target (output)
PROG = $(SRCS:.clisp=.fas) 

# object files for the target. 
OBJ = $(SRCS:.clisp=.fas)

run: $(PROG)
	$(CC) $(SRCS)

$(PROG): $(SRCS) 
	$(CC) -c $(SRCS) 

# DO NOT DELETE