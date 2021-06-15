#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

#define M 50
#define N 30

int survie[9] = {0, 0, 1, 1, 0, 0, 0, 0, 0};
int naissance[9] = {0, 0, 0, 1, 0, 0, 0, 0};
int grille_jeu[N][M];
int grille_voisin[N][M];

void end_sdl(char ok,
                  char const* msg,
                  SDL_Window* window,
                  SDL_Renderer* renderer) {
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

//prend en parametre i et j et les modifie si ils sortent du tableau
void tore(int * i, int * j){
       if(*i == -1){
              *i = N-1;
       }
       else{
              if(*i == N){
                     *i = 0;
              }
       }

       if(*j == -1){
              *j = M-1;
       }
       else{
              if(*j == M){
                     *j = 0;
              }
       }
}

//permet de compter le nombre de voisin d'une cellule d'adresse i et j
void iter_nbr_voisin(){
       int    voisin_i,
              voisin_j,
              iter_i,
              iter_j,
              i,
              j;
       
       for(i=0; i<N; i++){
              for(j=0; j<M; j++){
                     grille_voisin[i][j] = 0 - grille_jeu[i][j];
                     for(iter_i = -1; iter_i < 2; iter_i++){
                            for(iter_j = -1; iter_j < 2; iter_j++){
                                   voisin_i = i+iter_i;
                                   voisin_j = j+iter_j;
                                   tore(&voisin_i, &voisin_j);

                                   grille_voisin[i][j] += grille_jeu[voisin_i][voisin_j];
                            }
                     }
              }
       }
}

//effectue une iteration du jeu de la vie (gere les naissances et les morts)
void iter_jeu_vie(SDL_Renderer * renderer, SDL_DisplayMode screen){
       int    i,
              j;

       SDL_Rect individu;
       individu.w = screen.w/M;
	individu.h = screen.h/N;

        for(i=0; i<N; i++){
               for(j=0; j<M; j++){
                      individu.x = j*individu.w;
                      individu.y = i*individu.h;

                     if(grille_jeu[i][j] == 1)
                            grille_jeu[i][j] = survie[grille_voisin[i][j]];
                     else
                            grille_jeu[i][j] = naissance[grille_voisin[i][j]];

                     if(grille_jeu[i][j]){
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                     }
                     else{
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                     }
                     SDL_RenderFillRect(renderer, &individu);
               }
        }       
}

void init_jeu(){
       int i, j;
       for(i=0; i<N; i++){
              for(j=0; j<M; j++){
                     grille_jeu[i][j] = 0;
              }
       }
       //carre
       /*grille_jeu[10][10] = 1;
       grille_jeu[10][11] = 1;
       grille_jeu[11][10] = 1;
       grille_jeu[11][11] = 1;*/

       //grenouille
       grille_jeu[2][2] = 1;
       grille_jeu[2][3] = 1;
       grille_jeu[2][4] = 1;
       grille_jeu[3][1] = 1;
       grille_jeu[3][2] = 1;
       grille_jeu[3][3] = 1;

       //glider
       grille_jeu[8][6] = 1;
       grille_jeu[9][7] = 1;
       grille_jeu[10][5] = 1;
       grille_jeu[10][6] = 1;
       grille_jeu[10][7] = 1;
}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	int quit = 0;
	SDL_Event event;
       SDL_DisplayMode screen;

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;

       if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);
       SDL_GetCurrentDisplayMode(0, &screen);

	window = SDL_CreateWindow(
		"Jeu de la vie pas encore très vivant",
		SDL_WINDOWPOS_CENTERED,
              SDL_WINDOWPOS_CENTERED, 
		screen.w,
              screen.h,
		0);

	if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

       init_jeu();
       while (!quit){
              SDL_PollEvent(&event);

              iter_nbr_voisin();
              iter_jeu_vie(renderer, screen);
              SDL_RenderPresent(renderer);
              SDL_Delay(100);

              if (event.type == SDL_QUIT)
                     quit = 1;
       }

       SDL_DestroyRenderer(renderer);
       SDL_DestroyWindow(window);
	return 0;
}