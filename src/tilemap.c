#include "tilemap.h"

const int TILE_MAX		= 322; //20x12
const int TILE_WIDTH	= 40;
const int TILE_HEIGHT	= 40;

const int TILE_PLAIN		= 0;
const int TILE_HOME			= 1;
const int TILE_LEFT			= 2;
const int TILE_UP			= 3;
const int TILE_RIGHT		= 4;
const int TILE_DOWN			= 5;
const int TILE_MUD			= 6;
const int TILE_HOLE			= 7;
const int TILE_BLOCK		= 8;
const int TILE_REG			= 9;
const int TILE_HOVER		= 10;
const int TILE_SPEED		= 11;
const int TILE_MAX_SPRITES	= 12;

const int TILEMAP_WIDTH = 840;
const int TILEMAP_HEIGHT = 560;
const int tpl = 21;

int tilemap_arrow_count;
Tile *tile_list = NULL;
SDL_Texture *tilemap_tile = NULL;
SDL_Rect tile_clips[TILE_MAX_SPRITES];
SDL_Rect tilemap_bound;

char *animal_positions;
Sprite *play_button;
SDL_Rect play_box;
Sprite *reset_button;
SDL_Rect reset_box;
Sprite *back_button;
SDL_Rect back_box;

void tilemap_initialize_system(char *levelname, char *animal_pos)
{
	int i;
	animal_positions = animal_pos;
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
	tilemap_bound.w = TILEMAP_WIDTH;
	tilemap_bound.h = TILEMAP_HEIGHT;

	tilemap_load_animals();

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
		if(x >= TILEMAP_WIDTH)
		{
			x = 0;
			y += TILE_HEIGHT;
		}
	}

	fclose(fileptr);

	//clip the sprite sheet
	tile_clips[TILE_PLAIN].x = 0;
	tile_clips[TILE_PLAIN].y = 0;
	tile_clips[TILE_PLAIN].w = TILE_WIDTH;
	tile_clips[TILE_PLAIN].h = TILE_HEIGHT;

	tile_clips[TILE_HOME].x = 0;
	tile_clips[TILE_HOME].y = 40;
	tile_clips[TILE_HOME].w = TILE_WIDTH;
	tile_clips[TILE_HOME].h = TILE_HEIGHT;

	tile_clips[TILE_LEFT].x = 0;
	tile_clips[TILE_LEFT].y = 80;
	tile_clips[TILE_LEFT].w = TILE_WIDTH;
	tile_clips[TILE_LEFT].h = TILE_HEIGHT;

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

	tile_clips[TILE_MUD].x = 80;
	tile_clips[TILE_MUD].y = 0;
	tile_clips[TILE_MUD].w = TILE_WIDTH;
	tile_clips[TILE_MUD].h = TILE_HEIGHT;

	tile_clips[TILE_HOLE].x = 80;
	tile_clips[TILE_HOLE].y = 40;
	tile_clips[TILE_HOLE].w = TILE_WIDTH;
	tile_clips[TILE_HOLE].h = TILE_HEIGHT;

	tile_clips[TILE_BLOCK].x = 80;
	tile_clips[TILE_BLOCK].y = 80;
	tile_clips[TILE_BLOCK].w = TILE_WIDTH;
	tile_clips[TILE_BLOCK].h = TILE_HEIGHT;

	tile_clips[TILE_REG].x = 120;
	tile_clips[TILE_REG].y = 0;
	tile_clips[TILE_REG].w = TILE_WIDTH;
	tile_clips[TILE_REG].h = TILE_HEIGHT;

	tile_clips[TILE_HOVER].x = 120;
	tile_clips[TILE_HOVER].y = 40;
	tile_clips[TILE_HOVER].w = TILE_WIDTH;
	tile_clips[TILE_HOVER].h = TILE_HEIGHT;

	tile_clips[TILE_SPEED].x = 120;
	tile_clips[TILE_SPEED].y = 80;
	tile_clips[TILE_SPEED].w = TILE_WIDTH;
	tile_clips[TILE_SPEED].h = TILE_HEIGHT;
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
	Sprite *sidemenu = sprite_load("images/level_side_menu.png", 80, TILEMAP_HEIGHT);
	sprite_draw(sidemenu, 0, TILEMAP_WIDTH, 0);

	play_box.x = TILEMAP_WIDTH + 20;
	play_box.y = 20;
	play_box.w = 40;
	play_box.h = 40;
	play_button = sprite_load("images/buttons.png", play_box.w, play_box.h);
	reset_box.x = TILEMAP_WIDTH + 20;
	reset_box.y = 80;
	reset_box.w = 40;
	reset_box.h = 40;
	reset_button = sprite_load("images/buttons.png", reset_box.w, reset_box.h);
	back_box.x = TILEMAP_WIDTH + 20;
	back_box.y = TILEMAP_HEIGHT - 60;
	back_box.w = 80;
	back_box.h = 40;
	back_button = sprite_load("images/buttons.png", back_box.w, back_box.h);

	sprite_draw(play_button, 64, play_box.x, play_box.y);
	sprite_draw(reset_button, 65, reset_box.x, reset_box.y);
	sprite_draw(back_button, 66, back_box.x, back_box.y);	
}

