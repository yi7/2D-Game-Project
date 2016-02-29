#include "camera.h"

static SDL_Rect Camera = {0, 0, 0, 0};

SDL_Rect camera_get_active_camera()
{
	return Camera;
}

/*Vec2d camera get_position()
{
	return Vec2d
}

void camera_set_size(Vec2d size);
Vec2d cemra get_size();*/