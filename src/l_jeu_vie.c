#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

#define M 50
#define N 30

int survie[9] = {0, 0, 1, 1, 0, 0, 0, 0, 0};
int naissance[9] = {0, 0, 0, 1, 0, 0, 0, 0};

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
int nbr_voisin(int ** tableau, int i, int j){
       int    voisin = 0;
       int    voisin_i,
              voisin_j,
              iter_i,
              iter_j;
              
       for(iter_i = -1; iter_i < 2; iter_i++){
              for(iter_j = -1; iter_j < 2; iter_j++){
                     if(!(iter_j == 0 && iter_i == 0)){
                            voisin_i = i+iter_i;
                            voisin_j = j+iter_j;
                            tore(&voisin_i, &voisin_j);

                            voisin += tableau[voisin_i][voisin_j];
                     }
              }
       }
       return voisin;
}

//effectue une iteration du jeu de la vie (gere les naissances et les morts)
void iter_jeu_vie(int *** tableau, SDL_Renderer * renderer, SDL_DisplayMode screen){
       int    i,
              j;

       SDL_Rect individu;
       individu.w = screen.w/M;
	individu.h = screen.h/N;

        for(i=0; i<N; i++){
               for(j=0; j<M; j++){
                      individu.x = j*individu.w;
                      individu.y = i*individu.h;

                     if(*tableau[i][j])
                            *tableau[i][j] = survie[nbr_voisin(*tableau, i, j)];
                     else
                            *tableau[i][j] = naissance[nbr_voisin(*tableau, i, j)];

                     if(*tableau[i][j]){
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                     }
                     else{
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                     }
                     SDL_RenderFillRect(renderer, &individu);
               }
        }       
}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;
       int i, j;

	int quit = 0;
	SDL_Event event;
       SDL_DisplayMode screen;

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;

       int ** tableau = (int**) malloc(sizeof(int*)*N);
       for(i=0; i<N; i++){
              tableau[i] = (int*) malloc(sizeof(int*)*M);
              for(j=0; j<M; j++){
                     tableau[i][j] = 0;
              }
       }

       if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);
       SDL_GetCurrentDisplayMode(0, &screen);

	window = SDL_CreateWindow(
		"Animation",
		SDL_WINDOWPOS_CENTERED,
              SDL_WINDOWPOS_CENTERED, 
		screen.w,
              screen.h,
		0);

	if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

       while (!quit){
              SDL_PollEvent(&event);

              iter_jeu_vie(&tableau, renderer, screen);
              SDL_RenderPresent(renderer);

              if (event.type == SDL_QUIT)
                     quit = 1;
       }

	return 0;
}