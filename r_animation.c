#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

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
}//trop violent il y a des exit alors qu'on est pas dans le main on doit faire sans les exit 

void draw(SDL_Renderer* renderer, int x, int y) 
{                                   
  SDL_Rect rectangle;                                             

  SDL_SetRenderDrawColor(renderer,                                
                              0, 255, 0,                              
                              255);                                   // 0 = transparent ; 255 = opaque
  rectangle.x = x;                                                    // x haut gauche du rectangle
  rectangle.y = y;                                                    // y haut gauche du rectangle
  rectangle.w = 200;                                                  // sa largeur (w = width)
  rectangle.h = 200;                                                  // sa hauteur (h = height)

  SDL_RenderFillRect(renderer, &rectangle);
}


void deplacement(SDL_Renderer* renderer, int* x, int y,int largeur, int pas)
{

    draw(renderer, *x, y);                                                     
    SDL_RenderPresent(renderer);                                        
    SDL_Delay(100); 
    *x=*x+pas;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


}





int main() 
{
    int x=0, y=0, largeur, hauteur;


  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  SDL_DisplayMode screen;


/*********************************************************************************************************************/  
/*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

  SDL_GetCurrentDisplayMode(0, &screen);


  /* Création de la fenêtre */
  window = SDL_CreateWindow("Premier dessin",
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

  largeur = display.w;
  hauteur = display.h;

  while(x+200 <= largeur)
  {
    deplacement(renderer, &x, y, largeur, 20);
  }

  while(x >= 0)
  {
    deplacement(renderer, &x, y, largeur, -20);
  }
    /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}



