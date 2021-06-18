CC = gcc
CFLAGS = -g -Wall -Wextra

OBJ = build/main.o build/tas_binaire.o

prog : $(OBJ)
	$(CC) $^ -o $@

build/tas_binaire.o : src/tas_binaire.c src/tas_binaire.h
	$(CC) $(CFLAGS) $< -c -o $@

build/main.o : src/main.c src/tas_binaire.h
	$(CC) $(CFLAGS) $< -c -o $@

clean :
	rm -f $(OBJ)
