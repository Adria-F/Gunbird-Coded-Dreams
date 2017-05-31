#ifndef __MODULE_CHARACTER_H__
#define __MODULE_CHARACTER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "Application.h"
#include "ModuleRender.h"

#define CHARACTER_SPEED 3

struct SDL_Texture;
struct Collider;
enum particle_type;
struct Particle;

class ModuleCharacter : public Module
{
public:

	virtual bool Start() = 0;
	virtual bool CleanUp() = 0;

public:

	SDL_Texture* texture_graphics = nullptr;
	SDL_Texture* texture_onhit = nullptr;

	Animation* current_animation = nullptr;

	Animation idle;
	Animation left;
	Animation right;
	Animation onhit;
	Animation death;
	Animation highscore_anim;

	char* shot_path;
	char* shot_path2;
	particle_type shot_lvl1;
	particle_type shot_lvl2;
	particle_type shot_lvl3;
	particle_type shot_lvl3_right;
	particle_type shot_lvl3_left;
	particle_type shot_lvl4;
	particle_type shot_lvl4_right;
	particle_type shot_lvl4_left;
	Particle* shot_particle_lvl1;
	Particle* shot_particle_lvl2;
	Particle* shot_particle_lvl3;
	Particle* shot_particle_lvl3_left;
	Particle* shot_particle_lvl3_right;
	Particle* shot_particle_lvl4;
	Particle* shot_particle_lvl4_left;
	Particle* shot_particle_lvl4_right;
};

#endif // !__MODULE_CHARACTER_H__