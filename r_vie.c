#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#define N 30
#define M 50

int survie[9]={0,0,1,1,0,0,0,0,0};
int naissance[9]={0,0,0,1,0,0,0,0,0};
int tab[N][M];
int grille_voisin[N][M];


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


void donner_vie(int x, int y, SDL_DisplayMode screen)
{
    x = x/(screen.w/M);
    y = y/(screen.h/N);
    tab[y][x] = 1;
}

void supprimer_vie(int x, int y, SDL_DisplayMode screen)
{
    x = x/(screen.w/M);
    y = y/(screen.h/N);
    tab[y][x] = 0;
}


void tore(int* i, int* j)
{
    if(*i==-1)
        *i=N-1;
    if(*i==N)
        *i=0;
    if(*j==-1)
        *j=M-1;
    if(*j==M)
        *j=0;  
}


void affichage_vie(SDL_Renderer* renderer, SDL_DisplayMode screen)
{
    int iter_i, iter_j;
    SDL_Rect individu;
    individu.w = screen.w/M;
	individu.h = screen.h/N;


    for(iter_i=0; iter_i<N; iter_i++)
    {
        for(iter_j=0; iter_j<M; iter_j++)
        {
            individu.x = iter_j*individu.w;
            individu.y = iter_i*individu.h;
            if(tab[iter_i][iter_j])
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            SDL_RenderFillRect(renderer, &individu);    
        }
    }
}



void iter_nbr_voisin(){
       int    voisin_i, voisin_j, iter_i, iter_j, i, j;
       
       for(i=0; i<N; i++)
       {
            for(j=0; j<M; j++)
            {
                grille_voisin[i][j] = 0 - tab[i][j];
                for(iter_i = -1; iter_i < 2; iter_i++)
                {
                    for(iter_j = -1; iter_j < 2; iter_j++)
                    {
                        voisin_i = i+iter_i;
                        voisin_j = j+iter_j;
                        tore(&voisin_i, &voisin_j);

                        grille_voisin[i][j] += tab[voisin_i][voisin_j];
                    }
                }
            }
       }
}

void iter_vie(SDL_DisplayMode screen)
{
    int iter_i, iter_j;

    SDL_Rect individu;
    individu.w = screen.w/M;
	individu.h = screen.h/N;


    for(iter_i=0; iter_i<N; iter_i++)
    {
        for(iter_j=0; iter_j<M; iter_j++)
        {
            individu.x = iter_j*individu.w;
            individu.y = iter_i*individu.h;
            if(tab[iter_i][iter_j])
                tab[iter_i][iter_j]=survie[grille_voisin[iter_i][iter_j]];
            else
                tab[iter_i][iter_j]=naissance[grille_voisin[iter_i][iter_j]];
              
        }
    }
}







void init_jeu()
{
    int i, j;
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            tab[i][j] = 0;
        }
    }
    //carre
    /*tab[10][10] = 1;
    tab[10][11] = 1;
    tab[11][10] = 1;
    tab[11][11] = 1;*/

    //grenouille
    /*tab[2][2] = 1;
    tab[2][3] = 1;
    tab[2][4] = 1;
    tab[3][1] = 1;
    tab[3][2] = 1;
    tab[3][3] = 1;*/

    //glider
    tab[8][6] = 1;
    tab[9][7] = 1;
    tab[10][5] = 1;
    tab[10][6] = 1;
    tab[10][7] = 1;
}

int main(int argc, char **argv) 
{
	(void)argc;
	(void)argv;

    int x, y;

    SDL_DisplayMode screen;

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);
    SDL_GetCurrentDisplayMode(0, &screen);

	window = SDL_CreateWindow(
		"Jeu de la vie",
		SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
		screen.w,
        screen.h,
		0);

	if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    init_jeu();
SDL_bool
  program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
  paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause


while (program_on) 
{                                                 // La boucle des évènements
  SDL_Event event;                                // Evènement à traiter

  while (program_on && SDL_PollEvent(&event)) 
    {                                                 // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas    
                                                  // terminé le programme Défiler l'élément en tête de file dans 'event'
    switch (event.type) 
    {                                            // En fonction de la valeur du type de cet évènement
    case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
        program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
        break;
    case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée
                                                  // comme la valeur du type est SDL_Keydown, dans la pratie 'union' de
                                                  // l'event, plusieurs champs deviennent pertinents   
      switch (event.key.keysym.sym) 
      {                                           // la touche appuyée est ...
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
    case SDL_MOUSEBUTTONDOWN:                     // Click souris   
      if (SDL_GetMouseState(&x, &y) & 
          SDL_BUTTON(SDL_BUTTON_LEFT) ) 
        {                                    // Si c'est un click gauche
            donner_vie(x, y, screen);           // Fonction à éxécuter lors d'un click gauche
        } 
      else if (SDL_GetMouseState(&x, &y) & 
                 SDL_BUTTON(SDL_BUTTON_RIGHT) ) 
            {                                                   // Si c'est un click droit
                supprimer_vie(x, y, screen);           // Fonction à éxécuter lors d'un click droit
            }
      break;
    default:                                      // Les évènements qu'on n'a pas envisagé
      break;
    }
  }
    if(!paused)
    {    
        iter_nbr_voisin();
        iter_vie(screen);
    }
    affichage_vie(renderer, screen);
    SDL_RenderPresent(renderer);
    SDL_Delay(50);
}

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
return 0;
}