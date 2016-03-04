#include "entity.h"

static Entity *entity_list = NULL;
const int ENTITY_MAX = 1000;

void entity_initialize_system()
{
	entity_list = (Entity *)malloc(sizeof(Entity) * ENTITY_MAX);
	if(!entity_list)
	{
		slog("failed to allocate Entity system");
		return;
	}

	memset(entity_list, 0, sizeof(Entity) * ENTITY_MAX);
	atexit(entity_close_system);
}

void entity_close_system()
{
	int i;
	Entity *entity;
	for(i = 0; i < ENTITY_MAX; i++)
	{
		entity = &entity_list[i];
		if(entity->inuse)
		{
			entity_free(&entity);
		}
	}
	free(entity_list);
}

Entity *entity_new()
{
	int i;
	for(i = 0; i < ENTITY_MAX; i++)
	{
		if(entity_list[i].inuse)
		{
			continue;
		}

		memset(&entity_list[i], 0, sizeof(Entity));
		entity_list[i].inuse = 1;
		return &entity_list[i];
	}

	return NULL;
}

void entity_free(Entity **entity)
{
	Entity *self;

	if(!entity) return;
	if(!*entity) return;
	self = *entity;

	sprite_free(&self->sprite);
	*entity = NULL;
}

void entity_draw(Entity *ent, int drawX, int drawY)
{

	if(!ent)
	{
		slog("Error: no entity to draw");
		return;
	}
	if(!ent->sprite)
	{
		slog("Error: entity has no sprite");
		return;
	}

	sprite_draw(ent->sprite, ent->frame, drawX, drawY);
}

int entity_intersect(Entity *a, Entity *b)
{
	SDL_Rect aBox;
	SDL_Rect bBox;

	aBox.x = a->position.x;
	aBox.y = a->position.y;
	aBox.w = a->sprite->frameSize.x;
	aBox.h = a->sprite->frameSize.y;

	bBox.x = b->position.x;
	bBox.y = b->position.y;
	bBox.w = b->sprite->frameSize.x;
	bBox.h = b->sprite->frameSize.y;

	return rect_intersect(aBox, bBox);
}

void entity_think_all()
{
	int i;
	for(i = 0; i < ENTITY_MAX; i++)
	{
		if(!entity_list[i].inuse)
		{
			continue;
		}

		if(!entity_list[i].think)
		{
			continue;
		}

		entity_list[i].think(&entity_list[i]);
	}
}

void entity_draw_all()
{
	int i;
	for(i = 0; i < ENTITY_MAX; i++)
	{
		if(!entity_list[i].inuse)
		{
			continue;
		}

		if(!entity_list[i].draw)
		{
			continue;
		}

		entity_list[i].draw(&entity_list[i]);
	}
}

void entity_update_all()
{
	int i;
	for(i = 0; i < ENTITY_MAX; i++)
	{
		if(!entity_list[i].inuse)
		{
			continue;
		}

		//vec2d_add(entity_list[i].position, entity_list[i].velocity, entity_list[i].position);

		if(!entity_list[i].update)
		{
			continue;
		}

		entity_list[i].update(&entity_list[i]);
	}
}

/*Entity *entity_intersect_all(Entity *a)
{
	int i;
	if(!a) return NULL;
	for(i = 0; i < ENTITY_MAX; i++)
	{
		if(!entity_list[i].inuse)
		{
			continue;
		}
		if(a == &entity_list[i])
		{
			continue;
			//don't clip self
		}
		if(entity_intersect(a, &entity_list[i]))
		{
			return &entity_list[i];
		}
	}
	return NULL;
}*/