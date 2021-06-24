CC = gcc
DOT = dot

CFLAGS = -g -Wall -Wextra
SDLC = -lSDL2 -lSDL2_image
DFLAGS = -Tpng

OBJ = build/main.o build/partition.o build/connexe.o build/kruskal.o build/labyrinthe.o build/representation.o build/parcours.o

prog : $(OBJ)
	$(CC) $^ -o $@ $(SDLC)

img/partition.png : file/partition.dot
	$(DOT) $(DFLAGS) $< -o $@	

img/graphe.png : file/graphe.dot
	$(DOT) $(DFLAGS) $< -o $@

img/comp_connexe.png : file/comp_connexe.dot
	$(DOT) $(DFLAGS) $< -o $@

img/arbre_couvrant.png : file/arbre_couvrant.dot
	$(DOT) $(DFLAGS) $< -o $@

build/partition.o : src/partition.c src/partition.h
	$(CC) $(CFLAGS) $< -c -o $@

build/connexe.o : src/connexe.c src/connexe.h src/partition.h
	$(CC) $(CFLAGS) $< -c -o $@

build/kruskal.o : src/kruskal.c src/kruskal.h src/connexe.h src/partition.h
	$(CC) $(CFLAGS) $< -c -o $@

build/labyrinthe.o : src/labyrinthe.c src/labyrinthe.h src/kruskal.h src/connexe.h src/partition.h
	$(CC) $(CFLAGS) $< -c -o $@

build/representation.o : src/representation.c src/representation.h src/labyrinthe.h
	$(CC) $(CFLAGS) $< -c -o $@

build/parcours.o : src/parcours.c src/parcours.h src/labyrinthe.h
	$(CC) $(CFLAGS) $< -c -o $@

build/main.o : src/main.c src/partition.h src/connexe.h src/kruskal.h src/labyrinthe.h src/representation.h src/parcours.h
	$(CC) $(CFLAGS) $< -c -o $@

clean :
	rm -f $(OBJ)