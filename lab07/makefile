CC = gcc
CFLAGS = -Wall -g

all: main

main: FunctiiCoada-V.o FunctiiStiva-V.o main.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c TCoada.h TStiva.h
	$(CC) $(CFLAGS) -c $< -o $@

FunctiiCoada-V.o: FunctiiCoada-V.c TCoada.h TCoada-V.h
	$(CC) $(CFLAGS) -c $< -o $@

FunctiiStiva-V.o: FunctiiStiva-V.c TStiva.h TStiva-V.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean checkMem

clean:
	rm -f *.o main

checkMem:
	valgrind --leak-check=yes --track-origins=yes ./main

