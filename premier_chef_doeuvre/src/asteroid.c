#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL_image.h>

void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
  char const* msg,                                    // message à afficher
  SDL_Window* window,                                 // fenêtre à fermer
  SDL_Renderer* renderer) 
  {                           // renderer à fermer
  char msg_formated[255];                                         
  int l;                                                          

  if (!ok) 
  {                                                      
    strncpy(msg_formated, msg, 250);                                 
    l = strlen(msg_formated);                                        
    strcpy(msg_formated + l, " : %s\n");                     

    SDL_Log(msg_formated, SDL_GetError());                   
  }                                                               

  if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
  if (window != NULL)   SDL_DestroyWindow(window);                                        

  SDL_Quit();                                                     

  if (!ok) 
  {                                                      
    exit(EXIT_FAILURE);                                              
  } 
  }


SDL_Rect creer_asteroid(int x, int y) 
{                                   
  SDL_Rect rectangle;
 

  rectangle.x = x;                                                   
  rectangle.y = y;                                                    
  rectangle.w = 50;                                                  
  rectangle.h = 50;                                                  


  return rectangle;
}



void deplacement(SDL_Rect* rectangle, int pas)
{
    (*rectangle).y += pas;
}


void afficher_ast(SDL_Texture* ast_texture,
                         SDL_Rect* rectangle, 
                         SDL_Renderer* renderer) 
{
    SDL_Rect source = {0};

    SDL_QueryTexture(ast_texture, NULL, NULL, &source.w, &source.h);
    SDL_RenderCopy(renderer, ast_texture, &source, rectangle);
}


void afficher_fond(SDL_Texture *fond_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(fond_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, fond_texture,
                 &source,
                 &destination);                 // Création de l'élément à afficher
  SDL_RenderPresent(renderer);                  // Affichage

}         








int main(int argc, char **argv) 
{
	(void)argc;
	(void)argv;

    int hauteur;


  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  SDL_DisplayMode screen;


/*********************************************************************************************************************/  
/*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

  SDL_GetCurrentDisplayMode(0, &screen);


  /* Création de la fenêtre */
  window = SDL_CreateWindow("Animation",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screen.w * 1,
                            screen.h * 1,
                            SDL_WINDOW_OPENGL);
  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  /* Création du renderer */
    renderer = SDL_CreateRenderer(
    window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

  /*                                      On dessine dans le renderer                                             */


  SDL_DisplayMode display;

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }

  if (SDL_GetCurrentDisplayMode(0, &display) != 0)
    printf("ERROR\n");


  hauteur = display.h;

    SDL_Texture* ast_texture = NULL,
                * fond_texture = NULL;

SDL_Rect rectangle = creer_asteroid(0, 0);
  fond_texture = IMG_LoadTexture(renderer, "Space01.png");   
                                           
if (fond_texture == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);
    ast_texture = IMG_LoadTexture(renderer, "Asteroids.png");   
                                           
                                            
    if (ast_texture == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);
    
    
while (rectangle.y<hauteur)
{
    deplacement(&rectangle,10);
    SDL_Delay(50);
    afficher_fond(fond_texture, window, renderer);
    afficher_ast(ast_texture, &rectangle, renderer);
    SDL_RenderPresent(renderer);

}


    IMG_Quit();


  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}

