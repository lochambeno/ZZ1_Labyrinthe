CC= gcc
CFLAGS= -g -Wall -Wextra
LDFLAGS= -lSDL2 -lSDL2_image -lm
OBJ= build/tas_noeuds.o build/main2.o build/partition.o build/liste.o build/graphe.o build/labyrinthe.o build/ennemi.o

prog:$(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

build/labyrinthe.o:src/labyrinthe.c src/labyrinthe.h src/graphe.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/ennemi.o:src/ennemi.c src/ennemi.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/graphe.o:src/graphe.c src/graphe.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/partition.o:src/partition.c src/partition.h src/liste.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/tas_noeuds.o:src/tas_noeuds.c src/tas_noeuds.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/liste.o:src/liste.c src/liste.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/main2.o:src/main2.c src/tas_noeuds.h src/partition.h src/liste.h src/graphe.h src/labyrinthe.h src/ennemi.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean : 
	rm -f $(OBJ)

