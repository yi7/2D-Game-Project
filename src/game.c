#include "stdio.h"
#include "stdlib.h"
#include "windows.h"

#include "SDL.h"
#include "SDL_image.h"

#include "cat.h"
#include "entity.h"
#include "graphics.h"
#include "menu.h"
#include "mice.h"
#include "mouse.h"
#include "simple_logger.h"
#include "sprite.h"
#include "tilemap.h"

extern SDL_Window *graphics_window;
extern SDL_Surface *graphics_surface;

void game_initialize_system();
bool game_get_image_path_from_file(char *filepath, char *filename);

int main(int argc, char *argv[])
{
	SDL_Surface *optimized_surface = NULL;
	SDL_Surface *temp = NULL;
	int done;
	const Uint8 *keys;
	char imagepath[512];

	game_initialize_system();
	SDL_ShowCursor(SDL_DISABLE);

	/*if(game_get_image_path_from_file(imagepath, "config.ini"))
	{
		temp = IMG_Load(imagepath);
	}

	if(temp)
	{
		optimized_surface = SDL_ConvertSurface( temp, graphics_surface->format, NULL );
		SDL_FreeSurface(temp);
		
	}
	SDL_BlitSurface(optimized_surface, NULL, graphics_surface, NULL);*/
	//SDL_UpdateWindowSurface(graphics_window);

	//mice_initialize();
	//cat_initialize();

	SDL_Event e;
	done = 0;
	do
	{
		if(menu_flag)
			menu_draw();
		else
			tilemap_render_tile();
		entity_draw_all();
		mouse_draw_self();

		graphics_next_frame();
		SDL_PumpEvents();

		entity_think_all();

		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				done = 1;
			}
			
			bool leftclick = false ;
			bool rightclick = false;
			if(e.type == SDL_MOUSEBUTTONDOWN)
			{
				if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					leftclick = true;
				}
				else if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
				{
					rightclick = true;
				}
			}
			if(leftclick == true)
			{
				if(menu_flag)
					menu_click();
				else
					tilemap_click();
			}
			else if(rightclick == true)
			{
				if(menu_flag)
					menu_click();
				else
					tilemap_remove_tile();
			}
		}

		keys = SDL_GetKeyboardState(NULL);
		if(keys[SDL_SCANCODE_ESCAPE])
		{
			done = 1;
		}

		SDL_RenderPresent(graphics_renderer); // update the screen with any rendering performed since previous call

	} while(!done);

	exit(0);
	return 0;
}

void game_close_system()
{
	//sprite_close_system();
}

void game_initialize_system()
{
	graphics_initialize_system("Mice Alert", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	sprite_initialize_system();
	entity_initialize_system();
	menu_initialize();
	//tilemap_initialize_system();
	mouse_initialize_self();	
	atexit(game_close_system);
}

bool game_get_image_path_from_file(char *filepath, char *filename)
{
	FILE *fileptr = NULL;
	char buffer[255];

	if(!filepath)
	{
		slog("game_get_image_path_from_file: No output parameter provided\n");
		return false;
	}

	if(!filename)
	{
		slog("game_get_image_path_from_file: No input file path provided\n");
		return false;
	}

	fileptr = fopen(filename, "r");
	if(!fileptr)
	{
		slog("game_get_image_path_from_file: Unable to open file: %s\n", filename);
		return false;
	}

	if(fscanf(fileptr, "%s", buffer))
	{
		if(strcmp(buffer, "image:") == 0)
		{
			fscanf(fileptr, "%s", filepath);
			fclose(fileptr);
			return true;
		}
	}

	return false;
}