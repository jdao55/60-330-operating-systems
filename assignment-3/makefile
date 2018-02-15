CC=gcc
CFLAGS=-Wall -Wextra -O3 -march=native 
LIBS= -lpthread -lm -fopenmp
all: part1_q1 part1_q2 part1_q3 part1_q4 part2

part1_q1: part1_q1.c 
	$(CC) $(CFLAGS) part1_q1.c -o bin/part1_q1 $(LIBS)
part1_q2: part1_q2.c 
	$(CC) $(CFLAGS) part1_q2.c -o bin/part1_q2 $(LIBS)
part1_q3: part1_q3.c
	$(CC) $(CFLAGS) part1_q3.c -o bin/part1_q3 $(LIBS)
part1_q4: part1_q4.c
	$(CC) $(CFLAGS) part1_q4.c -o bin/part1_q4 $(LIBS)


part2: part2_q1 part2_q2
part2_q1:part2_q1.c
	$(CC) $(CFLAGS) part2_q1.c -o bin/part2_q1 $(LIBS)
part2_q2:part2_q2.c
	$(CC) $(CFLAGS) part2_q2.c -o bin/part2_q2 $(LIBS)
clean:
	rm bin/part1_q1 bin/part1_q2 bin/part1_q3 bin/part1_q4 bin/part2_q1 bin/part2_q2
