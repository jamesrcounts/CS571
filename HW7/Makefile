###################################
# Makefile
# HW7
# CS571 - Fall 2012
# Jim Counts
###################################
CC = clisp

# .clisp source files
SRCS = cd.clisp interleave.clisp 

# target (output)
PROG = $(SRCS:.clisp=.fas) 

$(PROG): $(SRCS) 
	$(CC) -c $(SRCS) 

# DO NOT DELETE