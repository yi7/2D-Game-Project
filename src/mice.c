#include "mice.h"

Entity *mice = NULL;

const int MICE_W = 40;
const int MICE_H = 40;
const int MICE_FRAME_W = 40;
const int MICE_FRAME_H = 40;

Sprite *mice_sprite;

void mice_initialize()
{
	Vect2d pos = {500, 500};
	mice_sprite = sprite_load("images/HP_1.png", MICE_FRAME_W, MICE_FRAME_H);
	
	mice = entity_new();
	mice->sprite = mice_sprite;
	mice->frame = 0;
	mice->frameSize.x = MICE_FRAME_W;
	mice->frameSize.y = MICE_FRAME_H;
	mice->position.x = 400;
	mice->position.y = 0;
	mice->velocity = 2;
	mice->direction = UP;

	mice->think = mice_think;
	mice->draw = mice_draw;
}

void mice_draw(Entity *entity)
{
	entity_draw(entity, entity->position.x, entity->position.y);
}

void mice_think(Entity *entity)
{
	if(entity->direction == UP)
	{
		entity->position.y -= entity->velocity;
	}
	else if(entity->direction == DOWN)
	{
		entity->position.y += entity->velocity;
	}
	else if(entity->direction == LEFT)
	{
		entity->position.x -= entity->velocity;
	}
	else if(entity->direction == RIGHT)
	{
		entity->position.x += entity->velocity;
	}


	if(tilemap_entity_out_of_bounds(entity))
	{
		if(entity->direction == UP)
		{
			entity->position.y += entity->velocity;
			entity->direction = RIGHT;
		}
		else if(entity->direction == DOWN)
		{
			entity->position.y -= entity->velocity;
			entity->direction = LEFT;
		}
		else if(entity->direction == LEFT)
		{
			entity->position.x += entity->velocity;
			entity->direction = UP;
		}
		else if(entity->direction == RIGHT)
		{
			entity->position.x -= entity->velocity;
			entity->direction = DOWN;
		}
	}

	tilemap_entity_on_special_tile(entity);
}