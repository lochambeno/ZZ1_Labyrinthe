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
              *i = N;
       }
       else{
              if(*i == N+1){
                     *i = 0;
              }
       }

       if(*j == -1){
              *j = M;
       }
       else{
              if(*j == M+1){
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

void iter_jeu_vie(int ** tableau){
       int    i,
              j;

       
}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	int quit = 1;
	SDL_Event event;

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;



       while (!quit){
    	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)
            quit = 1;

    }

	return 0;
}