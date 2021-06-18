#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include "window.h"

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
    TTF_Quit(); 
    SDL_Quit();                                                     

    if (!ok) {                                                      
            exit(EXIT_FAILURE);                                              
    }                                                               
} 

void create_sdl(SDL_Window** window, SDL_Renderer** renderer, TTF_Font** font, char* window_title, char* font_path) {
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

    if (TTF_Init() < 0) end_sdl(0, "Couldn't initialize SDL TTF", *window, *renderer);

    *font = TTF_OpenFont(font_path, 65);
    if (*font == NULL) end_sdl(0, "Can't load font", *window, *renderer);
}