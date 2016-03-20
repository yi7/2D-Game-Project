#include "cat.h"

const int CAT_W = 40;
const int CAT_H = 40;
const int CAT_FRAME_W = 40;
const int CAT_FRAME_H = 40;

Uint32 cat_now;
Entity *cat = NULL;
Sprite *cat_sprite;

void cat_initialize()
{
	cat_now = SDL_GetTicks();
	cat_sprite = sprite_load("images/reg_cat_sprite.png", CAT_FRAME_W, CAT_FRAME_H);
	
	cat = entity_new();
	cat->sprite = cat_sprite;
	cat->frame = 0;
	cat->frameSize.x = CAT_FRAME_W;
	cat->frameSize.y = CAT_FRAME_H;
	cat->position.x = 0;
	cat->position.y = 0;
	cat->velocity = 2;
	cat->state = LEFT;

	cat->free = cat_free;
	cat->think = cat_think;
	cat->draw = cat_draw;
}

void cat_free(Entity *entity)
{
	entity_free(&entity);
}

void cat_draw(Entity *entity)
{
	int frame = ((SDL_GetTicks() - cat_now) * 7 / 1000) % 8;
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