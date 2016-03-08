#include "cat.h"

const int CAT_W = 40;
const int CAT_H = 40;
const int CAT_FRAME_W = 40;
const int CAT_FRAME_H = 40;

Entity *cat = NULL;
Sprite *cat_sprite;

void cat_initialize()
{
	cat_sprite = sprite_load("images/dot.png", CAT_FRAME_W, CAT_FRAME_H);
	
	cat = entity_new();
	cat->sprite = cat_sprite;
	cat->frame = 0;
	cat->frameSize.x = CAT_FRAME_W;
	cat->frameSize.y = CAT_FRAME_H;
	cat->position.x = 0;
	cat->position.y = 0;
	cat->velocity = 2;
	cat->state = LEFT;

	cat->think = cat_think;
	cat->draw = cat_draw;
	cat->free = cat_free;
}

void cat_free(Entity *entity)
{
	entity_free(&entity);
}

void cat_draw(Entity *entity)
{
	//entity->frame = (entity->frame + 1) % 8;
	entity_draw(entity, entity->position.x, entity->position.y);
}

void cat_think(Entity *entity)
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

	cat_touch(entity);
	tilemap_entity_on_special_tile(entity);
}

void cat_touch(Entity *self)
{
	Entity *other;
	
	other = entity_intersect_all(self);
	if(!other)
	{
		return;
	}

	other->state = FAINT;
}