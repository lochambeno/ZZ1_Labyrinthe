CC= gcc
CFLAGS= -g -Wall -Wextra
LDFLAGS=
OBJ= build/tas.o build/main.o build/partition.o build/liste.o build/graphe.o

prog:$(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

build/graphe.o:src/graphe.c src/graphe.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/partition.o:src/partition.c src/partition.h src/liste.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/tas.o:src/tas.c src/tas.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/liste.o:src/liste.c src/liste.h
	$(CC) $(CFLAGS) -c -o $@ $<

build/main.o:src/main.c src/tas.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean : 
	rm -f $(OBJ)

afficher :
	dot -Tpng files/affichage.dot -o files/affichage.png
	open files/affichage.png

afficher_graphe :
	dot -Tpng files/graphe.dot -o files/graphe.png
	open files/graphe.png