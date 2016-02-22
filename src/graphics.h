#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

void graphics_initialize_system(char *windowName, int renderWidth, int renderHeight, int fullscreen);
void graphics_close_system();

void graphics_render_surface_to_screen(SDL_Surface *surface, SDL_Rect srcRect, int x, int y);
void graphics_reset_buffer();


#endif
