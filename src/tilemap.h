#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "stdio.h"
#include "stdlib.h"

#include "SDL.h"
#include "SDL_image.h"

#include "graphics.h"
#include "simple_logger.h"
#include "sprite.h"

typedef struct
{
	SDL_Rect tile_box; /**<the attributes of the tile*/
	int tile_type; /**<the tile type*/
} Tile;

void tilemap_initialize_system();
void tilemap_close_system();

void tilemap_load_tile(char *filename);
void tilemap_set_tile();
void tilemap_free_tile(Tile *tile);
void tilemap_render_tile();

#endif