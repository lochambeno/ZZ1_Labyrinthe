CC= gcc
CFLAGS= -g -Wall -Wextra
SDLC= -lSDL2 -lSDL2_image -lSDL2_ttf
OBJ = main.o window.o score.o

prog : $(OBJ)
	$(CC) $^ -o $@ $(SDLC)

main.o : main.c window.h score.h
	$(CC) $(CFLAGS) -c $<

window.o : window.c window.h
	$(CC) $(CFLAGS) -c $<

score.o : score.c score.h window.h
	$(CC) $(CFLAGS) -c $<

clean : 
	rm -f $(OBJ)