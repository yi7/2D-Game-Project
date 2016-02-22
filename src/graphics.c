#include "stdlib.h"

#include "graphics.h"
#include "simple_logger.h"

SDL_Window *graphics_window = NULL;
static SDL_Renderer *graphics_renderer = NULL;
static SDL_Texture *graphics_texture = NULL;
SDL_Surface *graphics_surface = NULL;
static SDL_Surface *graphics_temp_surface = NULL;

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

	graphics_surface = SDL_GetWindowSurface(graphics_window);

	atexit(graphics_close_system);
	slog("graphics initialized");
}

void graphics_close_system()
{
	if(graphics_window)
		SDL_DestroyWindow(graphics_window);
	if(graphics_renderer)
		SDL_DestroyRenderer(graphics_renderer);
	if(graphics_texture)
		SDL_DestroyTexture(graphics_texture);
	if(graphics_surface)
		SDL_FreeSurface(graphics_surface);
	if(graphics_temp_surface)
		SDL_FreeSurface(graphics_temp_surface);
	
	SDL_Window *graphics_window = NULL;
	SDL_Renderer *graphics_renderer = NULL;
	SDL_Texture *graphics_texture = NULL;
	SDL_Surface *graphics_surface = NULL;
	SDL_Surface *graphics_temp_surface = NULL;
}

void graphics_render_surface_to_screen(SDL_Surface *surface, SDL_Rect srcRect, int x, int y)
{
    SDL_Rect dstRect;
    SDL_Point point = {1, 1};
    int w, h;

    if (!graphics_texture)
    {
        slog("graphics_render_surface_to_screen: no texture available");
        return;
    }
    if (!surface)
    {
        slog("graphics_render_surface_to_screen: no surface provided");
        return;
    }

    SDL_QueryTexture(graphics_texture, NULL, NULL, &w, &h);

    /*check if resize is needed*/
    if ((surface->w > w) || (surface->h > h))
    {
        SDL_DestroyTexture(graphics_texture);
        graphics_texture = SDL_CreateTexture(graphics_renderer,
                                                   graphics_surface->format->format,
                                                   SDL_TEXTUREACCESS_STREAMING, 
                                                   surface->w,
                                                   surface->h);
        if (!graphics_texture)
        {
            slog("gt_graphics_render_surface_to_screen: failed to allocate more space for the screen texture!");
            return;
        }
    }

    SDL_SetTextureBlendMode(graphics_texture,SDL_BLENDMODE_BLEND);        
    SDL_UpdateTexture(graphics_texture, &srcRect, surface->pixels, surface->pitch);

    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;

    SDL_RenderCopy(graphics_renderer, graphics_texture, &srcRect, &dstRect);
}

void graphics_reset_buffer()
{
	SDL_RenderPresent(graphics_renderer);
}

