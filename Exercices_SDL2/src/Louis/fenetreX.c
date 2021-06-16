#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  SDL_Event event;

  int largeur;
  int hauteur;

  SDL_Window *window_1 = NULL,              
      *window_2 = NULL,
      *window_3 = NULL,
      *window_4 = NULL,
      *window_5 = NULL;                      

  SDL_DisplayMode display;

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }

  if (SDL_GetCurrentDisplayMode(0, &display) != 0)
    printf("ERROR\n");

  largeur = display.w/3;
  hauteur = display.h/3;

  window_1 = SDL_CreateWindow(
      "En haut à gauche",                    // codage en utf8, donc accents possibles
      0, 0,                                  // coin haut gauche en haut gauche de l'écran
      largeur, hauteur,                            
      0);               

  if (window_1 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  
  window_2 = SDL_CreateWindow(
      "En haut à droite",                    
      2*largeur, 0,                               
      largeur, hauteur,                             
      0);

  if (window_2 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

    window_3 = SDL_CreateWindow(
      "Au milieu",                    
      largeur, hauteur,               
      largeur, hauteur,               
      0);

  if (window_3 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   
    SDL_DestroyWindow(window_2);
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

    window_4 = SDL_CreateWindow(
      "En bas à gauche",                    
      0, 2*hauteur,                          
      largeur, hauteur,                             
      0);

  if (window_4 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_3);
    SDL_DestroyWindow(window_2);
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  window_5 = SDL_CreateWindow(
    "En bas à droite",                    
    2*largeur, 2*hauteur,                           
    largeur, hauteur,                              
    0);

  if (window_5 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_4);    
    SDL_DestroyWindow(window_3);
    SDL_DestroyWindow(window_2);
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  
  do {
      SDL_WaitEvent(&event);
  }while(event.type != SDL_QUIT);                            

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
 
  SDL_DestroyWindow(window_5);  
  SDL_DestroyWindow(window_4);
  SDL_DestroyWindow(window_3);
  SDL_DestroyWindow(window_2);
  SDL_DestroyWindow(window_1);

  SDL_Quit();
  return 0;
}

