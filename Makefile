# Makefile for the puzzle API
# Isaac Feldman 2021
PROG = 
OBJS = puzzle.o
LIBS = 
CFLAGS =  -Wall -pedantic -std=c11 -ggdb 
CC = gcc

.PHONY: all clean

all: puzzle.o

unittest: $(OBJS) puzzle_unit_test.o $(LIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	valgrind ./unittest
	rm -f unittest

puzzle.o: puzzle.h 
puzzle_unit_test.o: puzzle_unit_test.c 

clean:
	rm -f *~ *.o core

