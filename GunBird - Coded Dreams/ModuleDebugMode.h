#ifndef __MODULEDEBUGMODE_H__
#define __MODULEDEBUGMODE_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleDebugMode : public Module
{
public:
	ModuleDebugMode();
	~ModuleDebugMode();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* debugging_on = nullptr;
	SDL_Rect notifier;
	bool debugging = false;
};

#endif // __MODULEDEBUGMODE_H__