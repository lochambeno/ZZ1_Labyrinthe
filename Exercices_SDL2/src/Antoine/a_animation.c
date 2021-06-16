#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>               // Nécessaire pour la fonction IMG_Load
#include <math.h>
#include <stdio.h>
#include <string.h>

/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/

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

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
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

void play_with_texture_3(SDL_Texture* my_texture,
                         SDL_Window* window,
                         SDL_Renderer* renderer) {
  SDL_Rect 
        source = {0},                             // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},                  // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(                                
      window, &window_dimensions.w,                 
      &window_dimensions.h);                      // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,         
                   &source.w,                       
                   &source.h);                    // Récupération des dimensions de l'image

  /* On décide de déplacer dans la fenêtre         cette image */
  float zoom = 0.25;                              // Facteur de zoom entre l'image source et l'image affichée

  int nb_it = 200, i;                                // Nombre d'images de l'animation
  destination.w = source.w * zoom;                // On applique le zoom sur la largeur
  destination.h = source.h * zoom;                // On applique le zoom sur la hauteur
  destination.x =                                   
      (window_dimensions.w - destination.w) / 2;  // On centre en largeur
  float h = window_dimensions.h - destination.h;  // hauteur du déplacement à effectuer

  for (i = 0; i < nb_it; ++i) {
    destination.y = 
        h * (1 - exp(-5.0 * i / nb_it) / 2 *
                     (1 + cos(10.0 * i / nb_it * 2 *
                              3.14)));            // hauteur en fonction du numéro d'image

    SDL_RenderClear(renderer);                    // Effacer l'image précédente

    SDL_SetTextureAlphaMod(my_texture,(1.0-1.0*i/nb_it)*255);      // L'opacité va passer de 255 à 0 au fil de l'animation
    SDL_RenderCopy(renderer, my_texture, &source, &destination);   // Préparation de l'affichage
    SDL_RenderPresent(renderer);                  // Affichage de la nouvelle image
    SDL_Delay(30);                                // Pause en ms
  }                                                 
  SDL_RenderClear(renderer);                      // Effacer la fenêtre une fois le travail terminé
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_Texture* my_texture = NULL;         // La texture


  SDL_DisplayMode screen;

/*********************************************************************************************************************/  
/*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w,
              screen.h);

  /* Création de la fenêtre */
  window = SDL_CreateWindow("Premier dessin",
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
  my_texture=load_texture_from_image("./../images/licorne2.png", window, renderer);
  play_with_texture_3(my_texture,window,renderer);


  /*********************************************************************************************************************/
  /* on referme proprement la SDL */
  IMG_Quit();
  SDL_DestroyTexture(my_texture);
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}
