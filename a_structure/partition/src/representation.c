#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include "representation.h"

void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
                    char const* msg,                                    // message à afficher
                    SDL_Window* window,                                 // fenêtre à fermer
                    SDL_Renderer* renderer) {                           // renderer à fermer
    char msg_formated[255];                                         
    int l;                                                          

    if (!ok) {                                                      
        strncpy(msg_formated, msg, 250);                                 
        l = strlen(msg_formated);                                        
        strcpy(msg_formated + l, " : %s\n");                     

        SDL_Log(msg_formated, SDL_GetError());                   
    }                                                               

    if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
    if (window != NULL)   SDL_DestroyWindow(window);                                        

    IMG_Quit();
    SDL_Quit();                                                     

    if (!ok) {                                                      
            exit(EXIT_FAILURE);                                              
    }                                                               
} 

void create_sdl(SDL_Window** window, SDL_Renderer** renderer, char* window_title) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", *window, *renderer);
    
    *window = SDL_CreateWindow(window_title,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            1080,
                            720,
                            0);
    
    if (*window == NULL) end_sdl(0, "ERROR WINDOW CREATION", *window, *renderer);
    
    *renderer = SDL_CreateRenderer(
            *window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", *window, *renderer);
}

void draw_laby_line(SDL_Renderer* renderer, int window_h, int window_w, laby_t laby) {
    int i;
    int length_h = window_h/laby.hauteur;
    int length_w = window_w/laby.largeur;
    int pos_x, pos_y;
    for (i=0; i<laby.graphe.nbr_noeuds; ++i) {
        pos_x = length_w/2 + length_w*(i%laby.largeur);
        pos_y = length_h/2 + length_h*(i/laby.largeur);
        if (laby.caracteristique[i].NSEO & 2) SDL_RenderDrawLine(renderer,pos_x,pos_y,pos_x+length_w,pos_y);
        if (laby.caracteristique[i].NSEO & 4) SDL_RenderDrawLine(renderer,pos_x,pos_y,pos_x,pos_y+length_h);
    }
}

void draw_laby(SDL_Renderer* renderer, int window_h, int window_w, SDL_Texture* texture, laby_t laby) {
    int i;

    SDL_Rect source={0}, destination={0};

    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);

    source.h=source.h/8;
    source.w=source.w/12;

    destination.h = window_h/laby.hauteur;
    destination.w = window_w/laby.largeur;

    for (i=0; i<laby.graphe.nbr_noeuds; ++i) {
        destination.x = destination.w*(i%laby.largeur);
        destination.y = destination.h*(i/laby.largeur);

        switch (laby.caracteristique[i].NSEO) {
            case 15:
                source.x=9*source.w;
                source.y=0*source.h;
                break;
            case 14:
                source.x=4*source.w;
                source.y=2*source.h;
                break;
            case 13:
                source.x=5*source.w;
                source.y=2*source.h;
                break;
            case 12:
                source.x=0;
                source.y=0;
                break;
            case 11:
                source.x=4*source.w;
                source.y=3*source.h;
                break;
            case 10:
                source.x=5*source.w;
                source.y=source.h;
                break;
            case 9:
                source.x=6*source.w;
                source.y=source.h;
                break;
            case 8:
                source.x=9*source.w;
                source.y=2*source.h;
                break;
            case 7:
                source.x=5*source.w;
                source.y=3*source.h;
                break;
            case 6:
                source.x=5*source.w;
                source.y=0;
                break;
            case 5:
                source.x=6*source.w;
                source.y=0;
                break;
            case 4:
                source.x=8*source.w;
                source.y=2*source.h;
                break;
            case 3:
                source.x=0;
                source.y=source.h;
                break;
            case 2:
                source.x=8*source.w;
                source.y=3*source.h;
                break;
            case 1:
                source.x=9*source.w;
                source.y=3*source.h;
                break;
            default:
                source.x=0;
                source.y=2*source.h;
                break;
        }
        SDL_RenderCopy(renderer, texture, &source, &destination);
    }
}


void draw_laby_parcours_prof(SDL_Renderer* renderer, int window_h, int window_w, SDL_Texture* texture, laby_t laby, exploration_t exploration, int state) {
    int i;

    SDL_Rect source={0}, destination={0}, animation={0};

    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);

    source.h=source.h/8;
    source.w=source.w/12;

    destination.h = window_h/laby.hauteur;
    destination.w = window_w/laby.largeur;

    animation.h = destination.h;
    animation.w = destination.w;

    for (i=0; i<state; ++i) {
        destination.x = destination.w*(exploration.liste[i]%laby.largeur);
        destination.y = destination.h*(exploration.liste[i]/laby.largeur);

        switch (laby.caracteristique[exploration.liste[i]].NSEO) {
            case 15:
                source.x=9*source.w;
                source.y=0*source.h;
                break;
            case 14:
                source.x=4*source.w;
                source.y=2*source.h;
                break;
            case 13:
                source.x=5*source.w;
                source.y=2*source.h;
                break;
            case 12:
                source.x=0;
                source.y=0;
                break;
            case 11:
                source.x=4*source.w;
                source.y=3*source.h;
                break;
            case 10:
                source.x=5*source.w;
                source.y=source.h;
                break;
            case 9:
                source.x=6*source.w;
                source.y=source.h;
                break;
            case 8:
                source.x=9*source.w;
                source.y=2*source.h;
                break;
            case 7:
                source.x=5*source.w;
                source.y=3*source.h;
                break;
            case 6:
                source.x=5*source.w;
                source.y=0;
                break;
            case 5:
                source.x=6*source.w;
                source.y=0;
                break;
            case 4:
                source.x=8*source.w;
                source.y=2*source.h;
                break;
            case 3:
                source.x=0;
                source.y=source.h;
                break;
            case 2:
                source.x=8*source.w;
                source.y=3*source.h;
                break;
            case 1:
                source.x=9*source.w;
                source.y=3*source.h;
                break;
            default:
                source.x=0;
                source.y=2*source.h;
                break;
        }
        SDL_RenderCopy(renderer, texture, &source, &destination);
    }
    animation.x = animation.w*(exploration.liste[i]%laby.largeur);
    animation.y = animation.h*(exploration.liste[i]/laby.largeur);
    SDL_RenderFillRect(renderer, &animation);
}
 