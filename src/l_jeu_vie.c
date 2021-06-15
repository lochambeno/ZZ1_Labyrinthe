#include <SDL2/SDL.h>
#include <stdio.h>

#define N 50
#define M 30

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