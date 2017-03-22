#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect ship;
	Animation flag;
	Animation pink_girl;
	Animation two_men;
	Animation green_man;
	Animation blue_man;
	Animation brown_man;
	Animation purple_man;

private:

	bool boat_up;
	int boat_delay;
	int float_variation;
};

#endif