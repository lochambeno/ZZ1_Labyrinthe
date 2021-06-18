#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>

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

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;
    SDL_Texture* my_texture = NULL;

    my_image = IMG_Load(file_image_name);
    
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image);
    SDL_FreeSurface(my_image);
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

void afficher_fond(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},
          window_dimensions = {0},
          destination = {0};

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);

  destination = window_dimensions;

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination);
}


void construire_vignettes(SDL_Texture* my_texture, SDL_Rect state[40], SDL_Rect* destination) {
    SDL_Rect source = {0};
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);
    int offset_x = source.w / 4,
        offset_y = source.h / 5;
    int i = 0, x, y; 
    float zoom = 2;                                  
    for (y = 0; y < source.h ; y += offset_y) {
        for (x = 0; x < source.w; x += offset_x) {
            state[i].x = x;
            state[i].y = y;
            state[i].w = offset_x;
            state[i].h = offset_y;
            ++i;
        }
    }
    state[14] = state[13];
    state[15] = state[16];                         
    for(; i< 40 ; ++i){
        state[i] = state[39-i];
    }

    (*destination).w = offset_x * zoom;
    (*destination).h = offset_y * zoom;
}

void afficher_vignette(SDL_Texture* my_texture, SDL_Renderer* renderer, SDL_Rect state, SDL_Rect destination) {
    SDL_RenderCopy(renderer, my_texture, &state, &destination);
}


int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* my_texture = NULL, *bg_texture = NULL;


    SDL_DisplayMode screen;

    /*********************************************************************************************************************/  
    /*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Animation shadow",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen.w * 0.66,
                              screen.h * 0.66,
                              SDL_WINDOW_OPENGL);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /*********************************************************************************************************************/
    /*                                     On dessine dans le renderer                                                   */
    my_texture=load_texture_from_image("./../images/shadow-80x70.png", window, renderer);
    bg_texture=load_texture_from_image("./../images/nasa-xFO2Xt33xgI-unsplash.jpg", window, renderer);

    int i=0, cpt=0;
    SDL_Rect
        window_dimensions = {0},
        destination = {0};
    SDL_GetWindowSize(window,
                      &window_dimensions.w, 
                      &window_dimensions.h); 
    SDL_Rect state[40];
    construire_vignettes(my_texture, state, &destination);
    destination.x = window_dimensions.w * 0.75;
    destination.y = window_dimensions.h * 0.7;
    
    

    SDL_bool
        program_on = SDL_TRUE,
        paused = SDL_FALSE;
    while (program_on) {
        SDL_Event event;

        while (program_on && SDL_PollEvent(&event)) {
             
            switch (event.type) {
            case SDL_QUIT:
                program_on = SDL_FALSE;
                break;
            case SDL_KEYDOWN:  

                switch (event.key.keysym.sym) {
                case SDLK_p:
                case SDLK_SPACE:
                    paused = !paused;
                    break;
                case SDLK_ESCAPE:
                case SDLK_q:
                    program_on = 0;                           
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
        }
    }
    afficher_fond(bg_texture, window, renderer);
    afficher_vignette(my_texture, renderer, state[i], destination);
    if (!paused) {
        if (cpt<35) ++i;
        else {
            if (cpt<=36) {
                if (!(cpt%2)) --i;
                else ++i;
            }
            else {
                if (cpt<=49) {
                    if (!(cpt%2)) i=i-1;
                    else ++i;
                    destination.x -= window_dimensions.w * 0.05;
                }
                else --i;
            }
        }
        cpt++;
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
    if (i==-1) program_on = SDL_FALSE;
    }


    /*********************************************************************************************************************/
    /* on referme proprement la SDL */
    IMG_Quit();
    SDL_DestroyTexture(my_texture);
    SDL_DestroyTexture(bg_texture);
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}
