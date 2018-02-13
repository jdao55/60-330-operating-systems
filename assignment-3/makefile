CC=gcc
CFLAGS=-O3 -Wall -Wextra -march=native -Ofast
LIBS=-lpthread -lm -fopenmp
all: q1 q2 q3

q1: q1.c 
	$(CC) $(CFLAGS) q1.c -o q1 $(LIBS)
q2: q2.c 
	$(CC) $(CFLAGS) q2.c -o q2 $(LIBS)
q3: q3.c
	$(CC) $(CFLAGS) q3.c -o q3 $(LIBS)

clean:
	rm q1 q2 q3
