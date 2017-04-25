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

	void OnCollision(Collider* c1, Collider* c2);

public:
	Animation stele1;
	Animation stele2;
	Animation stele3;

};

#endif