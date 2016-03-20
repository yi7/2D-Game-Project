#include "mice.h"

const int MICE_W = 40;
const int MICE_H = 40;
const int MICE_FRAME_W = 40;
const int MICE_FRAME_H = 40;

Uint32 mice_now;
Entity *mice = NULL;
Sprite *mice_sprite;

void mice_initialize()
{
	mice_now = SDL_GetTicks();

	mice_sprite = sprite_load("images/hover_mouse_sprite.png", MICE_FRAME_W, MICE_FRAME_H);
	
	mice = entity_new();
	mice->sprite = mice_sprite;
	mice->frame = 0;
	mice->frameSize.x = MICE_FRAME_W;
	mice->frameSize.y = MICE_FRAME_H;
	mice->position.x = 400;
	mice->position.y = 0;
	mice->velocity = 2;
	mice->state = UP;

	mice->free = mice_free;
	mice->think = mice_think;
	mice->draw = mice_draw;
}

void mice_free(Entity *entity)
{
	entity_free(&entity);
}

void mice_draw(Entity *entity)
{
	int frame = ((SDL_GetTicks() - mice_now) * 7 / 1000) % 8;
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
	case FAINT:
		entity->frame = 0;
		entity_draw(entity, entity->position.x, entity->position.y);
		break;
	}
}

void mice_think(Entity *entity)
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
	else if(entity->state == FAINT)
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

	tilemap_entity_on_special_tile(entity);
}