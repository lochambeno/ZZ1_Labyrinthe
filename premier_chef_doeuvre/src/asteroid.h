#ifndef ASTEROID_H
#define ASTEROID_H


void end_sdl(char , char const* , SDL_Window* , SDL_Renderer* );
SDL_Rect creer_asteroid(int , int);
void deplacement(SDL_Rect* , int );
void afficher_ast(SDL_Texture* , SDL_Rect* , SDL_Renderer* );
void afficher_fond(SDL_Texture *, SDL_Window *, SDL_Renderer *);





#endif