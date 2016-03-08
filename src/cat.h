#ifndef __CAT_H__
#define __CAT_H__

#include "entity.h"
#include "simple_logger.h"
#include "sprite.h"
#include "tilemap.h"
#include "vector.h"

void cat_initialize();
void cat_free(Entity *entity);
void cat_draw(Entity *entity);
void cat_think(Entity *entity);
void cat_touch(Entity *self);

#endif