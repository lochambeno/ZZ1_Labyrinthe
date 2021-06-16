#include <SDL2/SDL.h>
#include <stdio.h>

/************************************/
/*  exemple de création de fenêtres */
/************************************/

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  int display_width, display_height;

  SDL_Window *window_d1 = NULL, *window_d2 = NULL, *window_d3 = NULL, *window_d4 = NULL, *window_d5 = NULL,              // Future fenêtre de gauche
      *window_g1 = NULL, *window_g2 = NULL, *window_g3 = NULL, *window_g4 = NULL, *window_g5 = NULL;                      // Future fenêtre de droite

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }
  
  SDL_DisplayMode current;
  int current_display = SDL_GetCurrentDisplayMode(0,&current);

  if (current_display !=0) {
      SDL_Log("Error : could not get display mode : %s", SDL_GetError());
  }
  else {
    display_width=current.w/5;
    display_height=current.h/5;
  }

  /* Création des fenêtres de haut-gauche à bas-droite */
  window_d1 = SDL_CreateWindow(
      "Fenêtre d1",                    
      0, 0,                              
      display_width, display_height, 
      SDL_WINDOW_RESIZABLE);     

  if (window_d1 == NULL) {
    SDL_Log("Error : SDL window d1 creation - %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }


  window_d2 = SDL_CreateWindow(
      "Fenêtre d2",
      display_width, display_height,      
      display_width, display_height,   
      SDL_WINDOW_RESIZABLE);   

  if (window_d2 == NULL) {
    SDL_Log("Error : SDL window d2 creation - %s\n", SDL_GetError()); 
    SDL_DestroyWindow(window_d1);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }


  window_d3 = SDL_CreateWindow(
      "Fenêtre d3",
      2*display_width, 2*display_height,      
      display_width, display_height,   
      SDL_WINDOW_RESIZABLE);   

  if (window_d3 == NULL) {
    SDL_Log("Error : SDL window d3 creation - %s\n", SDL_GetError()); 
    SDL_DestroyWindow(window_d2);
    SDL_DestroyWindow(window_d1);    
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  

  window_d4 = SDL_CreateWindow(
      "Fenêtre d4",
      3*display_width, 3*display_height,      
      display_width, display_height,   
      SDL_WINDOW_RESIZABLE);   

  if (window_d4 == NULL) {
    SDL_Log("Error : SDL window d4 creation - %s\n", SDL_GetError());
    SDL_DestroyWindow(window_d3);     
    SDL_DestroyWindow(window_d2);
    SDL_DestroyWindow(window_d1);    
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  

  window_d5 = SDL_CreateWindow(
      "Fenêtre d5",
      4*display_width, 4*display_height,      
      display_width, display_height,   
      SDL_WINDOW_RESIZABLE);   

  if (window_d5 == NULL) {
    SDL_Log("Error : SDL window d5 creation - %s\n", SDL_GetError());
    SDL_DestroyWindow(window_d4);  
    SDL_DestroyWindow(window_d3);     
    SDL_DestroyWindow(window_d2);
    SDL_DestroyWindow(window_d1);    
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  
  /* Création des fenêtres de bas-droite à haut-gauche */
  window_g1 = SDL_CreateWindow(
      "Fenêtre g1",                    
      0, 4*display_height,                              
      display_width, display_height, 
      SDL_WINDOW_RESIZABLE);     

  if (window_g1 == NULL) {
    SDL_Log("Error : SDL window g1 creation - %s\n", SDL_GetError());
    SDL_DestroyWindow(window_d5);
    SDL_DestroyWindow(window_d4);  
    SDL_DestroyWindow(window_d3);     
    SDL_DestroyWindow(window_d2);
    SDL_DestroyWindow(window_d1);     
    SDL_Quit();
    exit(EXIT_FAILURE);
  }


  window_g2 = SDL_CreateWindow(
      "Fenêtre g2",
      display_width, 3*display_height,      
      display_width, display_height,   
      SDL_WINDOW_RESIZABLE);   

  if (window_g2 == NULL) {
    SDL_Log("Error : SDL window g2 creation - %s\n", SDL_GetError()); 
    SDL_DestroyWindow(window_g1);
    SDL_DestroyWindow(window_d5);
    SDL_DestroyWindow(window_d4);  
    SDL_DestroyWindow(window_d3);     
    SDL_DestroyWindow(window_d2);
    SDL_DestroyWindow(window_d1); 
    SDL_Quit();
    exit(EXIT_FAILURE);
  }


  window_g3 = SDL_CreateWindow(
      "Fenêtre g3",
      2*display_width, 2*display_height,      
      display_width, display_height,   
      SDL_WINDOW_RESIZABLE);   

  if (window_g3 == NULL) {
    SDL_Log("Error : SDL window g3 creation - %s\n", SDL_GetError()); 
    SDL_DestroyWindow(window_g2);
    SDL_DestroyWindow(window_g1);
    SDL_DestroyWindow(window_d5);
    SDL_DestroyWindow(window_d4);  
    SDL_DestroyWindow(window_d3);     
    SDL_DestroyWindow(window_d2);
    SDL_DestroyWindow(window_d1);    
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  

  window_g4 = SDL_CreateWindow(
      "Fenêtre g4",
      3*display_width, display_height,      
      display_width, display_height,   
      SDL_WINDOW_RESIZABLE);   

  if (window_g4 == NULL) {
    SDL_Log("Error : SDL window g4 creation - %s\n", SDL_GetError());
    SDL_DestroyWindow(window_g3); 
    SDL_DestroyWindow(window_g2);
    SDL_DestroyWindow(window_g1);
    SDL_DestroyWindow(window_d5);
    SDL_DestroyWindow(window_d4);  
    SDL_DestroyWindow(window_d3);     
    SDL_DestroyWindow(window_d2);
    SDL_DestroyWindow(window_d1);  
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  

  window_g5 = SDL_CreateWindow(
      "Fenêtre g5",
      4*display_width, 0,      
      display_width, display_height,   
      SDL_WINDOW_RESIZABLE);   

  if (window_g5 == NULL) {
    SDL_Log("Error : SDL window g5 creation - %s\n", SDL_GetError());
    SDL_DestroyWindow(window_g4);
    SDL_DestroyWindow(window_g3); 
    SDL_DestroyWindow(window_g2);
    SDL_DestroyWindow(window_g1);
    SDL_DestroyWindow(window_d5);
    SDL_DestroyWindow(window_d4);  
    SDL_DestroyWindow(window_d3);     
    SDL_DestroyWindow(window_d2);
    SDL_DestroyWindow(window_d1);    
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  /* Normalement, on devrait ici remplir les fenêtres... */
  SDL_Delay(20000);                           // Pause exprimée  en ms

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */
    SDL_DestroyWindow(window_g5);
    SDL_DestroyWindow(window_g4);
    SDL_DestroyWindow(window_g3); 
    SDL_DestroyWindow(window_g2);
    SDL_DestroyWindow(window_g1);
    SDL_DestroyWindow(window_d5);
    SDL_DestroyWindow(window_d4);  
    SDL_DestroyWindow(window_d3);     
    SDL_DestroyWindow(window_d2);
    SDL_DestroyWindow(window_d1);   

  SDL_Quit();
  return 0;
}
