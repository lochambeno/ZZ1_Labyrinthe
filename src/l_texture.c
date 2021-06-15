#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#define M 24
#define N 18

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

SDL_Texture * charger_texture(char* nom_fichier, SDL_Window* window, SDL_Renderer* renderer){
	SDL_Surface * mon_image = NULL;
	SDL_Texture * ma_texture = NULL;

	mon_image = IMG_Load(nom_fichier);
	if (mon_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

	ma_texture = SDL_CreateTextureFromSurface(renderer, mon_image);
	SDL_FreeSurface(mon_image); //pas besoin de SDL_Surface pour la suite
	if (ma_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

	return ma_texture;
}

void afficher_eau(SDL_Texture * ma_texture, SDL_Window * window, SDL_Renderer * renderer){
	int i, j, zoom;
	SDL_Rect	source = {0},
				window_dimension = {0},
				destination = {0};

	SDL_GetWindowSize(
         window, &window_dimension.w,
         &window_dimension.h);			//--> dim fenetre

	source.x = 551;
	source.y = 26;
	source.h = 23;
	source.w = 23;

	zoom = 2;
	destination.h = source.h*zoom;
	destination.w = source.w*zoom;
	
	for(i=0; i<M; i++){
		for(j=0; j<N; j++){
			destination.x = i*destination.h;
			destination.y = j*destination.w;

			SDL_RenderCopy(renderer, ma_texture, &source, &destination);
		}
	}
}

void afficher_terre(SDL_Texture * ma_texture, SDL_Window * window, SDL_Renderer * renderer){
	int i, j, zoom;
	SDL_Rect	source = {0},
				window_dimension = {0},
				destination = {0};

	SDL_GetWindowSize(
         window, &window_dimension.w,
         &window_dimension.h);			//--> dim fenetre

	source.x = 76;
	source.y = 1;
	source.h = 23;
	source.w = 23;

	zoom = 2;
	destination.h = source.h*zoom;
	destination.w = source.w*zoom;
	
	//insere l'angle de terre
	destination.x = 0;
	destination.y = 8*destination.w;
	SDL_RenderCopy(renderer, ma_texture, &source, &destination);

	//insere la ligne de terre		
	source.x = 101;
	for(i=1; i<M; i++){
		destination.x = i*destination.h;
		SDL_RenderCopy(renderer, ma_texture, &source, &destination);
	}

	//insere la partie gauche de la ligne centrale
	source.x = 76;
	source.y = 26;

	destination.x = 0;
	destination.y = 9*destination.w;
	SDL_RenderCopy(renderer, ma_texture, &source, &destination);

	//insere la ligne centrale
	source.x = 101;
	for(i=1; i<M; i++){
		destination.x = i*destination.h;
		SDL_RenderCopy(renderer, ma_texture, &source, &destination);
	}

	//insere la partie gauche de la ligne du dessous
	source.x = 76;
	source.y = 51;

	destination.x = 0;
	destination.y = 10*destination.w;
	SDL_RenderCopy(renderer, ma_texture, &source, &destination);

	//insere la ligne centrale
	source.x = 101;
	for(i=1; i<M; i++){
		destination.x = i*destination.h;
		SDL_RenderCopy(renderer, ma_texture, &source, &destination);
	}	
}

void anim_personnage();

int main(){
	int quit = 0;
	SDL_Event event;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Texture * texture = NULL;

	//SDL_DisplayMode screen;

	if(SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

	//SDL_GetCurrentDisplayMode(0, &screen);

	window = SDL_CreateWindow(
		"Test_Texture",
		SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
		1080,
        720,
		0);

	if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

	texture = charger_texture("./src/images/sprite-murs1.png", window, renderer);
	afficher_eau(texture, window, renderer);
	afficher_terre(texture, window, renderer);
	SDL_RenderPresent(renderer);

	while (!quit){
    	SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
            quit = 1;
    }

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();

	return 0;
}