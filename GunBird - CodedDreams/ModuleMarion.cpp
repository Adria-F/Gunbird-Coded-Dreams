#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleCharacter.h"
#include "ModuleMarion.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleMarion::ModuleMarion()
{
	// idle animation (arcade sprite sheet)
	idle.PushBack({ 5, 64, 21, 32 });//x - y - w - h
	idle.PushBack({ 37, 64, 21, 32 });
	idle.PushBack({ 68, 64, 21, 32 });
	idle.PushBack({ 101, 64, 21, 32 });
	idle.speed = 0.1f;

	//right animation
	right.PushBack({ 5, 129, 23, 32 });//x - y - w - h
	right.PushBack({ 37, 129, 23, 32 });
	right.PushBack({ 68, 129, 23, 32 });
	right.PushBack({ 101, 129, 23, 32 });
	right.PushBack({ 5, 97, 23, 32 });
	right.PushBack({ 37, 97, 23, 32 });
	right.PushBack({ 68, 97, 23, 32 });
	right.PushBack({ 101, 97, 23, 32 });
	right.speed = 0.1f;

	//left animation
	left.PushBack({ 3, 33, 23, 32 });//x - y - w - h
	left.PushBack({ 35, 33, 23, 32 });
	left.PushBack({ 66, 33, 23, 32 });
	left.PushBack({ 99, 33, 23, 32 });
	left.PushBack({ 3, 0, 23, 32 });
	left.PushBack({ 35, 0, 23, 32 });
	left.PushBack({ 66, 0, 23, 32 });
	left.PushBack({ 99, 0, 23, 32 });
	left.speed = 0.1f;
}

ModuleMarion::~ModuleMarion()
{}

// Load assets
bool ModuleMarion::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	texture_graphics = App->textures->Load("assets/characters/marion.png"); // arcade version
	texture_onhit = App->textures->Load("assets/characters/Collision sprites.png"); 
	shot_path = "assets/effects/gunbird_211 [EFFECT] MARION (Shoots Level 1 & 2).wav";
	shot_lvl1 = particle_type::P_MARION_BULLET_P1;
	shot_lvl2 = particle_type::P_MARION_BULLET_P2;
	shot_particle_lvl1 = &App->particles->MARION_bullet_p1_particle;
	shot_particle_lvl2 = &App->particles->MARION_bullet_p2_particle;
	
	return ret;
}

bool ModuleMarion::CleanUp()
{
	bool ret = true;

	App->textures->Unload(texture_graphics);
	texture_graphics = nullptr;
	App->textures->Unload(texture_onhit);
	texture_onhit = nullptr;

	return ret;
}
	