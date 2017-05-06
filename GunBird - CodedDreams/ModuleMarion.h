#ifndef __ModuleMarion_H__
#define __ModuleMarion_H__

#include "ModuleCharacter.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleMarion : public ModuleCharacter
{
public:
	ModuleMarion();
	~ModuleMarion();

	bool Start();
	bool CleanUp();

public:
	Animation stele1;
	Animation stele2;
	Animation stele3;

};

#endif