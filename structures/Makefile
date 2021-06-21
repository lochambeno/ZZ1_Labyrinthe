CC= gcc
CFLAGS= -g -Wall -Wextra -O2
LDFLAGS=
OBJ= build/tas.o build/main.o build/partition.o build/liste.o

prog:$(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

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