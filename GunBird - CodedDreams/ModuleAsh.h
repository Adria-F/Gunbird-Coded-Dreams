#ifndef __ModuleAsh_H__
#define __ModuleAsh_H__

#include "ModuleCharacter.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleAsh : public ModuleCharacter
{
public:
	ModuleAsh();
	~ModuleAsh();

	bool Start();
	bool CleanUp();
};

#endif