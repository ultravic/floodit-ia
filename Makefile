# Victor Picussa - GRR20163068
CFLAGS = -Wall -O3
CC = g++
FILES = src/solver.cpp
OUT = solver

all: solver clean

solver: solver.o
	$(CC) $(FILES) -o $(OUT) $(CFLAGS) -l cgraph

solver.o:
	$(CC) $(FILES) -o solver.o $(CFLAGS) -l cgraph

clean:
	rm *.o

purge:
	rm solver
