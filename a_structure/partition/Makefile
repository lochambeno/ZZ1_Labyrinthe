CC = gcc
DOT = dot

CFLAGS = -g -Wall -Wextra
DFLAGS = -Tpng

OBJ = build/main.o build/partition.o build/connexe.o

prog : $(OBJ)
	$(CC) $^ -o $@

img/partition.png : file/partition.dot
	$(DOT) $(DFLAGS) $< -o $@	

img/graphe.png : file/graphe.dot
	$(DOT) $(DFLAGS) $< -o $@

img/comp_connexe.png : file/comp_connexe.dot
	$(DOT) $(DFLAGS) $< -o $@

build/partition.o : src/partition.c src/partition.h
	$(CC) $(CFLAGS) $< -c -o $@

build/connexe.o : src/connexe.c src/connexe.h src/partition.h
	$(CC) $(CFLAGS) $< -c -o $@

build/main.o : src/main.c src/partition.h src/connexe.h
	$(CC) $(CFLAGS) $< -c -o $@

clean :
	rm -f $(OBJ)