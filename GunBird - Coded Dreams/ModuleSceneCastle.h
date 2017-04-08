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
	SDL_Texture* graphics_build1 = nullptr;
	Animation build1;
	Collider* rect_build1;
	SDL_Rect rec_building1;
	//flag1
	Animation flag1;	
	SDL_Rect rec_flag1;



	bool fading;
};

#endif // __MODULESCENECASTLE_H__