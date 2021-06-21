CC= gcc
CFLAGS= -g -Wall -Wextra
LFLAGS=
OBJ= build/partition.o build/main.o

prog:$(OBJ)
	$(CC) $^ -o $@ 

build/partition.o:src/partition.c src/partition.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/main.o:src/main.c src/partition.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean : 
	rm -f $(OBJ)