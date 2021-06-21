CC= gcc
CFLAGS= -g -Wall -Wextra
LFLAGS=
OBJ= build/window.o build/main.o

prog:$(OBJ)
	$(CC) $^ -o $@ 

build/window.o:src/tas.c src/tas.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/main.o:src/main.c src/tas.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean : 
	rm -f $(OBJ)