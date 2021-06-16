#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define N 30
#define M 50 

int survie[9] = {0,0,1,1,0,0,0,0,0};
int naissance[9] = {0,0,0,1,0,0,0,0,0};

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

void tore(int* i, int* j) {
    if (*i==N) *i=0;
    if (*i==-1) *i=N-1;
    if (*j==M) *j=0;
    if (*j==-1) *j=M-1;
}

int** init_zero() {
    int i, j;
    int** tab = (int **)malloc(N*sizeof(int *));
    for (i=0;i<N;++i) {
        tab[i] = (int*)malloc(M*sizeof(int));
        for (j=0;j<M;++j) {
            tab[i][j]=0;
        }
    }
    return tab;
}

int** init_grille() {
    int** tab=init_zero();
    tab[0][1]=1;
    tab[1][2]=1;
    tab[2][0]=1;
    tab[2][1]=1;
    tab[2][2]=1;
    return tab;
}

void afficher(int** tab) {
    int i, j;
    for (i=0;i<N;++i) {
        for (j=0;j<M;++j) {
            printf("%d ",tab[i][j]);
        }
        printf("\n");
    }
}

int nbr_voisins(int** tab, int i, int j) {
    int nbr=0, n, m, voisin_i, voisin_j;
    for (n=-1; n<2;++n) {
        for(m=-1;m<2;++m) {
            if (m!=0 || n!=0) {
                voisin_i=n+i;
                voisin_j=m+j;
                tore(&voisin_i, &voisin_j);
                nbr+=tab[voisin_i][voisin_j];
            }
        }
    }
    return nbr;
}

int** tab_voisins(int** tab) {
    int i, j;
    int** voisins=init_zero();
    for (i=0;i<N;++i) {
        for (j=0;j<M;++j) {
            voisins[i][j]=nbr_voisins(tab,i,j);
        }
    }
    return voisins;
}

void jeu_iter(int** tab) {
    int** voisins = tab_voisins(tab);
    int i, j;
    for (i=0;i<N;++i) {
        for (j=0;j<M;++j) {
            if (tab[i][j]) tab[i][j]=survie[voisins[i][j]];
            else tab[i][j]=naissance[voisins[i][j]];
        }
    }
}

void draw(SDL_Renderer* renderer, int i, int j, int w, int h) {                                   // Je pense que vous allez faire moins laid :)
    SDL_Rect rectangle;                                             

    SDL_SetRenderDrawColor(renderer,                                
                              255, 0, 255,                               // mode Red, Green, Blue (tous dans 0..255)
                              255);                                   // 0 = transparent ; 255 = opaque
    rectangle.x = j*w;                                                    // x haut gauche du rectangle
    rectangle.y = i*h;                                                    // y haut gauche du rectangle
    rectangle.w = w;                                                  // sa largeur (w = width)
    rectangle.h = h;                                                  // sa hauteur (h = height)

    SDL_RenderFillRect(renderer, &rectangle);
}

void draw_all(SDL_Renderer* renderer, int** grille, int w, int h) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderClear(renderer);
    int i, j;
    for (i=0; i<N; ++i) {
            for (j=0; j<M; ++j) {
                if (grille[i][j]) draw(renderer, i, j, w, h);
            }
        }
    SDL_RenderPresent(renderer);
}

void change_state(int** grille, int x, int y, int vie, SDL_DisplayMode screen) {
    int i = y/(screen.h/N);
    int j = x/(screen.w/M);
    grille[i][j]=vie;
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    int i, x, y;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_DisplayMode screen;

/*********************************************************************************************************************/  
/*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Premier dessin",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen.w,
                                screen.h,
                                SDL_WINDOW_OPENGL);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

    /* Création du renderer */
    renderer = SDL_CreateRenderer(
               window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    /*********************************************************************************************************************/
    /*                                     On dessine dans le renderer                                                   */
    int** grille = init_grille();

    SDL_bool
        program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
        paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause
    while (program_on) {                              // La boucle des évènements
        SDL_Event event;                                // Evènement à traiter

        while (program_on && SDL_PollEvent(&event)) {   // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                                        // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type) {                         // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:                                // Un évènement simple, on a cliqué sur la x de la // fenêtre
            program_on = SDL_FALSE;                     // Il est temps d'arrêter le programme
            break;
            case SDL_KEYDOWN:                             // Le type de event est : une touche appuyée
                                                        // comme la valeur du type est SDL_Keydown, dans la pratie 'union' de
                                                        // l'event, plusieurs champs deviennent pertinents   
            switch (event.key.keysym.sym) {             // la touche appuyée est ...
            case SDLK_p:                                // 'p'
            case SDLK_SPACE:                            // 'SPC'
                paused = !paused;                         // basculement pause/unpause
                break;
            case SDLK_ESCAPE:                           // 'ESCAPE'  
            case SDLK_q:                                // 'q'
                program_on = 0;                           // 'escape' ou 'q', d'autres façons de quitter le programme                                     
                break;
            default:                                    // Une touche appuyée qu'on ne traite pas
                break;
            }
            break;
            case SDL_MOUSEBUTTONDOWN:                     // Click souris   
            if (SDL_GetMouseState(&x, &y) & 
                SDL_BUTTON(SDL_BUTTON_LEFT) ) {         // Si c'est un click gauche
                change_state(grille, x, y, 1, screen);           // Fonction à éxécuter lors d'un click gauche
            } else if (SDL_GetMouseState(&x, &y) & 
                        SDL_BUTTON(SDL_BUTTON_RIGHT) ) { // Si c'est un click droit
                change_state(grille, x, y, 0, screen);           // Fonction à éxécuter lors d'un click droit
            }
        break;
        default:                                      // Les évènements qu'on n'a pas envisagé
        break;
        }
    }
    draw_all(renderer, grille, screen.w/M, screen.h/N);          // On redessine
    if (!paused) {                                  // Si on n'est pas en pause
        jeu_iter(grille);             // la vie continue... 
    }
    SDL_Delay(50);                                  // Petite pause
    }

/*
    for (iter=0; iter<500; ++iter) {
        for (i=0; i<N; ++i) {
            for (j=0; j<M; ++j) {
                if (grille[i][j]) draw(renderer, i, j, screen.w/M, screen.h/N);
            }
        }
        SDL_RenderPresent(renderer);                                        // affichage
        SDL_Delay(70);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderClear(renderer);
        jeu_iter(grille);
    }
*/

    /*********************************************************************************************************************/
    /* on libère la grille utilisée */
    for (i=0;i<N;++i) {
        free(grille[i]);
    }
    free(grille);

    /*********************************************************************************************************************/
    /* on referme proprement la SDL */
    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}