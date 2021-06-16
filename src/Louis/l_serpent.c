#include <SDL2/SDL.h>
#include <stdio.h>

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

//fonction permettant le deplacement du rectangle
void mv_rect(int *h, int* v, SDL_Rect * rect, int win_w, int win_h){
	if(*v == 0 && rect->x + 100 <= win_w){
		rect->x = rect->x + 1;
	}
	else{
			*v = 1;
	}

	if(*v == 1 && rect->x > 0){
		rect->x = rect->x - 1;
	}
	else{
		*v = 0;
	}

	if(*h == 0 && rect->y + 100 <= win_h){
		rect->y = rect->y + 1;
	}
	else{
		*h = 1;
	}

	if(*h == 1 && rect->y > 0){
		rect->y = rect->y - 1;
	}
	else{
		*h = 0;
	}

}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	int win_h;
	int win_w;

	SDL_Event event;
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;

	SDL_DisplayMode screen;

	SDL_Rect rect;
	SDL_Rect rect2;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

	SDL_GetCurrentDisplayMode(0, &screen);

	window = SDL_CreateWindow(
		"Animation",
		SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
		screen.w * 0.66,
        screen.h * 0.66,
		0);

	if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

	//on initialise le rectangle
	SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
	rect.x = 0;
	rect.y = 0;
	rect.w = 100;
	rect.h = 100;

	SDL_RenderFillRect(renderer, &rect);		
	SDL_RenderPresent(renderer);

	SDL_GetWindowSize(window, &win_w, &win_h);

	rect2.x = 0;
	rect2.y = 0;
	rect2.w = win_w;
	rect2.h = win_h;

	int quit = 0;
	int d = 0, v = 0;
	while (!quit){
    	SDL_PollEvent(&event);
		mv_rect(&d, &v, &rect, win_w, win_h);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect2);

		SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);

        if (event.type == SDL_QUIT)
            quit = 1;

    }
	return 0;
}

