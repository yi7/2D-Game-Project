#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "SDL.h"

/**
 * @brief a simple 2d vector structure
 */
typedef struct
{
	float x; /**<the x component of the vector*/
	float y; /**<the y component of the vector*/
} Vect2d;

typedef struct
{
	union {
		float x; /**<the x component of the vector*/
		float r; /**<the red component of the color*/
	};
	union {
		float y; /**<the y component of the vector*/
		float g; /**<the green component of the color*/
	};
	union {
		float z; /**<the z component of the vector*/
		float b; /**<the blue component of the color*/
	};
} Vect3d;

typedef struct
{
	union {float x; float r;};
	union {float y; float g;};
	union {float z; float b;};
	union {float w; float a;};
} Vect4d;

/**
 * @brief check if two rectangles intersect
 */
int rect_intersect(SDL_Rect a, SDL_Rect b);

#define ZERO 0

#define vec2d_add(a,b,c) (c.x=a.x+b.x,c.y=a.y+b.y);
#define vec3d_add(a,b,c) (c.x=a.x+b.x,c.y=a.y+b.y,c.z=a.z+b.z);
#define vec4d_add(a,b,c) (c.x=a.x+b.x,c.y=a.y+b.y,c.z=a.z+b.z,c.w=a.w+b.w);

#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)

#endif