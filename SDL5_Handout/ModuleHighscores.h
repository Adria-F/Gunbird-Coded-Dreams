#ifndef __MODULEHIGHSCORES_H__
#define __MODULEHIGHSCORES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleHighscores : public Module
{
public:
	ModuleHighscores();
	~ModuleHighscores();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	bool fading;
	int background_x;
	int background_y;
};

#endif // __MODULEHIGHSCORE_H__