#ifndef ZZ1_PROJET_CD_VAISSEAU_H
#define ZZ1_PROJET_CD_VAISSEAU_H

typedef struct vaisseau_c{
	SDL_Rect r_sprite;
	SDL_Rect r_collision;
}vaisseau_t;

vaisseau_t init_vaisseau(SDL_Window *, SDL_Texture *);
void bouger_vaisseau_G(vaisseau_t * );
void bouger_vaisseau_D(vaisseau_t * , int );
void afficher_vaisseau(vaisseau_t, SDL_Texture *, SDL_Renderer *);

#endif