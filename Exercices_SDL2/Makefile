CC=gcc
CFLAGS=-Wall -Wextra -g -lSDL2 -lSDL2_image

a_animation: src/Antoine/a_animation.c
	$(CC) $(CFLAGS) -lm -o exec/$@ $<

a_animation_shadow: src/Antoine/a_animation_shadow.c
	$(CC) $(CFLAGS) -o exec/$@ $<

a_dvd: src/Antoine/a_dvd.c
	$(CC) $(CFLAGS) -o exec/$@ $<

a_jeuvie: src/Antoine/a_jeuvie.c
	$(CC) $(CFLAGS) -o exec/$@ $<

a_x_windows: src/Antoine/X_windows.c
	$(CC) $(CFLAGS) -o exec/$@ $<

r_animation: src/Raphael/r_animation.c
	$(CC) $(CFLAGS) -o exec/$@ $<

r_sprite: src/Raphael/r_sprite.c
	$(CC) $(CFLAGS) -o exec/$@ $<

r_vie: src/Raphael/r_vie.c
	$(CC) $(CFLAGS) -lm -o exec/$@ $<

l_carre: src/Louis/l_carre.c
	$(CC) $(CFLAGS) -o exec/$@ $<

l_fenetreX: src/Louis/l_fenetreX.c
	$(CC) $(CFLAGS) -o exec/$@ $<

l_jeu_vie: src/Louis/l_jeu_vie.c
	$(CC) $(CFLAGS) -o exec/$@ $<

l_texture: src/Louis/l_texture.c
	$(CC) $(CFLAGS) -o exec/$@ $<
