#ifndef WINDOW_H
#define WINDOW_H

void end_sdl(char, char const*, SDL_Window*, SDL_Renderer*);
void create_sdl(SDL_Window*, SDL_Renderer*, SDL_DisplayMode, char*, float, float);
SDL_Texture* load_texture_from_image(char*, SDL_Window*, SDL_Renderer*);

#endif