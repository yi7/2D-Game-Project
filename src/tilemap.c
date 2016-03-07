#include "tilemap.h"

const int TILE_MAX		= 322; //20x12
const int TILE_WIDTH	= 40;
const int TILE_HEIGHT	= 40;

const int TILE_MAX_SPRITES = 12;
const int TILE_RED		= 0;
const int TILE_GREEN	= 1;
const int TILE_BLUE		= 2;
const int TILE_UP		= 3;
const int TILE_RIGHT	= 4;
const int TILE_DOWN		= 5;
const int TILE_LEFT		= 6;
const int TILE_MID		= 7;
const int TILE_BOT		= 8;
const int TILE_TOPRIGHT = 9;
const int TILE_MIDRIGHT	= 10;
const int TILE_BOTRIGHT = 11;

int tilemap_width;
int tilemap_height;
int tilemap_tpl;

Tile *tile_list = NULL;
SDL_Texture *tilemap_tile = NULL;
SDL_Rect tile_clips[TILE_MAX_SPRITES];
SDL_Rect tilemap_bound;

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
	char attribute[4];

	if(fscanf(fileptr, "%s", buffer))
	{
		if(strcmp(buffer, "map_width:") == 0)
		{
			fscanf(fileptr, "%s", attribute);
			tilemap_width = atoi(attribute);
		}
	}
	
	if(fscanf(fileptr, "%s", buffer))
	{
		if(strcmp(buffer, "map_height:") == 0)
		{
			fscanf(fileptr, "%s", attribute);
			tilemap_height = atoi(attribute);
		}
	}

	if(fscanf(fileptr, "%s", buffer))
	{
		if(strcmp(buffer, "tpl:") == 0)
		{
			fscanf(fileptr, "%s", attribute);
			tilemap_tpl = atoi(attribute);
		}
	}
}

void tilemap_load_map(char *filename)
{
	int i;
	int x = 0, y = 0;
	Tile *tile;
	FILE *fileptr = NULL;
	int tiletype;
	

	fileptr = fopen(filename, "r");
	if(!fileptr)
	{
		slog("Error: Cannot open map file: %s\n", filename);
		return;
	}
	tilemap_load_attributes(fileptr);

	for(i = 0; i < TILE_MAX; i++)
	{
		tile = &tile_list[i];
		tile->tile_box.x = x;
		tile->tile_box.y = y;
		tile->tile_box.w = TILE_WIDTH;
		tile->tile_box.h = TILE_HEIGHT;

		fscanf(fileptr, "%d", &tiletype);
		tile->tile_type = tiletype;

		x += TILE_WIDTH;
		if(x >= tilemap_width)
		{
			x = 0;
			y += TILE_HEIGHT;
		}
	}

	fclose(fileptr);

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

	tile_clips[TILE_UP].x = 80;
	tile_clips[TILE_UP].y = 0;
	tile_clips[TILE_UP].w = TILE_WIDTH;
	tile_clips[TILE_UP].h = TILE_HEIGHT;

	tile_clips[TILE_RIGHT].x = 80;
	tile_clips[TILE_RIGHT].y = 80;
	tile_clips[TILE_RIGHT].w = TILE_WIDTH;
	tile_clips[TILE_RIGHT].h = TILE_HEIGHT;

	tile_clips[TILE_DOWN].x = 80;
	tile_clips[TILE_DOWN].y = 160;
	tile_clips[TILE_DOWN].w = TILE_WIDTH;
	tile_clips[TILE_DOWN].h = TILE_HEIGHT;

	tile_clips[TILE_LEFT].x = 160;
	tile_clips[TILE_LEFT].y = 0;
	tile_clips[TILE_LEFT].w = TILE_WIDTH;
	tile_clips[TILE_LEFT].h = TILE_HEIGHT;

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

	tile_clips[TILE_MIDRIGHT].x = 240;
	tile_clips[TILE_MIDRIGHT].y = 80;
	tile_clips[TILE_MIDRIGHT].w = TILE_WIDTH;
	tile_clips[TILE_MIDRIGHT].h = TILE_HEIGHT;

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
	
	if(x > tilemap_width || y > tilemap_height)
	{
		slog("Not a valid tile");
		return;
	}

	int mapX = x / TILE_WIDTH;
	int mapY = y / TILE_HEIGHT;
	int tile_pos = tilemap_tpl * mapY + mapX;


	Tile *tile = &tile_list[tile_pos];
	int type = tile->tile_type;
	switch(type)
	{
	case TILE_RED:
		tile->tile_type = TILE_UP;
		break;
	case TILE_GREEN:
		tile->tile_type = TILE_UP;
		break;
	case TILE_BLUE:
		tile->tile_type = TILE_UP;
		break;
	case TILE_UP:
		tile->tile_type = TILE_RIGHT;
		break;
	case TILE_RIGHT:
		tile->tile_type = TILE_DOWN;
		break;
	case TILE_DOWN:
		tile->tile_type = TILE_LEFT;
		break;
	case TILE_LEFT:
		tile->tile_type = TILE_UP;
		break;
	}
}

void tilemap_entity_on_special_tile(Entity *entity)
{
	int x = entity->position.x;
	int y = entity->position.y;
	
	if((x % TILE_WIDTH) != 0 && (y % TILE_HEIGHT) != 0)
	{
		return;
	}
	
	int mapX = x / TILE_WIDTH;
	int mapY = y / TILE_HEIGHT;
	int tile_pos = tilemap_tpl * mapY + mapX;
	Tile *tile = &tile_list[tile_pos];

	if(tile->tile_box.x != x || tile->tile_box.y != y)
	{
		return;
	}

	int type = tile->tile_type;
	switch(type)
	{
	case TILE_UP:
		entity->direction = UP;
		break;
	case TILE_RIGHT:
		entity->direction = RIGHT;
		break;
	case TILE_DOWN:
		entity->direction = DOWN;
		break;
	case TILE_LEFT:
		entity->direction = LEFT;
		break;
	}
}

int tilemap_entity_out_of_bounds(Entity *entity)
{
	if( entity->position.x >= 0 &&
		entity->position.x + entity->frameSize.x <= tilemap_width &&
		entity->position.y >= 0 &&
		entity->position.y + entity->frameSize.y <= tilemap_height )
		return 0;
	return 1;
}