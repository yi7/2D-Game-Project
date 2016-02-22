#include <string>
#include <string.h>
#include <stdlib.h>

#include "entity.h"
#include "simple_logger.h"

static Entity *entity_list = NULL;
static int entity_max = 0;

void entity_close_system();

void entity_initialize_system(int entityMax)
{
	if(entityMax == 0)
	{
		slog("cannot allocate zero Entities!");
		return;
	}

	entity_list = (Entity *)malloc(sizeof(Entity) * entityMax);
	if(!entity_list)
	{
		slog("failed to allocate Entity system");
		return;
	}

	memset(entity_list, 0, sizeof(Entity) * entityMax);
	entity_max = entityMax;
	atexit(entity_close_system);
}

void entity_close_system()
{
	int i;
	Entity *entity;
	for(i = 0; i < entity_max; i++)
	{
		entity = &entity_list[i];
		entity_free(&entity);
	}
	free(entity_list);
}

Entity *entity_new()
{
	int i;
	for(i = 0; i < entity_max; i++)
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

void entity_think_all()
{
	int i;
	for(i = 0; i < entity_max; i++)
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

void entity_update_all()
{
	int i;
	for(i = 0; i < entity_max; i++)
	{
		if(!entity_list[i].inuse)
		{
			continue;
		}

		vec2d_add(entity_list[i].position, entity_list[i].velocity, entity_list[i].position);

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
	for(i = 0; i < entity_max; i++)
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
}

int entity_intersect(Entity *a, Entity *b)
{
	SDL_Rect aB, bB;

	if((!a) || (!b))
	{
		slog("ErrorL missing entity for check");
		return 0;
	}

	aB = rect(
		a->position.x + a->bounds.x,
		a->position.y + a->bounds.y,
		a->bounds.w,
		a->bounds.h);
	bB = rect(
		b->position.x + b->bounds.x,
		b->position.y + b->bounds.y,
		b->bounds.w,
		b->bounds.h);
}*/