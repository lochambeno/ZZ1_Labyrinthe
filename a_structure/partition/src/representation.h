#ifndef REPRESENTATION_H
#define REPRESENTATION_H
#include "labyrinthe.h"

void end_sdl(char, char const*, SDL_Window*, SDL_Renderer*);
void create_sdl(SDL_Window**, SDL_Renderer**, char*);
void draw_laby_line(SDL_Renderer*, int, int, laby_t);
void draw_laby(SDL_Renderer*, int, int, SDL_Texture*, laby_t);

#endif