void tilemap_click()
{
	int x, y;
	SDL_GetMouseState( &x, &y );

	SDL_Rect mouse = {x, y, 0, 0};

	if(x > TILEMAP_WIDTH || y > TILEMAP_HEIGHT)
	{
		if(rect_intersect(mouse, play_box))
		{
			return;
		}
		else if(rect_intersect(mouse, reset_box))
		{
			entity_free_all();
			tilemap_load_animals();
			return;
		}
		else if(rect_intersect(mouse, back_box))
		{
			menu_flag = true;
			tilemap_close_system();
			entity_free_all();
			return;
		}
		else
		{
			return;
		}
	}

	int mapX = x / TILE_WIDTH;
	int mapY = y / TILE_HEIGHT;
	int tile_pos = tpl * mapY + mapX;

	Tile *tile = &tile_list[tile_pos];
	int type = tile->tile_buffer;
	
	if(tile->tile_type == TILE_HOLE || tile->tile_type == TILE_BLOCK || tile->tile_type == TILE_MUD)
	{
		return;
	}

	switch(type)
	{
	case TILE_PLAIN:
		tile->tile_buffer = TILE_UP;
		break;
	case TILE_LEFT:
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
	}
}

void tilemap_remove_tile()
{
	int x, y;
	SDL_GetMouseState( &x, &y );
	
	if(x > TILEMAP_WIDTH || y > TILEMAP_HEIGHT)
	{
		slog("Not a valid tile");
		return;
	}

	int mapX = x / TILE_WIDTH;
	int mapY = y / TILE_HEIGHT;
	int tile_pos = tpl * mapY + mapX;


	Tile *tile = &tile_list[tile_pos];
	tile->tile_buffer = NULL;
	
}

void tilemap_check_front_tile(Entity *entity) {
	int x = entity->position.x;
	int y = entity->position.y;

	int mapX = x / TILE_WIDTH;
	int mapY = y / TILE_HEIGHT;
	int tile_pos = tpl * mapY + mapX;

	int tile_front = -1;
	Tile *tile_check;

	Sound *bump = sound_load_chunk("sounds/normal-hitfinish.wav");

	switch(entity->state)
	{
	case UP:
		if(tile_pos - tpl > 0)
		{
			tile_front = tile_pos - tpl;
		}
		break;
	case RIGHT:
		if(tile_pos + 1 % tpl != 0 && tile_pos + 1 < TILE_MAX)
		{
			tile_front = tile_pos + 1;
		}
		break;
	case DOWN:
		if(tile_pos + tpl < TILE_MAX)
		{
			tile_front = tile_pos + tpl;
		}
		break;
	case LEFT:
		if(tile_pos % tpl != 0 && tile_pos - 1 > 0)
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
	int tile_pos = tpl * mapY + mapX;
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
			entity->state = FREE;
		}
		break;
	
	}
	tilemap_check_front_tile(entity);
}

int tilemap_entity_out_of_bounds(Entity *entity)
{
	if( entity->position.x >= 0 &&
		entity->position.x + entity->frameSize.x <= TILEMAP_WIDTH &&
		entity->position.y >= 0 &&
		entity->position.y + entity->frameSize.y <= TILEMAP_HEIGHT )
		return 0;
	return 1;
}

void tilemap_load_animals()
{
	int x;
	int y;
	char dir[8];
	char animal_type[16];
	State direction;
	FILE *fileptr = NULL;

	fileptr = fopen(animal_positions, "r");
	if(!fileptr)
	{
		slog("Error: could not open animal position file");
		return;
	}

	while(fscanf(fileptr, "%d %d %s %s", &x, &y, dir, animal_type) != EOF)
	{
		if(strcmp(dir, "up") == 0)
		{
			direction = UP;
		}
		else if(strcmp(dir, "down") == 0)
		{
			direction = DOWN;
		}
		else if(strcmp(dir, "left") == 0)
		{
			direction = LEFT;
		}
		else if(strcmp(dir, "right") == 0)
		{
			direction = RIGHT;
		}

		animal_initialize(x, y, direction, animal_type);
	}
}