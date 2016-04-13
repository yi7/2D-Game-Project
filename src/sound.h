#ifndef __SOUND_H__
#define __SOUND_H__

#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_mixer.h"
#include "simple_logger.h"

typedef struct Sound_S
{
	int inuse; /**<flag to check whether its in use or not*/
	char *filename; /**<the filename of the sound file*/
	Mix_Music *music; /**<the pointer to the music file*/
	Mix_Chunk *chunk; /**<the pointer to the chunk file*/
} Sound;

/**
 * @brief initializes the sound system
 */
void sound_initialize_system();

/**
 * @brief closes the sound system
 */
void sound_close_system();

/**
 * @brief loads the music into memory
 * @param filename the filename of the music to load
 */
Sound  *sound_load_music(char *filename);

/**
 * @brief loads the chunk into memory
 * @param filename the filename of the chunk to load
 */
Sound  *sound_load_chunk(char *filename);

/**
 * @brief plays the music
 * @param music the music to play
 */
void sound_play_music(Mix_Music *music);

/**
 * @brief plays the chunk
 * @param chunk the chunk to play
 */
void sound_play_chunk(Mix_Chunk *chunk);

#endif