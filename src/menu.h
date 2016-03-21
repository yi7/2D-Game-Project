#ifndef __MENU_H__
#define __MENU_H__

#include "animal.h"
#include "graphics.h"
#include "simple_logger.h"
#include "sprite.h"
#include "vector.h"
#include "tilemap.h"

extern int menu_flag;

void menu_initialize();
void menu_draw();
void menu_click();

#endif