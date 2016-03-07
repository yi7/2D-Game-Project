#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "string.h"
#include "stdlib.h"

#include "camera.h"
#include "graphics.h"
#include "simple_logger.h"
#include "sprite.h"
#include "vector.h"

enum State
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

/**
 * @brief the core data structure for our entity system
 */
typedef struct Entity_S
{
	int inuse; /**<flag for tracking resource*/
	Vect2d position;
	Vect2d frameSize;
	int velocity;
	enum State state;
	Sprite *sprite;
	int cameraEnt; /**<true if the entity is relative to the camera*/
	int frame;
	void (*draw)(struct Entity_S *self);
	int nextThink; /**<time index for next think*/
	int thinkRate; /**<how often to run think*/
	void (*think)(struct Entity_S *self); /**<think function for entity*/
	void (*update)(struct Entity_S *self);
	void (*touch)(struct Entity_S *self, struct Entity_S *other);
	void (*free)(struct Entity_S *self); /**<cleanup function called on free*/
} Entity;

/**
 * @brief initializes entity system and queues up cleanup on exit
 */
void entity_initialize_system();

void entity_close_system();

/**
 * @brief returns a pointer to an empty entity structure
 * @return NULL on error or no more space for entities or a valid entity pointer otherwise
 */
Entity *entity_new();

void entity_free(Entity **entity);
void entity_draw(Entity *entity, int drawX, int drawY);
int entity_intersect(Entity *a, Entity *b);
void entity_think(Entity *entity);

void entity_think_all();
void entity_draw_all();
void entity_update_all();
void entity_intersect_all(Entity *self);

/*int entity_intersect(Entity *a, Entity *b);
Rect rect(int a, int b, int c, int d);*/

#endif