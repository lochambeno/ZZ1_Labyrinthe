CC = gcc
CFLAGS = -g -Wall -Wextra

OBJ = build/main.o build/tas_binaire.o
OBJ2 = build/qsort.o build/tas_binaire.o

prog : $(OBJ)
	$(CC) $^ -o $@

quick_sort : $(OBJ2)
	$(CC) $^ -o $@

build/tas_binaire.o : src/tas_binaire.c src/tas_binaire.h
	$(CC) $(CFLAGS) $< -c -o $@

build/main.o : src/main.c src/tas_binaire.h
	$(CC) $(CFLAGS) $< -c -o $@

build/qsort.o : src/qsort.c src/tas_binaire.h
	$(CC) $(CFLAGS) $< -c -o $@

clean :
	rm -f $(OBJ) $(OBJ2)
