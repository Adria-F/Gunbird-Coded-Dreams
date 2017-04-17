#ifndef __MODULESHOOTING_H__
#define __MODULESHOOTING_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleShooting : public Module
{
public:
	ModuleShooting();
	~ModuleShooting();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* texture_bullet = nullptr;
	SDL_Rect rect_bullet;
};

#endif
