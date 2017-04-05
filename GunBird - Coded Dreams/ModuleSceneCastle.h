#ifndef __MODULESCENECASTLE_H__
#define __MODULESCENECASTLE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
struct Collider;

class ModuleSceneCastle : public Module
{
public:
	ModuleSceneCastle();
	~ModuleSceneCastle();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics_gturret = nullptr;
	Animation gturret;
	Collider* rect_gturret;
	SDL_Rect background;
	SDL_Rect rec_gturret;
	bool fading;
};

#endif // __MODULESCENECASTLE_H__