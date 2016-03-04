#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "simple_logger.h"
#include "sprite.h"
#include "vector.h"
#include "tilemap.h"

void mouse_initialize_self();
void mouse_draw_self();
Vect2d mouse_get_position();

#endif