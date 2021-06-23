#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "partition.h"
#include "connexe.h"
#include "kruskal.h"
#include "labyrinthe.h"
#include "representation.h"

int main() {
    SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
    SDL_Texture * texture = NULL;

    create_sdl(&window, &renderer, "Labyrinthe");
    int fin_programme = 0,
		pause = 0,
        window_h,
        window_w;

    laby_t laby = creer_laby(10,10);

    texture = IMG_LoadTexture(renderer, "./img/tileset.png");
    if (texture == NULL) {
        end_sdl(0, "Error : can't load texture", window, renderer);
    }

    SDL_GetWindowSize(window, &window_w, &window_h);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    while (!fin_programme){
        SDL_Event event;
            while(!fin_programme && SDL_PollEvent(&event)){
                switch(event.type){
                case SDL_QUIT:
                    fin_programme = 1;
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
					case SDLK_p:
						pause=0;
						break;
					case SDLK_ESCAPE:
						fin_programme = 1;
						break;
                    default:
                        break;
                    }
                    break;

                default:
                    break;
                }
            }

		draw_laby(renderer, window_h, window_w, texture, laby);
		SDL_RenderPresent(renderer);

		SDL_Delay(10);
    }

    //afficher_arbre_couvrant(labyrinthe.graphe);
    liberer_labyrinthe(&laby);
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}