#ifndef __MICE_H__
#define __MICE_H__

#include "SDL_image.h"

#include "entity.h"
#include "simple_logger.h"
#include "sprite.h"
#include "tilemap.h"
#include "vector.h"

void mice_initialize();
void mice_draw(Entity *entity);
void mice_think(Entity *entity);

#endif