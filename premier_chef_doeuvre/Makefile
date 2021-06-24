CC= gcc
CFLAGS= -g -Wall -Wextra
SDLC= -lSDL2 -lSDL2_image -lSDL2_ttf
OBJ = build/main.o build/window.o build/score.o build/asteroid.o build/vaisseau.o

prog : $(OBJ)
	$(CC) $^ -o $@ $(SDLC)

build/window.o : src/window.c src/window.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/score.o : src/score.c src/score.h src/window.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/asteroid.o:src/asteroid.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/vaisseau.o:src/vaisseau.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/main.o:src/main.c src/vaisseau.h src/asteroid.h src/window.h src/score.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean : 
	rm -f $(OBJ)