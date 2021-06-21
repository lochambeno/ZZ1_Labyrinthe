CC = gcc
DOT = dot

CFLAGS = -g -Wall -Wextra
DFLAGS = -Tpng

OBJ = build/main.o build/partition.o

prog : $(OBJ)
	$(CC) $^ -o $@

affichage.png : src/affichage.dot
	$(DOT) $(DFLAGS) $< -o $@	

build/partition.o : src/partition.c src/partition.h
	$(CC) $(CFLAGS) $< -c -o $@

build/main.o : src/main.c src/partition.h
	$(CC) $(CFLAGS) $< -c -o $@

clean :
	rm -f $(OBJ)