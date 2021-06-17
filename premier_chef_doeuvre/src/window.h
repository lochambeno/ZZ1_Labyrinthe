#ifndef WINDOW_H
#define WINDOW_H

void end_sdl(char, char const*, SDL_Window*, SDL_Renderer*);
void create_sdl(SDL_Window**, SDL_Renderer**, TTF_Font**, char*, char*, float, float);

#endif