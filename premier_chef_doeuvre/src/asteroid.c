#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>

SDL_Rect tab_init_ast[40];


SDL_Rect creer_asteroid(int x, int y) 
{                                   
  SDL_Rect rectangle;

  rectangle.x = x;                                                   
  rectangle.y = y;                                                    
  rectangle.w = 100;                                                  
  rectangle.h = 100;                                                  

  return rectangle;
}

void init_ast(int window_dimensions_w)
{
  int i;

  for (i=0;i<40;++i) 
  {
    tab_init_ast[i] = creer_asteroid(rand()%(window_dimensions_w-100), -(rand()%2500));
  }
}

void deplacer_ast(SDL_Rect* rectangle, int pas, int window_h)
{
  if(rectangle->y + pas <= window_h)
    rectangle->y += pas;
  else
    rectangle->y = -(rand()%2500);

}

void afficher_ast(SDL_Texture* ast_texture,
                         SDL_Rect rectangle, 
                         SDL_Renderer* renderer) 
{
    SDL_Rect source = {0};

    SDL_QueryTexture(ast_texture, NULL, NULL, &source.w, &source.h);
    SDL_RenderCopy(renderer, ast_texture, &source, &rectangle);
}


void afficher_fond(SDL_Texture *fond_texture, SDL_Window *window, SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(fond_texture, NULL, NULL, &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  SDL_RenderCopy(renderer, fond_texture, &source, &destination);

}