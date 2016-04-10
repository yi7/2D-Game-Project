#ifndef __SOUND_H__
#define __SOUND_H__

#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_mixer.h"
#include "simple_logger.h"

typedef struct Sound_S
{
	int inuse;
	char *filename;
	Mix_Music *music;
	Mix_Chunk *chunk;
} Sound;

void sound_initialize_system();
void sound_close_system();

Sound  *sound_load_music(char *filename);
Sound  *sound_load_chunk(char *filename);

void sound_play_music(Mix_Music *music);
void sound_play_chunk(Mix_Chunk *chunk);

#endif