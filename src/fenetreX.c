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

  SDL_Window *window_1 = NULL,               // Future fenêtre de gauche
      *window_2 = NULL,
      *window_3 = NULL,
      *window_4 = NULL,
      *window_5 = NULL;                      // Future fenêtre de droite

  SDL_DisplayMode display;
  SDL_GetCurrentDisplayMode(1, &display);

  largeur = (display.w)/3;
  hauteur = (display.h)/3;

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }


  window_1 = SDL_CreateWindow(
      "En haut à gauche",                    // codage en utf8, donc accents possibles
      0, 0,                                  // coin haut gauche en haut gauche de l'écran
      largeur, hauteur,                              // largeur = 400, hauteur = 300
      0);                // redimensionnable

  if (window_1 == NULL) {
    SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  
  window_2 = SDL_CreateWindow(
      "En haut à droite",                    // codage en utf8, donc accents possibles
      display.w - largeur, 0,                                // à droite de la fenêtre de gauche
      largeur, hauteur,                              // largeur = 500, hauteur = 300
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
      "Au milieu",                    // codage en utf8, donc accents possibles
      largeur, hauteur,                                // à droite de la fenêtre de gauche
      largeur, hauteur,                              // largeur = 500, hauteur = 300
      0);

  if (window_3 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

    window_4 = SDL_CreateWindow(
      "En bas à gauche",                    // codage en utf8, donc accents possibles
      0, 2*hauteur,                                // à droite de la fenêtre de gauche
      largeur, hauteur,                              // largeur = 500, hauteur = 300
      0);

  if (window_4 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  window_5 = SDL_CreateWindow(
    "En bas à droite",                    // codage en utf8, donc accents possibles
    2*largeur, 2*hauteur,                                // à droite de la fenêtre de gauche
    largeur, hauteur,                              // largeur = 500, hauteur = 300
    0);

  if (window_5 == NULL) {
    /* L'init de la SDL : OK
       fenêtre 1 :OK
       fenêtre 2 : échec */
    SDL_Log("Error : SDL window 2 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre 
    SDL_DestroyWindow(window_1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  /* Normalement, on devrait ici remplir les fenêtres... */
  do {
      SDL_WaitEvent(&event);
  }while(event.type != SDL_QUIT);                            // Pause exprimée  en ms

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
 
  SDL_DestroyWindow(window_5);  
  SDL_DestroyWindow(window_4);
  SDL_DestroyWindow(window_3);
  SDL_DestroyWindow(window_2);
  SDL_DestroyWindow(window_1);

  SDL_Quit();
  return 0;
}

