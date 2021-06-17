CC= gcc
CFLAGS= -g -Wall -Wextra
SDLC= -lSDL2 -lSDL2_image
OBJ = main.o window.o

prog : $(OBJ)
	$(CC) $^ -o $@ $(SDLC)

main.o : main.c window.h
	$(CC) $(CFLAGS) -c $<

window.o : window.c window.h
	$(CC) $(CFLAGS) -c $<

clean : 
	rm -f $(OBJ)