#include "animal.h"

Uint32 animal_now;
Entity *animal = NULL;

const int ANIMAL_FRAME_W = 40;
const int ANIMAL_FRAME_H = 40;

void animal_initialize(int x, int y, State direction, char *type)
{
	/*State direction;
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
	}*/

	if(strcmp(type, "normal_mouse") == 0)
	{
		animal_initialize_normalmouse(x, y, direction);
	}
	else if(strcmp(type, "hover_mouse") == 0)
	{
		animal_initialize_hovermouse(x, y, direction);
	}
	else if(strcmp(type, "speed_mouse") == 0)
	{
		animal_initialize_speedmouse(x, y, direction);
	}
	else if(strcmp(type, "normal_cat") == 0)
	{
		animal_initialize_normalcat(x, y, direction);
	}
}

void animal_initialize_hovermouse(int x, int y, State direction)
{
	animal_now = SDL_GetTicks();
	Sprite *animal_sprite = sprite_load("images/hover_mouse_sprite.png", ANIMAL_FRAME_W, ANIMAL_FRAME_H);
	
	animal = entity_new();
	animal->sprite = animal_sprite;
	animal->frame = 0;
	animal->frameSize.x = ANIMAL_FRAME_W;
	animal->frameSize.y = ANIMAL_FRAME_H;
	animal->position.x = x;
	animal->position.y = y;
	animal->velocity = 0;
	animal->state = direction;
	animal->animal_type = HOVER_MOUSE;
	animal->free = animal_free;
	animal->think = animal_think;
	animal->draw = animal_draw;
}

void animal_initialize_speedmouse(int x, int y, State direction)
{
	animal_now = SDL_GetTicks();
	Sprite *animal_sprite = sprite_load("images/race_mouse_sprite.png", ANIMAL_FRAME_W, ANIMAL_FRAME_H);
	
	animal = entity_new();
	animal->sprite = animal_sprite;
	animal->frame = 0;
	animal->frameSize.x = ANIMAL_FRAME_W;
	animal->frameSize.y = ANIMAL_FRAME_H;
	animal->position.x = x;
	animal->position.y = y;
	animal->velocity = 0;
	animal->state = direction;
	animal->animal_type = SPEED_MOUSE;
	animal->free = animal_free;
	animal->think = animal_think;
	animal->draw = animal_draw;
}

void animal_initialize_normalmouse(int x, int y, State direction)
{
	animal_now = SDL_GetTicks();
	Sprite *animal_sprite = sprite_load("images/reg_mouse_sprite.png", ANIMAL_FRAME_W, ANIMAL_FRAME_H);
	
	animal = entity_new();
	animal->sprite = animal_sprite;
	animal->frame = 0;
	animal->frameSize.x = ANIMAL_FRAME_W;
	animal->frameSize.y = ANIMAL_FRAME_H;
	animal->position.x = x;
	animal->position.y = y;
	animal->velocity = 0;
	animal->state = direction;
	animal->animal_type = MOUSE;
	animal->free = animal_free;
	animal->think = animal_think;
	animal->draw = animal_draw;
}

void animal_initialize_normalcat(int x, int y, State direction)
{
	animal_now = SDL_GetTicks();
	Sprite *animal_sprite = sprite_load("images/reg_cat_sprite.png", ANIMAL_FRAME_W, ANIMAL_FRAME_H);
	
	animal = entity_new();
	animal->sprite = animal_sprite;
	animal->frame = 0;
	animal->frameSize.x = ANIMAL_FRAME_W;
	animal->frameSize.y = ANIMAL_FRAME_H;
	animal->position.x = x;
	animal->position.y = y;
	animal->velocity = 0;
	animal->state = direction;
	animal->animal_type = CAT;
	animal->free = animal_free;
	animal->think = animal_think;
	animal->draw = animal_draw;
}

void animal_free(Entity *entity)
{
	entity_free(&entity);
}

void animal_draw(Entity *entity)
{
	int frame = ((SDL_GetTicks() - animal_now) * 7 / 1000) % 8;
	switch(entity->state)
	{
	case UP:
		entity->frame = frame;
		entity_draw(entity, entity->position.x, entity->position.y);
		break;
	case RIGHT:
		entity->frame = frame + 16;
		entity_draw(entity, entity->position.x, entity->position.y);
		break;
	case DOWN:
		entity->frame = frame + 32;
		entity_draw(entity, entity->position.x, entity->position.y);
		break;
	case LEFT:
		entity->frame = frame + 48;
		entity_draw(entity, entity->position.x, entity->position.y);
		break;
	case FREE:
		entity->frame = 0;
		entity_draw(entity, entity->position.x, entity->position.y);
		break;
	}
}

void animal_think(Entity *entity)
{
	if(entity->state == UP)
	{
		entity->position.y -= entity->velocity;
	}
	else if(entity->state == DOWN)
	{
		entity->position.y += entity->velocity;
	}
	else if(entity->state == LEFT)
	{
		entity->position.x -= entity->velocity;
	}
	else if(entity->state == RIGHT)
	{
		entity->position.x += entity->velocity;
	}
	else if(entity->state == FREE)
	{
		entity->free(entity);
		return;
	}


	if(tilemap_entity_out_of_bounds(entity))
	{
		if(entity->state == UP)
		{
			entity->position.y += entity->velocity;
			entity->state = RIGHT;
		}
		else if(entity->state == DOWN)
		{
			entity->position.y -= entity->velocity;
			entity->state = LEFT;
		}
		else if(entity->state == LEFT)
		{
			entity->position.x += entity->velocity;
			entity->state = UP;
		}
		else if(entity->state == RIGHT)
		{
			entity->position.x -= entity->velocity;
			entity->state = DOWN;
		}
	}

	animal_touch(entity);
	tilemap_entity_on_special_tile(entity);
}

void animal_touch(Entity *self)
{
	Entity *other;
	
	if(self->animal_type != CAT)
	{
		return;
	}

	other = entity_intersect_all(self);
	if(!other)
	{
		return;
	}

	other->state = FREE;
}