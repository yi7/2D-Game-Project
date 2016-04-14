#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "stdio.h"
#include "stdlib.h"

#include "SDL.h"
#include "SDL_image.h"

#include "animal.h"
#include "entity.h"
#include "graphics.h"
#include "menu.h"
#include "mouse.h"
#include "simple_logger.h"
#include "sound.h"
#include "sprite.h"

extern SDL_Rect tilemap_bound;
extern int tilemap_width;
extern int tilemap_height;

typedef struct
{
	SDL_Rect tile_box; /**<the attributes of the tile*/
	int tile_type; /**<the primary tile type*/
	int tile_buffer; /**<the secondary tile type*/
} Tile;

/**
 * @brief initializes the tilmap system
 * @param levelname the map file to load
 * @param animal_positions text file containing the positions of the animals in the level
 */
void tilemap_initialize_system(char *levelname, char *animal_positions);

/**
 * @brief closes the tilemap system
 */
void tilemap_close_system();

/**
 * @brief loads tile sprite sheet as surface and converts it into a texture
 * @param filename the filname of the tile sprite sheet
 */
void tilemap_load_tiles(char *filename);

/**
 * @brief loads the map by placing the tiles
 * @param filename the map file to load
 */
void tilemap_load_map(char *filename);

/**
 * @brief sets passed tile to NULL
 * @param tile the tile to free
 */
void tilemap_free_tile(Tile *tile);

/**
 * @brief draws the tile that was placed
 */
void tilemap_render_tile();

/**
 * @brief draws the side menu of the level
 */
void tilemap_draw_sidemenu();

/**
 * @brief depending on the mouse position, interact with the ui
 */
void tilemap_click();

/**
 * @brief removes a secondary tile thats on the map
 */
void tilemap_remove_tile();

/**
 * @brief checks the tile in front of an entity
 * @param entity the entity to check whats in front of it
 */
void tilemap_check_front_tile(Entity *entity);

/**
 * @brief checks the tile that an entity is on top of
 * @param entity the entity to check what tile it's on
 */
void tilemap_entity_on_special_tile(Entity *entity);

/**
 * @brief checks if entity is about to go out of the map
 * @param entity the entity to check whether its going out of the map or not
 */
int tilemap_entity_out_of_bounds(Entity *entity);

/**
 * @brief loads animals by reading their positions
 * @param filename containing the animal positions
 */
void tilemap_load_animals();

#endif