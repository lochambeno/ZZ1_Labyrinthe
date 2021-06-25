#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "score.h"


void afficher_score(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect pos_text, SDL_Rect pos_score, int i_score) {
    SDL_Surface* text_surface = NULL, *score_surface = NULL;

    text_surface = TTF_RenderText_Blended(font, "SC0RE: ", color);

    char s_score[20];
    sprintf(s_score, "%d", i_score);
    score_surface = TTF_RenderText_Blended(font, s_score, color);



    SDL_Texture* text_texture = NULL, * score_texture = NULL;     

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);

    SDL_FreeSurface(text_surface);
    SDL_FreeSurface(score_surface);



    SDL_QueryTexture(text_texture, NULL, NULL, &pos_text.w, &pos_text.h);

    pos_score.x=pos_text.x+pos_text.w;
    SDL_QueryTexture(score_texture, NULL, NULL, &pos_score.w, &pos_score.h);

    SDL_RenderCopy(renderer, text_texture, NULL, &pos_text);
    SDL_RenderCopy(renderer, score_texture, NULL, &pos_score);

    SDL_DestroyTexture(text_texture);
    SDL_DestroyTexture(score_texture);
}

void game_over(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) {
    SDL_Surface* text_surface = NULL;
    text_surface = TTF_RenderText_Blended(font, "GAME 0VER", color);

    SDL_Texture* text_texture = NULL;     
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);

    SDL_Rect pos = {0, 0, 0 ,0};
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);
    
    SDL_GetWindowSize(window, &pos.x, &pos.y);

    pos.x=(pos.x-pos.w)/2;
    pos.y=(pos.y-pos.h)/2;

    SDL_RenderCopy(renderer, text_texture, NULL, &pos);
    SDL_DestroyTexture(text_texture);
}