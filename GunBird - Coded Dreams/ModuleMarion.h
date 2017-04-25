#ifndef __ModuleMarion_H__
#define __ModuleMarion_H__

#include "Module.h"
#include "ModulePlayer.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleMarion : public ModulePlayer
{
public:
	ModuleMarion();
	~ModuleMarion();

	bool Start();
	update_status Update();
	bool CleanUp();

	Uint32 onhit_start_time = 0;
	Uint32 onhit_total_time = (Uint32)(2.0f * 0.5f * 2000.0f);
	Uint32 onhit_now;

	void OnCollision(Collider* c1, Collider* c2);

public:
	Animation stele1;
	Animation stele2;
	Animation stele3;

};

#endif