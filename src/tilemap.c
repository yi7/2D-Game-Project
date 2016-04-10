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
const int TILE_HOLE		= 7;
const int TILE_BLOCK	= 8;
const int TILE_TOPRIGHT = 9;
const int TILE_MIDRIGHT	= 10;
const int TILE_BOTRIGHT = 11;

int tilemap_width;
int tilemap_height;
int tilemap_tpl;

int tilemap_arrow_count;
Tile *tile_list = NULL;
SDL_Texture *tilemap_tile = NULL;
SDL_Rect tile_clips[TILE_MAX_SPRITES];
SDL_Rect tilemap_bound;

void tilemap_initialize_system(char *levelname)
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
		tile_list[i].tile_buffer = NULL;
		tile_list[i].tile_box = temp;
	}

	tilemap_load_tiles("images/tiles.png");

	tilemap_load_map(levelname);
	tilemap_bound.x = 0;
	tilemap_bound.y = 0;
	tilemap_bound.w = tilemap_width;
	tilemap_bound.h = tilemap_height;

	tilemap_arrow_count = 0;
	//tilemap_render_tile();

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
	tile_clips[TILE_GREEN].y = 40;
	tile_clips[TILE_GREEN].w = TILE_WIDTH;
	tile_clips[TILE_GREEN].h = TILE_HEIGHT;

	tile_clips[TILE_BLUE].x = 0;
	tile_clips[TILE_BLUE].y = 80;
	tile_clips[TILE_BLUE].w = TILE_WIDTH;
	tile_clips[TILE_BLUE].h = TILE_HEIGHT;

	tile_clips[TILE_UP].x = 40;
	tile_clips[TILE_UP].y = 0;
	tile_clips[TILE_UP].w = TILE_WIDTH;
	tile_clips[TILE_UP].h = TILE_HEIGHT;

	tile_clips[TILE_RIGHT].x = 40;
	tile_clips[TILE_RIGHT].y = 40;
	tile_clips[TILE_RIGHT].w = TILE_WIDTH;
	tile_clips[TILE_RIGHT].h = TILE_HEIGHT;

	tile_clips[TILE_DOWN].x = 40;
	tile_clips[TILE_DOWN].y = 80;
	tile_clips[TILE_DOWN].w = TILE_WIDTH;
	tile_clips[TILE_DOWN].h = TILE_HEIGHT;

	tile_clips[TILE_LEFT].x = 80;
	tile_clips[TILE_LEFT].y = 0;
	tile_clips[TILE_LEFT].w = TILE_WIDTH;
	tile_clips[TILE_LEFT].h = TILE_HEIGHT;

	tile_clips[TILE_HOLE].x = 80;
	tile_clips[TILE_HOLE].y = 40;
	tile_clips[TILE_HOLE].w = TILE_WIDTH;
	tile_clips[TILE_HOLE].h = TILE_HEIGHT;

	tile_clips[TILE_BLOCK].x = 80;
	tile_clips[TILE_BLOCK].y = 80;
	tile_clips[TILE_BLOCK].w = TILE_WIDTH;
	tile_clips[TILE_BLOCK].h = TILE_HEIGHT;

	tile_clips[TILE_TOPRIGHT].x = 120;
	tile_clips[TILE_TOPRIGHT].y = 0;
	tile_clips[TILE_TOPRIGHT].w = TILE_WIDTH;
	tile_clips[TILE_TOPRIGHT].h = TILE_HEIGHT;

	tile_clips[TILE_MIDRIGHT].x = 120;
	tile_clips[TILE_MIDRIGHT].y = 40;
	tile_clips[TILE_MIDRIGHT].w = TILE_WIDTH;
	tile_clips[TILE_MIDRIGHT].h = TILE_HEIGHT;

	tile_clips[TILE_BOTRIGHT].x = 120;
	tile_clips[TILE_BOTRIGHT].y = 80;
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

		SDL_Rect dst;
		dst.x = tile->tile_box.x;
		dst.y = tile->tile_box.y;
		dst.w = TILE_WIDTH;
		dst.h = TILE_HEIGHT;


		SDL_Rect src;
		src = tile_clips[tile_list[i].tile_type];
		SDL_RenderCopy(graphics_renderer, tilemap_tile, &src, &dst);

		if(tile_list[i].tile_buffer != NULL)
		{
			SDL_Rect srcb;
			srcb = tile_clips[tile_list[i].tile_buffer];
			SDL_RenderCopy(graphics_renderer, tilemap_tile, &srcb, &dst);
		}
	}
	tilemap_draw_sidemenu();
}

