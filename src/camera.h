#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "SDL.h"
#include "vector.h"

SDL_Rect camera_get_active_camera();
Vect2d camera_get_position();

void camera_set_size(Vect2d size);
Vect2d camera_get_size();

#endif