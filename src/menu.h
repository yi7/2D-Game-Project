#ifndef __MENU_H__
#define __MENU_H__

#include "animal.h"
#include "graphics.h"
#include "simple_logger.h"
#include "sprite.h"
#include "vector.h"
#include "tilemap.h"

extern int menu_flag;

/**
 * @brief initializes the menu
 */
void menu_initialize();

/**
 * @brief draws the menu
 */
void menu_draw();

/**
 * @brief depending on the mouse position, interact with the ui
 */
void menu_click();

#endif