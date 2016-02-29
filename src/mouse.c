#include "mouse.h"

Sprite *mouse;

struct
{
	Uint32 state;
	Uint32 shown;
	Uint32 frame;
	Uint16 x, y;
} Mouse;

void mouse_initialize_self()
{
	mouse = sprite_load("images/mouse.png", 16, 16);
	if(!mouse)
	{
		slog("Error: failed to load mouse sprite");
	}

	Mouse.state = 0;
	Mouse.shown = 0;
	Mouse.frame = 0;
}

void mouse_draw_self()
{
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	if(mouse)
	{
		sprite_draw(mouse, Mouse.frame, mx, my);
	}
	Mouse.frame = (Mouse.frame + 1) % 16;
	Mouse.x = mx;
	Mouse.y = my;
}