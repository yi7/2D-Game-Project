#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "vector.h"
#include "sprite.h"

/**
 * @brief the core data structure for our entity system
 */
typedef struct Entity_S
{
	int inuse; /**<flag for tracking resource*/
	Vect2d position;
	Vect2d velocity;
	Sprite *sprite;
	int frame;
	float health, maxhealth;
	void (*draw)(struct Entity_S *self, SDL_Renderer *renderer);
	int nextThink; /**<time index for next think*/
	int thinkRate; /**<how often to run think*/
	void (*think)(struct Entity_S *self); /**<think function for entity*/
	void (*update)(struct Entity_S *self);
	void (*touch)(struct Entity_S *self, struct Entity_S *other);
	void (*free)(struct Entity_S *self); /**<cleanup function called on free*/
} Entity;

/**
 * @brief initializes entity system and queues up cleanup on exit
 * @param maxEntities how many entities the system should support. Should not be zero
 */
void entity_initialize_system(Uint32 entityMax);

void entity_close_system();

/**
 * @brief returns a pointer to an empty entity structure
 * @return NULL on error or no more space for entities or a valid entity pointer otherwise
 */
Entity *entity_new();


void entity_free(Entity **entity);

void entity_think_all();
void entity_update_all();
void entity_draw_all();

bool entity_draw(Entity *entity, int frame, SDL_Renderer *renderer, int frameW, int frameH);

/*int entity_intersect(Entity *a, Entity *b);
Rect rect(int a, int b, int c, int d);*/

#endif