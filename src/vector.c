#include "vector.h"

/*SDL_Rect rect(int x, int y, int w, int h)
{
	Sdl_Rect
}*/

int rect_intersect(SDL_Rect a, SDL_Rect b)
{
	if( (a.x + a.w > b.x) &&
		(b.x + b.w > a.x) &&
		(a.y + a.h > b.y) &&
		(b.y + b.h > a.y))
		return 1;
	return 0;
}