
#ifndef __MODULEWELCOMETITLE_H__
#define __MODULEWELCOMETITLE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleWelcomeTitle : public Module
{
public:
	ModuleWelcomeTitle();
	~ModuleWelcomeTitle();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	Animation credits_anim;

	bool fading;
};

#endif // __MODULEWELCOMETITLE_H__