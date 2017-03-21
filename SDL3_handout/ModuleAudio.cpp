#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() : Module()
{
}


ModuleAudio::~ModuleAudio()
{
}

bool ModuleAudio::Init()
{
	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Load("assets/music/mine.ogg");
	Mix_PlayMusic(music, -1);

	return true;
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




