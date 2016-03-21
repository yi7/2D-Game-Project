#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "SDL.h"
#include "SDL_image.h"

#include "entity.h"
#include "simple_logger.h"
#include "sprite.h"
#include "tilemap.h"
#include "vector.h"

void animal_initialize_mouse();
void animal_initialize_cat();
void animal_free(Entity *entity);
void animal_draw(Entity *entity);
void animal_think(Entity *entity);
void animal_touch(Entity *self);

#endif