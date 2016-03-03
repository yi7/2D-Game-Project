#include "tilemap.h"

const int TILE_MAX		= 240; //20x12
const int TILE_WIDTH	= 40;
const int TILE_HEIGHT	= 40;

const int TILE_MAX_SPRITES = 12;
const int TILE_RED		= 0;
const int TILE_GREEN	= 1;
const int TILE_BLUE		= 2;
const int TILE_TOPLEFT	= 3;
const int TILE_LEFT		= 4;
const int TILE_BOTLEFT  = 5;
const int TILE_TOP		= 6;
const int TILE_MID		= 7;
const int TILE_BOT		= 8;
const int TILE_TOPRIGHT = 9;
const int TILE_RIGHT	= 10;
const int TILE_BOTRIGHT = 11;

int tilemap_width;
int tilemap_height;
int tilemap_tpl;

Tile *tile_list = NULL;
SDL_Texture *tilemap_tile = NULL;
SDL_Rect tile_clips[TILE_MAX_SPRITES];
SDL_Rect tilemap_bound;

Sprite *tilemap;

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

	tilemap_load_tiles("images/tiles.png");

	tilemap_load_map("images/level.map");
	tilemap_bound.x = 0;
	tilemap_bound.y = 0;
	tilemap_bound.w = tilemap_width;
	tilemap_bound.h = tilemap_height;

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

void tilemap_load_tiles(char *filename)
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

void tilemap_load_attributes(FILE *fileptr)
{
	char buffer[255];
	char width[4];
	char height[4];
	char tpl[4];

	if(fscanf(fileptr, "%s", buffer))
	{
		if(strcmp(buffer, "width:") == 0)
		{
			fscanf(fileptr, "%s", width);
			tilemap_width = atoi(width);
		}
	}
	
	if(fscanf(fileptr, "%s", buffer))
	{
		if(strcmp(buffer, "height:") == 0)
		{
			fscanf(fileptr, "%s", height);
			tilemap_height = atoi(height);
		}
	}

	if(fscanf(fileptr, "%s", buffer))
	{
		if(strcmp(buffer, "tpl:") == 0)
		{
			fscanf(fileptr, "%s", tpl);
			tilemap_tpl = atoi(tpl);
		}
	}
}

void tilemap_load_map(char *filename)
{
	int i;
	int x = 0, y = 0;
	Tile *tile;
	FILE *tilemap = NULL;
	int tiletype;
	

	tilemap = fopen(filename, "r");
	if(!tilemap)
	{
		slog("Error: Cannot open map file: %s\n", filename);
		return;
	}
	tilemap_load_attributes(tilemap);

	for(i = 0; i < TILE_MAX; i++)
	{
		tile = &tile_list[i];
		tile->tile_box.x = x;
		tile->tile_box.y = y;
		tile->tile_box.w = TILE_WIDTH;
		tile->tile_box.h = TILE_HEIGHT;

		fscanf(tilemap, "%d", &tiletype);
		tile->tile_type = tiletype;

		x += TILE_WIDTH;
		if(x >= tilemap_width)
		{
			x = 0;
			y += TILE_HEIGHT;
		}
	}

	fclose(tilemap);

	//clip the sprite sheet
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

void tilemap_place_tile()
{
	int x, y;
	SDL_GetMouseState( &x, &y );
	
	int mapX = x / TILE_WIDTH;
	int mapY = y / TILE_HEIGHT;
	int tile_pos = tilemap_tpl * mapY + mapX;

	Tile *tile = &tile_list[tile_pos];
	tile->tile_type = TILE_MID;
}

int tilemap_tile_collide()
{
	return 0;
}