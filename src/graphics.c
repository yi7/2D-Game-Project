#include "graphics.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int HUD_WIDTH = 160;
const int HUD_HEIGHT = SCREEN_HEIGHT;

SDL_Window *graphics_window = NULL;
SDL_Surface *graphics_surface = NULL;
SDL_Renderer *graphics_renderer = NULL;
SDL_Texture *graphics_texture = NULL;

static Uint32 graphics_f_delay = 30;
static Uint32 graphics_now = 0;
static Uint32 graphics_then = 0;
static float graphics_fps = 0; 

void graphics_initialize_system(char *windowName, int renderWidth, int renderHeight, int fullscreen)
{
	Uint32 flags = 0;

	if(fullscreen)
	{
		if(renderWidth == 0)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		else
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}
	}
	else
	{
		flags |= SDL_WINDOW_SHOWN;
	}

	graphics_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, renderWidth, renderHeight, flags);
	if(!graphics_window)
	{
		slog("graphics_initialize_system: Failed to create main window: %s\n", SDL_GetError);
		graphics_close_system();
		return;
	}

	graphics_renderer = SDL_CreateRenderer(graphics_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (!graphics_renderer)
    {
		slog("failed to create renderer: %s",SDL_GetError());
        graphics_close_system();
        return;
    }

	SDL_SetRenderDrawColor(graphics_renderer, 0, 0, 0, 255);
    SDL_RenderClear(graphics_renderer);
    SDL_RenderPresent(graphics_renderer);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(graphics_renderer, renderWidth, renderHeight);

	graphics_texture = SDL_CreateTexture(graphics_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, renderWidth, renderHeight);
    if (!graphics_texture)
    {
        slog("failed to create screen texture: %s",SDL_GetError());
        graphics_close_system();
        return;
    };

	/*graphics_surface = SDL_GetWindowSurface(graphics_window);
	if (!graphics_surface)
    {
        slog("failed to create screen surface: %s",SDL_GetError());
        graphics_close_system();
        return;
    }*/

	atexit(graphics_close_system);
	slog("graphics initialized");
}

void graphics_close_system()
{
	if(graphics_window)
	{
		SDL_DestroyWindow(graphics_window);
	}
	if(graphics_renderer)
	{
		SDL_DestroyRenderer(graphics_renderer);
	}
	if(graphics_texture)
	{
		SDL_DestroyTexture(graphics_texture);
	}
	if(graphics_surface)
	{
		SDL_FreeSurface(graphics_surface);
	}
	
	SDL_Window *graphics_window = NULL;
	SDL_Renderer *graphics_renderer = NULL;
	SDL_Texture *graphics_texture = NULL;
	SDL_Surface *graphics_surface = NULL;
}

void graphics_frame_delay()
{
    Uint32 diff;
    graphics_then = graphics_now;
    graphics_now = SDL_GetTicks();
    diff = (graphics_now - graphics_then);
    if (diff < graphics_f_delay)
    {
        SDL_Delay(graphics_f_delay - diff);
    }
    graphics_fps = 1000.0 / MAX(SDL_GetTicks() - graphics_then, 0.001);
	//slog("%f", graphics_fps);
}

void graphics_next_frame()
{
	SDL_RenderPresent(graphics_renderer);
	graphics_frame_delay();
}
