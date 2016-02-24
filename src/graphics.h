#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "stdlib.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "simple_logger.h"
#include "sprite.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window *graphics_window;
extern SDL_Surface *graphics_surface;
extern SDL_Renderer *graphics_renderer;

void graphics_initialize_system(char *windowName, int renderWidth, int renderHeight, int fullscreen);
void graphics_close_system();

void graphics_render_surface_to_screen(SDL_Surface *surface, SDL_Rect srcRect, int x, int y);
void graphics_draw_mouse();
void graphics_delay_frame();
void graphics_next_frame();

#endif
