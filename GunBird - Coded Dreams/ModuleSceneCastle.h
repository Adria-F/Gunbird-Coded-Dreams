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
	SDL_Texture* texture_bg = nullptr;
	SDL_Rect rect_background;

	//upper background
	SDL_Texture* texture_bg_upper = nullptr;
	SDL_Rect rect_background_upper;
	
	//First river
	SDL_Texture* texture_1_river = nullptr;
	Animation anim_1_river;
	SDL_Rect rect_1_river;

	//Second river
	SDL_Texture* texture_2_river = nullptr;
	Animation anim_2_river;
	SDL_Rect rect_2_river;

	//Bridge
	SDL_Texture* texture_bridge = nullptr;
	Animation anim_bridge;
	SDL_Rect rect_bridge;
	
	//gturret
	SDL_Texture* texture_gturret = nullptr;
	Animation anim_gturret;
	Collider* coll_gturret;
	SDL_Rect rect_gturret;

	//building1
	SDL_Texture* texture_buildings = nullptr;
	Animation anim_build1;
	Collider* coll_build1;
	SDL_Rect rect_building1;

	//build1 down
	//Animation anim_build1down;
	//SDL_Rect rect_build1down;

	//building2
	Animation anim_build2;
	Collider* coll_build2;
	SDL_Rect rect_building2;

	//knights
	SDL_Texture* texture_knight = nullptr;

	//up
	Animation anim_knight_up;
	SDL_Rect rect_knight_up;

	bool fading;
};

#endif // __MODULESCENECASTLE_H__