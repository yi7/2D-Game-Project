#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "stdio.h"
#include "stdlib.h"

#include "SDL.h"
#include "SDL_image.h"

#include "graphics.h"
#include "mouse.h"
#include "simple_logger.h"
#include "sprite.h"

extern SDL_Rect tilemap_bound;

typedef struct
{
	SDL_Rect tile_box; /**<the attributes of the tile*/
	int tile_type; /**<the tile type*/
} Tile;

void tilemap_initialize_system();
void tilemap_close_system();

void tilemap_load_tiles(char *filename);
void tilemap_load_attributes(char *fileptr);
void tilemap_load_map(char *filename);
void tilemap_free_tile(Tile *tile);
void tilemap_render_tile();
void tilemap_place_tile();

int tilemap_tile_collide();

#endif