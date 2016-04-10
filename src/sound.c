#include "sound.h"

static Sound *sound_list = NULL;
const int SOUND_MAX = 500;

void sound_initialize_system()
{
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	sound_list = (Sound *) malloc(sizeof(Sound) * SOUND_MAX);
	if(!sound_list)
	{
		slog("failed to allocate Sound system");
		return;
	}
	memset(sound_list, 0, sizeof(Sound) * SOUND_MAX);

	atexit(sound_close_system);
}

void sound_close_system()
{
	if(!sound_list)
	{
		return;
	}

	free(sound_list);
	sound_list = NULL;
}

Sound *sound_load_music(char *filename)
{
	int i;

	for(i = 0; i < SOUND_MAX; i++)
	{
		if(sound_list[i].inuse)
		{
			if(strcmp(filename, sound_list[i].filename) == 0)
			{
				return &sound_list[i];
			}
			continue;
		}
		memset(&sound_list[i], 0, sizeof(Sound));
		sound_list[i].inuse = 1;
		sound_list[i].filename = filename;
		sound_list[i].music = Mix_LoadMUS(filename);
		return &sound_list[i];
	}

	return NULL;
}

Sound *sound_load_chunk(char *filename)
{
	int i;

	for(i = 0; i < SOUND_MAX; i++)
	{
		if(sound_list[i].inuse)
		{
			if(strcmp(filename, sound_list[i].filename) == 0)
			{
				return &sound_list[i];
			}
			continue;
		}
		memset(&sound_list[i], 0, sizeof(Sound));
		sound_list[i].inuse = 1;
		sound_list[i].filename = filename;
		sound_list[i].chunk = Mix_LoadWAV(filename);
		return &sound_list[i];
	}

	return NULL;
}

void sound_play_music(Mix_Music *music)
{
	Mix_PlayMusic(music, 0);
}

void sound_play_chunk(Mix_Chunk *chunk)
{
	Mix_PlayChannel(-1, chunk, 0);
}
