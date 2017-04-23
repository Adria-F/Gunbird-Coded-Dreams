#ifndef __ModuleAsh_H__
#define __ModuleAsh_H__

#include "ModulePlayer.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleAsh : public ModulePlayer
{
public:
	ModuleAsh();
	~ModuleAsh();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

};

#endif