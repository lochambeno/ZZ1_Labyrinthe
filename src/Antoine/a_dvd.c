#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/

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

  SDL_Quit();                                                     

  if (!ok) {                                                      
         exit(EXIT_FAILURE);                                              
  }                                                               
}                                                                 

void draw(SDL_Renderer* renderer, int x, int y, int w, int h) {                                   // Je pense que vous allez faire moins laid :)
  SDL_Rect rectangle;                                             

  SDL_SetRenderDrawColor(renderer,                                
                              255, 0, 255,                               // mode Red, Green, Blue (tous dans 0..255)
                              255);                                   // 0 = transparent ; 255 = opaque
  rectangle.x = x;                                                    // x haut gauche du rectangle
  rectangle.y = y;                                                    // y haut gauche du rectangle
  rectangle.w = w;                                                  // sa largeur (w = width)
  rectangle.h = h;                                                  // sa hauteur (h = height)

  SDL_RenderFillRect(renderer, &rectangle);

  SDL_RenderPresent(renderer);                                        // affichage
  SDL_Delay(10);
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
  SDL_RenderClear(renderer);
}

void move(SDL_Renderer* renderer, int *x, int *y, int w, int h, int screen_width, int screen_height, int *haut, int *droite) {
    if (*haut) {
        if (*droite) {
            while (*x+w<screen_width && *y>0) {
                draw(renderer, *x, *y, w, h);
                ++*x;
                --*y;
            }
            if (*x+w == screen_width) *droite=0;
        }
        else {
            while (*x>0 && *y>0) {
                draw(renderer, *x, *y, w, h);
                --*x;
                --*y;
            }
            if (*x==0) *droite=1;
        }
        if (*y==0) *haut=0;
    }
    else {
        if (*droite) {
            while (*x+w<screen_width && *y+h<screen_height) {
                draw(renderer, *x, *y, w, h);
                ++*x;
                ++*y;
            }
            if (*x+w == screen_width) *droite=0;
        }
        else {
            while (*x>0 && *y+h<screen_height) {
                draw(renderer, *x, *y, w, h);
                --*x;
                ++*y;
            }
            if (*x==0) *droite=1;
        }
        if (*y+h==screen_height) *haut=1;
    }
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  int x=0, y=0, w=400, h=200, haut=0, droite=1, i=0;
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  SDL_DisplayMode screen;

/*********************************************************************************************************************/  
/*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w,
              screen.h);

  /* Création de la fenêtre */
  window = SDL_CreateWindow("Premier dessin",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, screen.w,
                            screen.h,
                            SDL_WINDOW_OPENGL);
  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  /* Création du renderer */
  renderer = SDL_CreateRenderer(
           window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

  /*********************************************************************************************************************/
  /*                                     On dessine dans le renderer                                                   */
  for (i=0;i<10;++i) {
    move(renderer, &x, &y, w, h, screen.w, screen.h, &haut, &droite);
  }

  /*********************************************************************************************************************/
  /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}