#include <SDL2/SDL_image.h>

#define M 24
#define N 18


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

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer )
{
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

void afficher_fond(SDL_Texture * my_texture, SDL_Window * window, SDL_Renderer * renderer){
	int i, j, zoom;
	SDL_Rect	source = {0},
				window_dimension = {0},
				destination = {0};

	SDL_GetWindowSize(
         window, &window_dimension.w,
         &window_dimension.h);			//--> dim fenetre

	source.x = 327;
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

			SDL_RenderCopy(renderer, my_texture, &source, &destination);
		}
	}
}


void animation(SDL_Texture* fond_texture,
                         SDL_Texture* my_texture, 
                         SDL_Window* window,
                         SDL_Renderer* renderer) 
                {
       SDL_Rect 
             source = {0},                    // Rectangle définissant la zone totale de la planche
             window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
             destination = {0},               // Rectangle définissant où la zone_source doit être déposée dans le renderer
             state = {0};                     // Rectangle de la vignette en cours dans la planche 

       SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
                         &window_dimensions.w,
                         &window_dimensions.h);
       SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
                        NULL, NULL,
                        &source.w, &source.h);

       /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

       int nb_images = 8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
       float zoom = 2;                        // zoom, car ces images sont un peu petites
       int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
           offset_y = source.h ;              // La hauteur d'une vignette de l'image, marche car la planche est bien réglée


       state.x = 0 ;                          // La première vignette est en début de ligne
       state.y = 0;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
       state.w = offset_x;                    // Largeur de la vignette
       state.h = offset_y;                    // Hauteur de la vignette

       destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
       destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

       destination.y =                        // La course se fait en milieu d'écran (en vertical)
         (window_dimensions.h - destination.h) /2;

       int speed = 9;
       for (int x = 0; x < window_dimensions.w - destination.w; x += speed) {
        destination.x = x;                   // Position en x pour l'affichage du sprite
        state.x += offset_x;                 // On passe à la vignette suivante dans l'image
        state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                                              // celle de début de ligne




        afficher_fond(fond_texture, window, renderer);

        SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                        &state,
                        &destination);  
        SDL_RenderPresent(renderer);         // Affichage
        SDL_Delay(80);                       // Pause en ms
       }
       SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
     }



int main(int argc, char **argv) 
{
	(void)argc;
	(void)argv;

    SDL_DisplayMode screen;

    SDL_Texture* run_texture = NULL,
                * fond_texture = NULL;

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);
    SDL_GetCurrentDisplayMode(0, &screen);

	window = SDL_CreateWindow(
		"Animation",
		SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
		1080,
        720,
		0);

	if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    fond_texture = load_texture_from_image("./sprite-murs.png", window, renderer);
    run_texture = load_texture_from_image("./run.png", window, renderer);
    
    
    animation(fond_texture, run_texture, window, renderer);

    IMG_Quit();


    SDL_DestroyTexture(fond_texture);
    SDL_DestroyTexture(run_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}