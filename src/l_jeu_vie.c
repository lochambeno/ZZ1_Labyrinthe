#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

#define M 144
#define N 90

// Regles de base
int survie[9] = {0, 0, 1, 1, 0, 0, 0, 0, 0};
int naissance[9] = {0, 0, 0, 1, 0, 0, 0, 0};


/*// Mazetrice
int survie[9] = {0, 1, 1, 1, 1, 0, 0, 0, 0};
int naissance[9] = {0, 0, 0, 1, 0, 0, 0, 0};
*/

/*// Maze
int survie[9] = {0, 1, 1, 1, 1, 1, 0, 0, 0};
int naissance[9] = {0, 0, 0, 1, 0, 0, 0, 0};*/

/*// Coral
int survie[9] = {0, 0, 0, 0, 1, 1, 1, 1, 1};
int naissance[9] = {0, 0, 0, 1, 0, 0, 0, 0};*/

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

void afficher_vie(SDL_Renderer * renderer, SDL_DisplayMode screen){
       int i, j;
       SDL_Rect individu;
       individu.w = screen.w/M;
	individu.h = screen.h/N;

       for(i=0; i<N; i++){
              for(j=0; j<M; j++){
                     individu.x = j*individu.w;
                     individu.y = i*individu.h;

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

//effectue une iteration du jeu de la vie (gere les naissances et les morts)
void iter_jeu_vie(){
       int    i,
              j;

        for(i=0; i<N; i++){
               for(j=0; j<M; j++){

                     if(grille_jeu[i][j] == 1)
                            grille_jeu[i][j] = survie[grille_voisin[i][j]];
                     else
                            grille_jeu[i][j] = naissance[grille_voisin[i][j]];
               }
        }       
}

void init_glider(int i, int j){
       grille_jeu[i][j+1] = 1;
       grille_jeu[i+1][j] = 1;
       grille_jeu[i+2][j] = 1;
       grille_jeu[i+2][j+1] = 1;
       grille_jeu[i+2][j+2] = 1;
}

void init_grenouille(int i, int j){
       grille_jeu[i][j+1] = 1;
       grille_jeu[i][j+2] = 1;
       grille_jeu[i][j+3] = 1;
       grille_jeu[i+1][j] = 1;
       grille_jeu[i+1][j+1] = 1;
       grille_jeu[i+1][j+2] = 1;
}

void init_canon(int i, int j){
       //carre de gauche
       grille_jeu[i+4][j] = 1;
       grille_jeu[i+5][j] = 1;
       grille_jeu[i+4][j+1] = 1;
       grille_jeu[i+5][j+1] = 1;
       //carre de droite
       grille_jeu[i+2][j+35] = 1;
       grille_jeu[i+2][j+34] = 1;
       grille_jeu[i+3][j+35] = 1;
       grille_jeu[i+3][j+34] = 1;
       //truc de gauche
       grille_jeu[i+2][j+12] = 1;       grille_jeu[i+2][j+13] = 1;
       grille_jeu[i+3][j+11] = 1;       grille_jeu[i+3][j+15] = 1;
       grille_jeu[i+4][j+10] = 1;       grille_jeu[i+4][j+16] = 1;
       grille_jeu[i+5][j+10] = 1;       grille_jeu[i+5][j+14] = 1; 
       grille_jeu[i+5][j+16] = 1;       grille_jeu[i+5][j+17] = 1;
       grille_jeu[i+6][j+10] = 1;       grille_jeu[i+6][j+16] = 1;
       grille_jeu[i+7][j+11] = 1;       grille_jeu[i+7][j+15] = 1;
       grille_jeu[i+8][j+12] = 1;       grille_jeu[i+8][j+13] = 1;     
       //truc de droite
       grille_jeu[i][j+24] = 1;         grille_jeu[i+1][j+24] = 1;
       grille_jeu[i+1][j+22] = 1;       grille_jeu[i+2][j+21] = 1;
       grille_jeu[i+2][j+20] = 1;       grille_jeu[i+3][j+21] = 1;
       grille_jeu[i+3][j+20] = 1;       grille_jeu[i+4][j+21] = 1;
       grille_jeu[i+4][j+20] = 1;       grille_jeu[i+5][j+22] = 1;
       grille_jeu[i+5][j+24] = 1;       grille_jeu[i+6][j+24] = 1;
}

void ajouter_vie(int x, int y, SDL_DisplayMode screen){
       int    x_case, y_case;

       x_case = x/(screen.w/M);
       y_case = y/(screen.h/N);

       grille_jeu[y_case][x_case] = 1;
}

void retirer_vie(int x, int y, SDL_DisplayMode screen){
       int    x_case, y_case;

       x_case = x/(screen.w/M);
       y_case = y/(screen.h/N);

       grille_jeu[y_case][x_case] = 0;
}

void init_jeu(){
       int i, j;
       for(i=0; i<N; i++){
              for(j=0; j<M; j++){
                     grille_jeu[i][j] = 0;
              }
       }
       
}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	int    quit = 0,
              pause = 0,
              mouse_x = 0,
              mouse_y = 0;

       SDL_DisplayMode screen;
       SDL_Event event;
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
       while (!quit){
              
              while(!quit && SDL_PollEvent(&event)){
                     switch(event.type){
                     case SDL_QUIT:
                            quit = 1;
                            break;

                     case SDL_KEYDOWN:
                            switch(event.key.keysym.sym){
                            case SDLK_SPACE:
                            case SDLK_p:
                                   pause = !pause;
                                   break;

                            case SDLK_ESCAPE:
                            case SDLK_q:
                                   quit = 1;
                                   break;

                            case SDLK_c:
                                   init_canon(0, 0);
                                   break;

                            case SDLK_r:
                                   init_jeu();
                                   break;

                            default:
                                   break;
                            }
                            break;

                     case SDL_MOUSEBUTTONDOWN:
                            if (SDL_GetMouseState(&mouse_x, &mouse_y) & SDL_BUTTON(SDL_BUTTON_LEFT) )
                                   ajouter_vie(mouse_x, mouse_y, screen);
                            else
                                   retirer_vie(mouse_x, mouse_y, screen);
                            break;
                     default:
                            break;
                     }
              }
              
              if(!pause){
                     iter_nbr_voisin();
                     iter_jeu_vie();
              }
              afficher_vie(renderer, screen);
              SDL_RenderPresent(renderer);
              SDL_Delay(50);
       }

       SDL_DestroyRenderer(renderer);
       SDL_DestroyWindow(window);
       SDL_Quit();
	return 0;
}