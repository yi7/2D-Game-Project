#include "SDL.h"
#include "SDL_image.h"
#include "stdio.h"
#include "stdlib.h"

#include "simple_logger.h"
#include "graphics.h"
#include "sprite.h"

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
	if(game_get_image_path_from_file(imagepath, "config.ini"))
	{
		temp = IMG_Load(imagepath);
	}

	if(temp)
	{
		optimized_surface = SDL_ConvertSurface( temp, graphics_surface->format, NULL );
		SDL_FreeSurface(temp);
		
	}
	SDL_BlitSurface(optimized_surface, NULL, graphics_surface, NULL);
	SDL_UpdateWindowSurface(graphics_window);

	SDL_Event e;
	done = 0;
	do
	{
		graphics_reset_buffer();
		SDL_PumpEvents();

		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				done = 1;
			}
		}

		keys = SDL_GetKeyboardState(NULL);
		if(keys[SDL_SCANCODE_ESCAPE])
		{
			done = 1;
		}
	} while(!done);

	exit(0);
	return 0;
}

void game_close_system()
{
	sprite_close_system();
}

void game_initialize_system()
{
	graphics_initialize_system("Game Test", 800, 400, 0);
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