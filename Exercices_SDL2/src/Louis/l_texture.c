#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#define M 9
#define N 6

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

	SDL_QueryTexture(ma_texture,           // Récupération des dimensions de l'image
                        NULL, NULL,
                        &source.w, &source.h);

	source.h = source.h/8;
	source.w = source.w/12;
	source.x = 0;
	source.y = 3*source.h;

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
	int i, zoom;
	SDL_Rect	source = {0},
				window_dimension = {0},
				destination = {0};

	SDL_GetWindowSize(
         window, &window_dimension.w,
         &window_dimension.h);			//--> dim fenetre

	SDL_QueryTexture(ma_texture,           // Récupération des dimensions de l'image
                        NULL, NULL,
                        &source.w, &source.h);

	source.h = source.h/8;
	source.w = source.w/12;

	source.x = 0;
	source.y = source.w;

	zoom = 1;
	destination.h = source.h*zoom;
	destination.w = source.w*zoom;
	
	/*//insere l'angle de terre
	destination.x = 0;
	destination.y = 2*destination.w;
	SDL_RenderCopy(renderer, ma_texture, &source, &destination);

	//insere la ligne de terre		
	source.x = 6*source.w;
	for(i=1; i<M; i++){
		destination.x = i*destination.h;
		SDL_RenderCopy(renderer, ma_texture, &source, &destination);
	}

	//insere la partie gauche de la ligne centrale
	source.x = 5*source.w;
	source.y = source.h;

	destination.x = 0;
	destination.y = 3*destination.h;
	SDL_RenderCopy(renderer, ma_texture, &source, &destination);*/

	//insere la ligne centrale
	destination.y = 3*destination.h;
	for(i=0; i<M; i++){
		destination.x = i*destination.h;
		SDL_RenderCopy(renderer, ma_texture, &source, &destination);
	}

	/*//insere la partie gauche de la ligne du dessous
	source.x = 5*source.w;
	source.y = 2*source.h;

	destination.x = 0;
	destination.y = 14*destination.w;
	SDL_RenderCopy(renderer, ma_texture, &source, &destination);

	//insere la ligne centrale
	source.x = 6*source.w;
	for(i=1; i<M; i++){
		destination.x = i*destination.h;
		SDL_RenderCopy(renderer, ma_texture, &source, &destination);
	}*/
}

void anim_personnage(	SDL_Texture * bg_texture, 
						SDL_Texture * ma_texture,
						SDL_Window * window,
						SDL_Renderer * renderer,
						int * i,
						int * position){
	
	SDL_Rect	source = {0},                             // Rectangle définissant la zone de la texture à récupérer
    			window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
    			destination = {0};

	SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
                    &window_dimensions.w, 
                    &window_dimensions.h);
	SDL_QueryTexture(ma_texture, NULL, NULL,    // Récupération des dimensions de l'image
                   &source.w, &source.h);

	int 	texture_h = source.h/4,
			texture_w = source.w/8;
	SDL_Rect vignettes[8];

	int j;
	for(j=0; j<8; ++j){
		vignettes[j].x = j*texture_w;
		vignettes[j].y = 3*texture_h;
		vignettes[j].w = texture_w;
		vignettes[j].h = texture_h;
	}
	
	destination.x = 23;
	destination.y = 8*46; //46 = taille d'une tile
	destination.w = 2*texture_w;
	destination.h = 2*texture_h;

	afficher_eau(bg_texture, window, renderer);
	afficher_terre(bg_texture, window, renderer);
	destination.x += 2*(*position);

	SDL_RenderCopy(renderer, ma_texture, &vignettes[*i], &destination);
	*i = (*i+1)%8;
	*position += 4;
	SDL_RenderPresent(renderer);
	SDL_Delay(100);
	
}

int main(){
	int quit = 0;
	int i = 0,
		position = 16;
	SDL_Event event;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Texture * bg_texture = NULL,
				* char_texture = NULL;

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

	bg_texture = charger_texture("./../images/roadTextures_tilesheet@2.png", window, renderer);
	char_texture = charger_texture("./../images/spritemap-v9-greenpants.png", window, renderer);

	while (!quit){
    	SDL_PollEvent(&event);
		anim_personnage(bg_texture, char_texture, window, renderer, &i, &position);

		if (event.type == SDL_QUIT)
            quit = 1;
    }

	SDL_DestroyTexture(char_texture);
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();

	return 0;
}
