CC= gcc
CFLAGS= -g -Wall -Wextra
LDFLAGS= -lSDL2 -lSDL2_image -lm -lSDL2_ttf
OBJ= build/tas_noeuds.o build/main.o build/partition.o build/liste.o build/graphe.o build/labyrinthe.o build/ennemi.o build/piece.o build/joueur.o build/score.o

prog:$(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

build/score.o : src/score.c src/score.h 
	$(CC) $(CFLAGS) -c -o $@ $<

build/piece.o:src/piece.c src/piece.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/joueur.o:src/joueur.c src/joueur.h
	$(CC) $(CFLAGS) -c -o $@ $<

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

build/main.o:src/main.c src/tas_noeuds.h src/partition.h src/liste.h src/graphe.h src/labyrinthe.h src/ennemi.h src/joueur.h src/piece.h src/score.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean : 
	rm -f $(OBJ)

afficher :
	dot -Tpng files/affichage.dot -o files/affichage.png
	open files/affichage.png

afficher_graphe :
	dot -Tpng files/graphe.dot -o files/graphe.png
	open files/graphe.png

afficher_cc :
	dot -Tpng files/sous_graphe.dot -o files/sous_graphe.png
	open files/sous_graphe.png

afficher_lab :
	dot -Tpng files/labyrinthe.dot -o files/labyrinthe.png
	open files/labyrinthe.png