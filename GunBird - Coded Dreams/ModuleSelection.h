#ifndef __MODULESELECTION_H__
#define __MODULESELECTION_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSelection : public Module
{
public:
	ModuleSelection();
	~ModuleSelection();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	bool fading;
};

#endif // __MODULESELECTION_H__