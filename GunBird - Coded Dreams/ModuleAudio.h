#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"

class ModuleAudio : public Module
{

public:
	ModuleAudio();
	virtual ~ModuleAudio();

	bool Load(const char* path);
	bool LoadFX(const char* path);
	void Play(int loop);
	void PlayFX(int loop);
	void Stop();

	bool Init();
	bool CleanUp();

public:
	Mix_Music* music = nullptr;
	Mix_Music* effect = nullptr;
};
#endif