void tilemap_draw_sidemenu()
{
	Sprite *sidemenu = sprite_load("images/level_side_menu.png", 80, tilemap_height);
	sprite_draw(sidemenu, 0, tilemap_width, 0);
}

void tilemap_click()
{
	int x, y;
	SDL_GetMouseState( &x, &y );
	if(x > tilemap_width || y > tilemap_height)
	{
		menu_flag = true;
		tilemap_close_system();
		entity_free_all();
		return;
	}

	int mapX = x / TILE_WIDTH;
	int mapY = y / TILE_HEIGHT;
	int tile_pos = tilemap_tpl * mapY + mapX;


	Tile *tile = &tile_list[tile_pos];
	int type = tile->tile_buffer;
	
	if(tile->tile_type == TILE_HOLE || tile->tile_type == TILE_BLOCK)
	{
		return;
	}

	switch(type)
	{
	case TILE_RED:
		tile->tile_buffer = TILE_UP;
		break;
	case TILE_GREEN:
		tile->tile_buffer = TILE_UP;
		break;
	case TILE_BLUE:
		tile->tile_buffer = TILE_UP;
		break;
	case TILE_UP:
		tile->tile_buffer = TILE_RIGHT;
		break;
	case TILE_RIGHT:
		tile->tile_buffer = TILE_DOWN;
		break;
	case TILE_DOWN:
		tile->tile_buffer = TILE_LEFT;
		break;
	case TILE_LEFT:
		tile->tile_buffer = TILE_UP;
		break;
	}
}

void tilemap_remove_tile()
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
	tile->tile_buffer = NULL;
	
}

void tilemap_check_front_tile(Entity *entity) {
	int x = entity->position.x;
	int y = entity->position.y;

	int mapX = x / TILE_WIDTH;
	int mapY = y / TILE_HEIGHT;
	int tile_pos = tilemap_tpl * mapY + mapX;

	int tile_front = -1;
	Tile *tile_check;

	Sound *bump = sound_load_chunk("sounds/normal-hitfinish.wav");

	switch(entity->state)
	{
	case UP:
		if(tile_pos - tilemap_tpl > 0)
		{
			tile_front = tile_pos - tilemap_tpl;
		}
		break;
	case RIGHT:
		if(tile_pos + 1 % tilemap_tpl != 0 && tile_pos + 1 < TILE_MAX)
		{
			tile_front = tile_pos + 1;
		}
		break;
	case DOWN:
		if(tile_pos + tilemap_tpl < TILE_MAX)
		{
			tile_front = tile_pos + tilemap_tpl;
		}
		break;
	case LEFT:
		if(tile_pos % tilemap_tpl != 0 && tile_pos - 1 > 0)
		{
			tile_front = tile_pos - 1;
		}
		break;
	}

	if(tile_front != -1)
	{
		tile_check = &tile_list[tile_front];
		if(tile_check->tile_type == TILE_BLOCK)
		{
			Mix_PlayChannel(-1, bump->chunk, 0);
			switch(entity->state)
			{
			case UP:
				entity->state = RIGHT;
				break;
			case RIGHT:
				entity->state = DOWN;
				break;
			case DOWN:
				entity->state = LEFT;
				break;
			case LEFT:
				entity->state = UP;
				break;
			}
		}
	}
}

void tilemap_entity_on_special_tile(Entity *entity)
{
	int x = entity->position.x;
	int y = entity->position.y;
	Sound *fall = sound_load_chunk("sounds/spinnerspin.wav");
	Sound *change = sound_load_chunk("sounds/soft-hitnormal.wav");
	
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

	int type;
	if(tile->tile_buffer)
	{
		type = tile->tile_buffer;
	}
	else
	{
		type = tile->tile_type;
	}

	switch(type)
	{
	case TILE_UP:
		Mix_PlayChannel(-1, change->chunk, 0);
		entity->state = UP;
		break;
	case TILE_RIGHT:
		Mix_PlayChannel(-1, change->chunk, 0);
		entity->state = RIGHT;
		break;
	case TILE_DOWN:
		Mix_PlayChannel(-1, change->chunk, 0);
		entity->state = DOWN;
		break;
	case TILE_LEFT:
		Mix_PlayChannel(-1, change->chunk, 0);
		entity->state = LEFT;
		break;
	case TILE_HOLE:
		if(!entity->animal_type == HOVER_MOUSE)
		{
			Mix_PlayChannel(-1, fall->chunk, 0);
			entity->state = FAINT;
		}
		break;
	}
	tilemap_check_front_tile(entity);
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