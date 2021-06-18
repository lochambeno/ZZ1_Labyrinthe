#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/

typedef struct couleur {
    int R;
    int G;
    int B;
} couleur_t;

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

void draw(SDL_Renderer* renderer, int x, int y, int w, int h, couleur_t couleur) {                                   // Je pense que vous allez faire moins laid :)
  SDL_Rect rectangle;                                             

  SDL_SetRenderDrawColor(renderer,                                
                              couleur.R, couleur.G, couleur.B,                               // mode Red, Green, Blue (tous dans 0..255)
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

void move(SDL_Renderer* renderer, int *x, int *y, int w, int h, SDL_DisplayMode screen, int *haut, int *droite, couleur_t couleur) {
    if (*haut) {
        if (*droite) {
            while (*x+w<screen.w && *y>0) {
                draw(renderer, *x, *y, w, h, couleur);
                *x+=5;
                *y-=5;
            }
            if (*x+w >= screen.w) *droite=0;
        }
        else {
            while (*x>0 && *y>0) {
                draw(renderer, *x, *y, w, h, couleur);
                *x-=5;
                *y-=5;
            }
            if (*x<=0) *droite=1;
        }
        if (*y<=0) *haut=0;
    }
    else {
        if (*droite) {
            while (*x+w<screen.w && *y+h<screen.h) {
                draw(renderer, *x, *y, w, h, couleur);
                *x+=5;
                *y+=5;
            }
            if (*x+w >= screen.w) *droite=0;
        }
        else {
            while (*x>0 && *y+h<screen.h) {
                draw(renderer, *x, *y, w, h, couleur);
                *x-=5;
                *y+=5;
            }
            if (*x<=0) *droite=1;
        }
        if (*y+h>=screen.h) *haut=1;
    }
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    srand(time(NULL));

    int x=0, y=0, w=400, h=200, haut=0, droite=1, i=0;
    couleur_t couleur;
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
        couleur.R=rand()%256;
        couleur.G=rand()%256;
        couleur.B=rand()%256;
        move(renderer, &x, &y, w, h, screen, &haut, &droite, couleur);
    }

    SDL_bool
        program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
        paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause
    while (program_on) {                              // La boucle des évènements
        SDL_Event event;                                // Evènement à traiter

        while (program_on && SDL_PollEvent(&event)) {   // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                                        // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type) {                         // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
                program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
                break;
            case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée
                                                        // comme la valeur du type est SDL_Keydown, dans la pratie 'union' de
                                                        // l'event, plusieurs champs deviennent pertinents   
                switch (event.key.keysym.sym) {             // la touche appuyée est ...
                case SDLK_p:                                // 'p'
                case SDLK_SPACE:                            // 'SPC'
                    paused = !paused;                         // basculement pause/unpause
                    break;
                case SDLK_ESCAPE:                           // 'ESCAPE'  
                case SDLK_q:                                // 'q'
                    program_on = 0;                           // 'escape' ou 'q', d'autres façons de quitter le programme                                     
                    break;
                default:                                    // Une touche appuyée qu'on ne traite pas
                    break;
                }
                break;
            default:                                      // Les évènements qu'on n'a pas envisagé
                break;
        }
    }
    move(renderer, &x, &y, w, h, screen, &haut, &droite, couleur);
    draw(renderer, x, y, w, h, couleur);
    SDL_RenderPresent(renderer);
    //draw_all(renderer, grille, screen.w/M, screen.h/N);          // On redessine
    /*if (!paused) {                                  // Si on n'est pas en pause
        jeu_iter(grille);             // la vie continue... 
    }*/
    SDL_Delay(50);                                  // Petite pause
    }


    /*********************************************************************************************************************/
    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}