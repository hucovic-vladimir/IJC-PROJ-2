CC = gcc
CCFLAGS = -std=c11 -pedantic -Wall -Wextra -g
LDFLAGS = -fsanitize=address



tail: wordcount.o
	$(CC) wordcount.o -o wordcount $(LDFLAGS)

wordcount.o: wordcount.c
	$(CC) $(CCFLAGS) wordcount.c -c

run: wordcount
	./wordcount


clean:
	rm wordcount *.o
