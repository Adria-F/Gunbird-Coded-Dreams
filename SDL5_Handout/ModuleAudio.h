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
	void Play();
	void Stop();

	bool Init();
	bool CleanUp();
public:
	Mix_Music* music = nullptr;
};
#endif