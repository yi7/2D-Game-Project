#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "simple_logger.h"
#include "sprite.h"
#include "vector.h"
#include "tilemap.h"

/**
 * @brief initializes the computer mouse
 */
void mouse_initialize_self();

/**
 * @brief draws the mouse onto the window
 */
void mouse_draw_self();

#endif