#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "string.h"
#include "string.h"
#include "stdlib.h"

#include "SDL.h"
#include "SDL_image.h"

#include "graphics.h"
#include "simple_logger.h"
#include "vector.h"

typedef struct
{
	int refCount;			/**<keeps track of references to this element*/
	char filename[128];		/**<name of the image file loaded*/
	SDL_Texture *image;		/**<texture of the image loaded*/
	Vect2d imageSize;		/**<x and y dimensions of the image loaded*/
	Vect2d frameSize;		/**<the dimensions of a frame in the sprite sheet*/
	int fpl;				/**<how many frames per line in this sprite sheet*/
} Sprite;

/**
 * @brief initializes the sprite system
 */
void sprite_initialize_system();

/**
 * @brief closes the sprite system
 */
void sprite_close_system();

/**
 * @brief loads the sprite and return a pointer to it
 * @param filename the filename of the sprite to load
 * @param the frame width of the sprite
 * @param the frame height of the sprite
 */
Sprite* sprite_load(char *filename, int frameW, int frameH);

/**
 * @brief frees a loaded sprite from memory
 * @param sprite the sprite to be freed
 */
void sprite_free(Sprite **sprite);

/**
 * @brief draws the sprite
 * @param sprite the sprite to draw
 * @param the frame index of the sprite to draw
 * @param the width of the sprite frame
 * @param the height of the sprite frame
 */
void sprite_draw(Sprite *sprite, int frame, int drawX, int drawY);

#endif