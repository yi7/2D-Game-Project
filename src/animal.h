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
 * @brief initializes animal based on type
 * @param x x position of animal
 * @param y y position of animal
 * @param direction direction animal is facing
 * @param type type of animal
 */
void animal_initialize(int x, int y, State direction, char *type);

/**
 * @brief initializes the hover mouse entity
 * @param x x position of hover mouse
 * @param y y position of hover mouse
 * @param direction direction of hover mouse
 */
void animal_initialize_hovermouse(int x, int y, State direction);

/**
 * @brief initializes the speed mouse entity
 * @param x x position of speed mouse
 * @param y y position of speed mouse
 * @param direction direction of speed mouse
 */
void animal_initialize_speedmouse(int x, int y, State direction);

/**
 * @brief initializes the normal mouse entity
 * @param x x position of normal mouse
 * @param y y position of normal mouse
 * @param direction direction of normal mouse
 */
void animal_initialize_normalmouse(int x, int y, State direction);

/**
 * @brief initializes the normal cat entity
 * @param x x position of normal cat
 * @param y y position of normal cat
 * @param direction direction of normal cat
 */
void animal_initialize_normalcat(int x, int y, State direction);

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