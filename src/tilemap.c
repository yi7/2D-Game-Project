#include "tilemap.h"

const int TILE_MAX = 60; //10x6
const int TILE_MAX_SPRITES = 12;
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;

const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_TOPLEFT = 3;
const int TILE_LEFT = 4;
const int TILE_BOTLEFT = 5;
const int TILE_TOP = 6;
const int TILE_MID = 7;
const int TILE_BOT = 8;
const int TILE_TOPRIGHT = 9;
const int TILE_RIGHT = 10;
const int TILE_BOTRIGHT = 11;

static Tile *tile_list = NULL;
SDL_Texture *tilemap_tile = NULL;
SDL_Rect tile_clips[TILE_MAX_SPRITES];

void tilemap_initialize_system()
{
	int i;
	if(TILE_MAX == 0)
	{
		slog("Error: no tiles to place on map");
	}

	tile_list = (Tile *)malloc(sizeof(Tile) * TILE_MAX);
	if(!tile_list)
	{
		slog("Error: failed to allocate tilemap system.");
        return;
	}
	
	memset(tile_list, 0, sizeof(Tile) * TILE_MAX);

	SDL_Rect temp = {0, 0, 0, 0};
	for(i = 0; i < TILE_MAX; i++)
	{
		tile_list[i].tile_box = temp;
	}

	tilemap_load_tile("images/tiles.png");
	tilemap_set_tile();
	tilemap_render_tile();

	atexit(tilemap_close_system);
}

void tilemap_close_system()
{
	int i;
	for(i = 0; i < TILE_MAX; i++)
	{
		tilemap_free_tile(&tile_list[i]);
	}

	SDL_DestroyTexture(tilemap_tile);
}

void tilemap_free_tile(Tile *tile)
{
	tile = NULL;
}

void tilemap_load_tile(char *filename)
{
	SDL_Surface *temp = IMG_Load(filename);
	if(!temp)
	{
		slog("Error: could not load tile sprite");
		return;
	}

	tilemap_tile = SDL_CreateTextureFromSurface(graphics_renderer, temp);
	SDL_FreeSurface(temp);

	if(!tilemap_tile)
	{
		slog("Error: could not create texture from sprite surface");
		return;
	}
}

void tilemap_set_tile()
{
	int i;
	int x = 0, y = 0;
	Tile *tile;

	for(i = 0; i < TILE_MAX; i++)
	{
		tile = &tile_list[i];
		tile->tile_box.x = x;
		tile->tile_box.y = y;
		tile->tile_box.w = TILE_WIDTH;
		tile->tile_box.h = TILE_HEIGHT;

		if(i % 2 == 0)
			tile->tile_type = TILE_RED;
		else if(i % 3 == 0)
			tile->tile_type = TILE_BLUE;
		else
			tile->tile_type = TILE_GREEN;

		x += TILE_WIDTH;
		if(x >= SCREEN_WIDTH)
		{
			x = 0;
			y += TILE_HEIGHT;
		}
	}

	//clip the sprite sheet
	if(tile->tile_type)
	{
		tile_clips[TILE_RED].x = 0;
		tile_clips[TILE_RED].y = 0;
		tile_clips[TILE_RED].w = TILE_WIDTH;
		tile_clips[TILE_RED].h = TILE_HEIGHT;

		tile_clips[TILE_GREEN].x = 0;
		tile_clips[TILE_GREEN].y = 80;
		tile_clips[TILE_GREEN].w = TILE_WIDTH;
		tile_clips[TILE_GREEN].h = TILE_HEIGHT;

		tile_clips[TILE_BLUE].x = 0;
		tile_clips[TILE_BLUE].y = 160;
		tile_clips[TILE_BLUE].w = TILE_WIDTH;
		tile_clips[TILE_BLUE].h = TILE_HEIGHT;

		tile_clips[TILE_TOPLEFT].x = 80;
		tile_clips[TILE_TOPLEFT].y = 0;
		tile_clips[TILE_TOPLEFT].w = TILE_WIDTH;
		tile_clips[TILE_TOPLEFT].h = TILE_HEIGHT;

		tile_clips[TILE_LEFT].x = 80;
		tile_clips[TILE_LEFT].y = 80;
		tile_clips[TILE_LEFT].w = TILE_WIDTH;
		tile_clips[TILE_LEFT].h = TILE_HEIGHT;

		tile_clips[TILE_BOTLEFT].x = 80;
		tile_clips[TILE_BOTLEFT].y = 160;
		tile_clips[TILE_BOTLEFT].w = TILE_WIDTH;
		tile_clips[TILE_BOTLEFT].h = TILE_HEIGHT;

		tile_clips[TILE_TOP].x = 160;
		tile_clips[TILE_TOP].y = 0;
		tile_clips[TILE_TOP].w = TILE_WIDTH;
		tile_clips[TILE_TOP].h = TILE_HEIGHT;

		tile_clips[TILE_MID].x = 160;
		tile_clips[TILE_MID].y = 80;
		tile_clips[TILE_MID].w = TILE_WIDTH;
		tile_clips[TILE_MID].h = TILE_HEIGHT;

		tile_clips[TILE_BOT].x = 160;
		tile_clips[TILE_BOT].y = 160;
		tile_clips[TILE_BOT].w = TILE_WIDTH;
		tile_clips[TILE_BOT].h = TILE_HEIGHT;

		tile_clips[TILE_TOPRIGHT].x = 240;
		tile_clips[TILE_TOPRIGHT].y = 0;
		tile_clips[TILE_TOPRIGHT].w = TILE_WIDTH;
		tile_clips[TILE_TOPRIGHT].h = TILE_HEIGHT;

		tile_clips[TILE_RIGHT].x = 240;
		tile_clips[TILE_RIGHT].y = 80;
		tile_clips[TILE_RIGHT].w = TILE_WIDTH;
		tile_clips[TILE_RIGHT].h = TILE_HEIGHT;

		tile_clips[TILE_BOTRIGHT].x = 240;
		tile_clips[TILE_BOTRIGHT].y = 160;
		tile_clips[TILE_BOTRIGHT].w = TILE_WIDTH;
		tile_clips[TILE_BOTRIGHT].h = TILE_HEIGHT;
	}
}

void tilemap_render_tile()
{
	int i;
	for(i = 0; i < TILE_MAX; i++)
	{
		Tile *tile = &tile_list[i];
		if(!tile)
		{
			slog("Error: tile not loaded");
		}

		SDL_Rect src;
		src = tile_clips[tile_list[i].tile_type];

		SDL_Rect dst;
		dst.x = tile->tile_box.x;
		dst.y = tile->tile_box.y;
		dst.w = TILE_WIDTH;
		dst.h = TILE_HEIGHT;

		SDL_RenderCopy(graphics_renderer, tilemap_tile, &src, &dst);
	}
}
