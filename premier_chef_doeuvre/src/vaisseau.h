#ifndef ZZ1_PROJET_CD_VAISSEAU_H
#define ZZ1_PROJET_CD_VAISSEAU_H

SDL_Rect init_vaisseau(SDL_Window *, SDL_Texture *);
void bouger_vaisseau_G(SDL_Rect * );
void bouger_vaisseau_D(SDL_Rect * , int );
void afficher_vaisseau(SDL_Rect, SDL_Texture *, SDL_Renderer *);

#endif