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
extern const int HUD_WIDTH;
extern const int HUD_HEIGHT;

extern SDL_Window *graphics_window;
extern SDL_Surface *graphics_surface;
extern SDL_Renderer *graphics_renderer;

/**
 * @brief initializes the graphics system
 * @param windowName the window name of the window
 * @param renderWidth the width of the window
 * @param renderHeight the height of the window
 * @param fullscreen flag that sets whether its full screen or windowed
 */
void graphics_initialize_system(char *windowName, int renderWidth, int renderHeight, int fullscreen);

/**
 * @brief closes the graphics system
 */
void graphics_close_system();

/**
 * @brief sets the fps of the game
 */
void graphics_frame_delay();

/**
 * @brief sets the next frame to load
 */
void graphics_next_frame();

#endif
