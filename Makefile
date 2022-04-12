CC = gcc
CCFLAGS = -std=c11 -pedantic -Wall -Wextra -g
LDFLAGS = -fsanitize=address



tail: tail.o
	$(CC) tail.o -o tail $(LDFLAGS)

tail.o: tail.c
	$(CC) $(CCFLAGS) tail.c -c

run: tail
	./tail


clean:
	rm tail *.o
