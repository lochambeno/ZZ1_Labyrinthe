#ifndef ZZ1_PROJET_CD_ASTEROID_H
#define ZZ1_PROJET_CD_ASTEROID_H

SDL_Rect creer_asteroid(int , int);
void deplacer_ast(SDL_Rect* , int , int);
void afficher_ast(SDL_Texture* , SDL_Rect* , SDL_Renderer* );
void afficher_fond(SDL_Texture *, SDL_Window *, SDL_Renderer *);

#endif