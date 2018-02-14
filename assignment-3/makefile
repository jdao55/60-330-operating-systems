CC=gcc
CFLAGS=-O3 -Wall -Wextra -march=native -Ofast
LIBS=-lpthread -lm -fopenmp
all: part1_q1 part1_q2 part1_q3 part1_q4

q1: part1_q1.c 
	$(CC) $(CFLAGS) part1_q1.c -o part1_q1 $(LIBS)
q2: part1_q2.c 
	$(CC) $(CFLAGS) part1_q2.c -o part1_q2 $(LIBS)
q3: part1_q3.c
	$(CC) $(CFLAGS) part1_q3.c -o part1_q3 $(LIBS)
q4: part1_q4.c
	$(CC) $(CFLAGS) part1_q4.c -o part1_q4 $(LIBS)
clean:
	rm part1_q1 part1_q2 part1_q3 part1_q4
