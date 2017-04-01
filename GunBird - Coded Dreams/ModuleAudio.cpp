#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )
//Josep: I've created a new music called effect so I can put different sounds in the game. It dosn't work :(
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

void ModuleAudio::Play(int loop)
{
	Mix_PlayMusic(music, loop);
}

void ModuleAudio::PlayFX(int loop)
{
	Mix_PlayMusic(effect, loop);
}

void ModuleAudio::Stop()
{
	Mix_FreeMusic(music);
	Mix_FreeMusic(effect);
	music = nullptr;
	effect = nullptr;
	Mix_HaltMusic();
}

bool ModuleAudio::Load(const char* path)
{
	music = Mix_LoadMUS(path);

	return true;
}

bool ModuleAudio::LoadFX(const char* path)
{
	effect = Mix_LoadMUS(path);

	return true;
}

bool ModuleAudio::CleanUp()
{
	return true;
}
