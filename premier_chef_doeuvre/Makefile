CC=gcc
CFLAGS=-Wall -Wextra -g 
LFLAGS=-lSDL2 -lSDL2_image

executable:build/main.o build/vaisseau.o build/asteroid.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

build/asteroid.o:src/asteroid.c
	$(CC) -c -o $@ $<

build/vaisseau.o:src/vaisseau.c
	$(CC) -c -o $@ $<

build/main.o:src/main.c src/vaisseau.h src/asteroid.h
	$(CC) -c -o $@ $<