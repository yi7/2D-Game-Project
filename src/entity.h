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
	RIGHT,
	FREE
};

enum Type
{
	HOVER_MOUSE,
	SPEED_MOUSE,
	MOUSE,
	CAT
};

/**
 * @brief the core data structure for our entity system
 */
typedef struct Entity_S
{
	int inuse; /**<flag for tracking resource*/
	Vect2d position; /**<position of the entity*/
	Vect2d frameSize; /**<frame size of the entity*/
	int velocity; /**<velocity of the entity*/
	enum State state; /**<directional state of the entity*/
	enum Type animal_type; /**<what type of animal the entity is*/
	Sprite *sprite; /**<sprite associated with the entity*/
	int cameraEnt; /**<true if the entity is relative to the camera*/
	int frame; /**current frame of the entity*/
	void (*draw)(struct Entity_S *self); /**<draw function for entity*/
	int nextThink; /**<time index for next think*/
	int thinkRate; /**<how often to run think*/
	void (*think)(struct Entity_S *self); /**<think function for entity*/
	void (*update)(struct Entity_S *self); /**<update function for entity*/
	void (*touch)(struct Entity_S *self, struct Entity_S *other); /**<touch function for entity*/
	void (*free)(struct Entity_S *self); /**<cleanup function called on free*/
} Entity;

/**
 * @brief initializes entity system and queues up cleanup on exit
 */
void entity_initialize_system();

/**
 * @brief closes the entity system
 */
void entity_close_system();

/**
 * @brief returns a pointer to an empty entity structure
 * @return NULL on error or no more space for entities or a valid entity pointer otherwise
 */
Entity *entity_new();

/**
 * @brief frees a entity
 * @param entity the entity to be freed
 */
void entity_free(Entity **entity);

/**
 * @brief draws the entity
 * @param entity the entity to be drawn
 * @param drawX the x position of the entity to be drawn
 * @param drawY the y position of the entity to be drawn
 */
void entity_draw(Entity *entity, int drawX, int drawY);

/**
 * @brief checks whether two entities intersect with each other
 * @param a entity to check
 * @param b entity to check
 */
int entity_intersect(Entity *a, Entity *b);

/**
 * @brief calls all think functions of entities on the entity system
 */
void entity_think_all();

/**
 * @brief calls all draw functions of entities on the entity system
 */
void entity_draw_all();

/**
 * @brief calls all update function of entities on the entity system
 */
void entity_update_all();

/**
 * @brief checks whether the passed entity intersects with any entity on the entity system
 * @param self the entity to check whether its intersecting with others
 */
Entity *entity_intersect_all(Entity *self);

/**
 * @brief frees all entity on the entity system
 */
void entity_free_all();

#endif