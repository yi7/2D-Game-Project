#include "sprite.h"

static Sprite *sprite_list = NULL;
const int SPRITE_MAX = 1000;
int sprite_num;
//extern SDL_Renderer *graphics_renderer;

struct
{
	Uint32 state;
	Uint32 shown;
	Uint32 frame;
	Uint16 x, y;
} Mouse;

Sprite *sprite_mouse;

void sprite_initialize_system()
{
	sprite_list = (Sprite *)malloc(sizeof(Sprite) * SPRITE_MAX);
	if(!sprite_list)
	{
		slog("Error: failed to allocate sprite system.");
        return;
	}
	
	memset(sprite_list, 0, sizeof(Sprite) * SPRITE_MAX);
	sprite_num = 0;
	atexit(sprite_close_system);
}

void sprite_close_system()
{
	int i;
    if (!sprite_list)
    {
        return;
    }

    for (i = 0; i < SPRITE_MAX; i++)
    {
        if (sprite_list[i].image != 0)
        {
            SDL_DestroyTexture(sprite_list[i].image);
        }
    }

    free(sprite_list);
    sprite_list = NULL;
}

Sprite *sprite_load(char *filename, int frameW, int frameH)
{
	int i;
	SDL_Surface *temp;

	if(!sprite_list)
	{
		slog("error: using sprite system uninitialized");
        return NULL;
	}

	/*first search to see if the requested sprite image is alreday loaded*/
	for(i = 0; i < SPRITE_MAX; i++)
	{
		if (sprite_list[i].refCount == 0)
        {
            continue;
        }
		if(strcmp(filename, sprite_list[i].filename) == 0)
		{
			sprite_list[i].refCount++;
			return &sprite_list[i];
		}
	}

	/*makesure we have the room for a new sprite*/
	if(sprite_num + 1 >= SPRITE_MAX)
	{
		slog("Maximum Sprites Reached.\n");
		exit(1);
	}
	sprite_num++;

	/*if its not already in memory, then load it.*/
	for(i = 0; i <= sprite_num; i++)
	{
		if(!sprite_list[i].refCount)
			break;
	}
	temp = IMG_Load(filename);
	if(!temp)
	{
		slog("unable to load a vital sprite: %s\n", SDL_GetError());
		exit(0);
	}

	/*sets a transparent color for blitting.*/
	SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 255,255,255));

	sprite_list[i].image = SDL_CreateTextureFromSurface(graphics_renderer, temp);
	SDL_FreeSurface(temp);

	/*then copy the given information to the sprite*/
	strcpy(sprite_list[i].filename, filename);

	/*now sprites don't have to be 16 frames per line, but most will be.*/
	sprite_list[i].fpl = 16;
	sprite_list[i].frameSize.x = frameW;
	sprite_list[i].frameSize.y = frameH;
	sprite_list[i].refCount++;
	return &sprite_list[i];
}

void sprite_free(Sprite **sprite)
{
	Sprite *self;

	if(!sprite) return;
	if(!*sprite) return;

	self = *sprite;
	self->refCount--;

	if(self->refCount <= 0)
	{
		SDL_DestroyTexture(self->image);
		memset(self, 0, sizeof(Sprite));
	}

	*sprite = NULL;
}

void sprite_draw(Sprite *sprite, int frame, int frameW, int frameH)
{
	SDL_Rect src, dest;
	if ((!sprite) || (!graphics_renderer))
		return;
	src.x = frame % sprite->fpl * sprite->frameSize.x;
	src.y = frame / sprite->fpl * sprite->frameSize.y;
	src.w = sprite->frameSize.x;
	src.h = sprite->frameSize.y;
	dest.x = frameW;
	dest.y = frameH;
	dest.w = sprite->frameSize.x;
	dest.h = sprite->frameSize.y;
	SDL_RenderCopy(graphics_renderer, sprite->image, &src, &dest);  
}

void sprite_initialize_mouse()
{
	sprite_mouse = sprite_load("images/mouse.png", 16, 16);
	if(!sprite_mouse)
	{
		slog("Error: could not initialize mouse");
	}
	Mouse.state = 0;
	Mouse.shown = 0;
	Mouse.frame = 0;
}

void sprite_draw_mouse()
{
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	if(sprite_mouse)
	{
		sprite_draw(sprite_mouse, Mouse.frame, mx, my);
	}
	Mouse.frame = (Mouse.frame + 1) % 16;
	Mouse.x = mx;
	Mouse.y = my;
}