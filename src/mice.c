#include "mice.h"

Entity *mice = NULL;

const int MICE_W = 40;
const int MICE_H = 40;
const int MICE_FRAME_W = 20;
const int MICE_FRAME_H = 20;

Sprite *mice_sprite;

typedef enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT
} miceStates;

void mice_initialize()
{
	Vect2d pos = {500, 500};
	mice_sprite = sprite_load("images/dot.png", MICE_FRAME_W, MICE_FRAME_H);
	
	mice = entity_new();
	mice->sprite = mice_sprite;
	mice->frameSize.x = 20;
	mice->frameSize.y = 20;
	mice->position.x = 200;
	mice->position.y = 0;
	mice->velocity = 20;
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
	SDL_Rect mice_bound;
	mice_bound.x = entity->position.x;
	mice_bound.y = entity->position.y;
	mice_bound.w = entity->frameSize.x;
	mice_bound.h = entity->frameSize.y;

	if(rect_intersect(tilemap_bound, mice_bound))
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
	}
	else
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
}