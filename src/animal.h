#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "SDL.h"
#include "SDL_image.h"

#include "entity.h"
#include "simple_logger.h"
#include "sprite.h"
#include "tilemap.h"
#include "vector.h"

/**
 * @brief initializes the hover mouse entity
 */
void animal_initialize_hovermouse();

/**
 * @brief initializes the speed mouse entity
 */
void animal_initialize_speedmouse();

/**
 * @brief initializes the normal mouse entity
 */
void animal_initialize_normalmouse();

/**
 * @brief initializes the cat entity
 */
void animal_initialize_cat();

/**
 * @brief frees the animal entity passed
 * @param entity the entity to be freed
 */
void animal_free(Entity *entity);

/**
 * @brief draws the animal entity passed
 * @param entity the entity to be drawn
 */
void animal_draw(Entity *entity);

/**
 * @brief think function of the animal entity passed
 * @param entity the entity to think
 */
void animal_think(Entity *entity);

/**
 * @brief touch function of the entity
 * @param self the entity to check whether it touches anything
 */
void animal_touch(Entity *self);

#endif