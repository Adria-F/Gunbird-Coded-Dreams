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
	
	//background
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;

	//gturret
	SDL_Texture* graphics_gturret = nullptr;
	Animation gturret;
	Collider* rect_gturret;
	SDL_Rect rec_gturret;

	//building1
	SDL_Texture* graphics_buildings = nullptr;
	Animation build1;
	Collider* rect_build1;
	SDL_Rect rec_building1;

	//build1 down
	Animation build1down;
	SDL_Rect rec_build1down;

	//flag1
	Animation flag1;	
	SDL_Rect rec_flag1;

	//building2
	Animation build2;
	Collider* rect_build2;
	SDL_Rect rec_building2;
	//flag2
	Animation flag2;
	SDL_Rect rec_flag2;


	bool fading;
};

#endif // __MODULESCENECASTLE_H__