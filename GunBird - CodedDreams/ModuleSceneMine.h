#ifndef __MODULESCENEMINE_H__
#define __MODULESCENEMINE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneMine : public Module
{
public:
	ModuleSceneMine();
	~ModuleSceneMine();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics_background_text = nullptr;
	SDL_Texture* graphics_above_background_text = nullptr;

	SDL_Rect background_rect;
	SDL_Rect above_background_rect;
	float overlay_position;
	float overlay_speed = 0.09f;
	bool lost = false;

	bool fading;
};

#endif // __MODULESCENEMINE_H__