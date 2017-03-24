#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio()
{
}


ModuleAudio::~ModuleAudio()
{
}

bool ModuleAudio::Init()
{
	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	return true;
}

void ModuleAudio::Play()
{
	Mix_PlayMusic(music, -1);
}

void ModuleAudio::Stop()
{
	Mix_HaltMusic();
}

bool ModuleAudio::Load(const char* path)
{
	music = Mix_LoadMUS(path);

	return true;
}

bool ModuleAudio::CleanUp()
{
	return true;
}
