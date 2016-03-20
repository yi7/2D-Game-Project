#include "menu.h"

int menu_flag = true;

Sprite *background;

Sprite *button1;
SDL_Rect button1_box;
Sprite *button2;
SDL_Rect button2_box;

void menu_initialize()
{
	background = sprite_load("images/bgtest2.png", 1024, 768);

	button1_box.x = 80;
	button1_box.y = 80;
	button1_box.w = 80;
	button1_box.h = 40;
	button1 = sprite_load("images/button_test.png", button1_box.w, button1_box.h);
	button2_box.x = 200;
	button2_box.y = 80;
	button2_box.w = 80;
	button2_box.h = 40;
	button2 = sprite_load("images/button_test.png", button2_box.w, button2_box.h);
}

void menu_draw()
{
	SDL_RenderCopy(graphics_renderer, background->image, NULL, NULL); 
	sprite_draw(button1, 0, button1_box.x, button1_box.y);
	sprite_draw(button2, 0, button2_box.x, button2_box.y);	
}

void menu_click()
{
	int x, y;
	SDL_Rect mouse;

	SDL_GetMouseState( &x, &y );
	mouse.x = x;
	mouse.y = y;
	mouse.w = 0;
	mouse.h = 0;
	
	if(rect_intersect(mouse, button1_box))
	{
		slog("button1 clicked\n");
		menu_flag = false;
		tilemap_initialize_system();
	}
	else if(rect_intersect(mouse, button2_box))
	{
		slog("button2 clicked\n");
	}
}