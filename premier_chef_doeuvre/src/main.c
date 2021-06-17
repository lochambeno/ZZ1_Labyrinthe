#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include "score.h"

int main1() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;
    TTF_Font* font = NULL;

    /* Initialisation de la SDL */
    create_sdl(&window, &renderer, &screen, &font, "chef_d_oeuvre", "./SubZER0.ttf", 1, 1);
    
    /* Variables du programme */
    SDL_Color color_text = {255, 255, 255, 255};
    SDL_Rect pos_text = {20, 20, 0, 0}, pos_score = {20, 20, 0, 0};
    int score=0;

    /* Boucle des événements */
    SDL_bool
        program_on = SDL_TRUE,
        paused = SDL_FALSE,
        over = SDL_FALSE;
    while (program_on) {
        SDL_Event event;

        while (program_on && SDL_PollEvent(&event)) {
                                                        
            switch (event.type) {
            case SDL_QUIT:
                program_on = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                                                        
                switch (event.key.keysym.sym) {
                case SDLK_p:
                case SDLK_SPACE:
                    paused = !paused;
                    break;
                case SDLK_ESCAPE:
                case SDLK_q:
                    program_on = 0;
                    break;
                case SDLK_k:
                    paused = !paused;
                    over = SDL_TRUE;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
        
        afficher_score(window, renderer, font, color_text, pos_text, pos_score, score);

        if (!paused) {
        
            score+=10;
        }
        if (over) {
            game_over(window, renderer, screen, font, color_text);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    /* Fermeture de la SDL */
    end_sdl(1, "Normal ending", window, renderer);

    return 0;
}