CC = gcc
CCFLAGS = -std=c11 -pedantic -Wall -Wextra -g
LDFLAGS = -fsanitize=address


all: wordcount wordcount-dynamic tail

.PHONY: clean

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CCFLAGS) wordcount.o io.o -o $@ -fPIC -L. -lhtab -static

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CCFLAGS) wordcount.o io.o -o $@ $(LDFLAGS) -fPIC -L. -lhtab

wordcount.o: wordcount.c
	$(CC) $(CCFLAGS) $^ -c

io.o: io.c
	$(CC) $(CCFLAGS) $^ -c

libhtab.a: htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o \
           htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o
	ar rcs $@ $^

libhtab.so: htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o \
            htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o
	gcc -shared -fPIC $^ -o $@

clean:
	rm wordcount tail wordcount-dynamic *.o


htab_bucket_count.o: htab_bucket_count.c htab_structs_definition.h htab.h
	$(CC) $(CCFLAGS) -c -fPIC $<

htab_clear.o: htab_clear.c htab_structs_definition.h htab.h
	$(CC) $(CCFLAGS) -c -fPIC $<

htab_erase.o: htab_erase.c htab_structs_definition.h htab.h
	$(CC) $(CCFLAGS) -c -fPIC $<

htab_find.o: htab_find.c htab_structs_definition.h htab.h
	$(CC) $(CCFLAGS) -c -fPIC $<

htab_for_each.o: htab_for_each.c htab_structs_definition.h htab.h
	$(CC) $(CCFLAGS) -c -fPIC $<

htab_free.o: htab_free.c htab_structs_definition.h htab.h
	$(CC) $(CCFLAGS) -c -fPIC $<

htab_hash_function.o: htab_hash_function.c htab_structs_definition.h htab.h
	$(CC) $(CCFLAGS) -c -fPIC $<

htab_init.o: htab_init.c htab_structs_definition.h htab.h
	$(CC) $(CCFLAGS) -c -fPIC $<

htab_lookup_add.o: htab_lookup_add.c htab_structs_definition.h htab.h
	$(CC) $(CCFLAGS) -c -fPIC $<

htab_resize.o: htab_resize.c htab_structs_definition.h htab.h
	$(CC) $(CCFLAGS) -c -fPIC $<

htab_size.o: htab_size.c htab_structs_definition.h htab.h
	$(CC) $(CCFLAGS) -c -fPIC $<

tail: tail.o
	$(CC) tail.o -o tail $(LDFLAGS)

tail.o: tail.c
	$(CC) $(CCFLAGS) tail.c -c

xhucov00.zip:
