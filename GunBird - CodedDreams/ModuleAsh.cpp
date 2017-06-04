#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleCharacter.h"
#include "ModuleAsh.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleAsh::ModuleAsh()
{

	// idle animation
	idle.PushBack({ 14, 13, 19, 32 });//x - y - w - h
	idle.PushBack({ 43, 13, 19, 32 });
	idle.speed = 0.3f;

	//right animation
	right.PushBack({ 15, 97, 14, 32 });//x - y - w - h
	right.PushBack({ 39, 97, 14, 32 });
	right.speed = 0.3f;

	//left animation
	left.PushBack({ 70, 55, 14, 32 });
	left.PushBack({ 94, 55, 14, 32 });
	left.speed = 0.3f;
	
	//highscores animation
	highscore_anim.PushBack({ 14, 13, 19, 32 });//x - y - w - h
	highscore_anim.PushBack({ 43, 13, 19, 32 });
	highscore_anim.PushBack({ 70, 55, 14, 32 });
	highscore_anim.PushBack({ 94, 55, 14, 32 });
	highscore_anim.PushBack({ 14, 13, 19, 32 });//x - y - w - h
	highscore_anim.PushBack({ 43, 13, 19, 32 });
	highscore_anim.PushBack({ 15, 97, 14, 32 });//x - y - w - h
	highscore_anim.PushBack({ 39, 97, 14, 32 });
	highscore_anim.speed = 0.1f;

	/*//onhit flying enemies (Torpedo)
	onhit.PushBack({ 52, 43, 31, 31 });
	onhit.PushBack({ 90, 44, 31, 31 });
	onhit.PushBack({ 131, 47, 31, 31 });
	onhit.PushBack({ 168, 46, 31, 31 });
	onhit.PushBack({ 206, 46, 31, 31 });
	onhit.PushBack({ 16, 84, 31, 31 });
	onhit.PushBack({ 54, 84, 31, 31 });
	onhit.PushBack({ 92, 84, 31, 31 });
	onhit.PushBack({ 130, 84, 31, 31 });

	onhit.PushBack({ 15, 2, 31, 31 });
	onhit.PushBack({ 50, 4, 31, 31 });
	onhit.PushBack({ 89, 4, 31, 31 });
	onhit.PushBack({ 125, 6, 31, 31 });
	onhit.PushBack({ 166, 7, 31, 31 });
	onhit.PushBack({ 203, 8, 31, 31 });
	onhit.PushBack({ 16, 41, 31, 31 });
	onhit.speed = 0.25f;*/

	//Bomb animations
	{
		//bomb
		dropping_bomb.anim.PushBack({ 0, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 0, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 0, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 0, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 222, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 222, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 222, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 222, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 444, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 444, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 444, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 444, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 666, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 666, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 666, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 666, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 888, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 888, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 888, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 888, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 1110, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 1110, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 1110, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 1110, 0, 222, 222 });
		dropping_bomb.anim.PushBack({ 0, 0, 0, 0 });
		//dropping_bomb.anim.PushBack({ 1332, 0, 222, 222 });
		dropping_bomb.anim.speed = 0.9f;
		dropping_bomb.anim.loop = false;
		dropping_bomb.life = 1000;

		//start
		bomb_north.anim.PushBack({ 0, 0, 222, 222 });
		bomb_north.anim.PushBack({ 0, 222, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 222, 222, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 444, 222, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 666, 222, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 888, 222, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1110, 222, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1332, 222, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });

		//bucle (3)
		bomb_north.anim.PushBack({ 0, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 222, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 444, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 666, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 888, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1110, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1332, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });

		bomb_north.anim.PushBack({ 0, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 222, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 444, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 666, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 888, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1110, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1332, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		//
		bomb_north.anim.PushBack({ 0, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 222, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 444, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 666, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 888, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1110, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1332, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });

		bomb_north.anim.PushBack({ 0, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 222, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 444, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 666, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 888, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1110, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1332, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		//
		bomb_north.anim.PushBack({ 0, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 222, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 444, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 666, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 888, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1110, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1332, 444, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });

		bomb_north.anim.PushBack({ 0, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 222, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 444, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 666, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 888, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1110, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1332, 666, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });

		//end
		bomb_north.anim.PushBack({ 0, 888, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 222, 888, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 444, 888, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 666, 888, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 888, 888, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1110, 888, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1332, 888, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });

		bomb_north.anim.PushBack({ 0, 1110, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 222, 1110, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 444, 1110, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 666, 1110, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 888, 1110, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1110, 1110, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.PushBack({ 1332, 1110, 222, 222 });
		bomb_north.anim.PushBack({ 0, 0, 0, 0 });
		bomb_north.anim.speed = 0.9f;
		bomb_north.anim.loop = false;
		bomb_north.life = 2750;
	}
}

ModuleAsh::~ModuleAsh()
{}

// Load assets
bool ModuleAsh::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	texture_graphics = App->textures->Load("assets/characters/ash.png"); // arcade version
	texture_onhit = App->textures->Load("assets/characters/Collision sprites.png");
	shot_path = "assets/effects/gunbird_209 [EFFECT] ASH (Shoots Level 1 & 2).wav";
	shot_path2 = "assets/effects/gunbird_210 [EFFECT] ASH (Shoots Level 3 & 4).wav";
	upgrade_path = "assets/effects/upgrade_ash.wav";
	full_upgrade_path = "assets/effects/ash_full_upgrade.wav";
	bomb_path = "assets/effects/ash_bomb.wav";
	shot_lvl1 = particle_type::P_ASH_BULLET_P1;
	shot_lvl2 = particle_type::P_ASH_BULLET_P2;
	shot_lvl3 = particle_type::P_ASH_BULLET_P3;
	shot_lvl3_donut_p3 = particle_type::P_ASH_BULLET_P3_DONUT;
	bomb = particle_type::P_ASH_BOMB;
	shot_particle_lvl1 = &App->particles->ASH_bullet_p1_particle;
	shot_particle_lvl2 = &App->particles->ASH_bullet_p2_particle;
	shot_particle_lvl3 = &App->particles ->ASH_bullet_p3_particle;
	shot_particle_lvl3_donut= &App->particles->ASH_bullet_p3_donut_particle;

	return ret;
}

bool ModuleAsh::CleanUp()
{
	bool ret = true;
	
	App->textures->Unload(texture_graphics);
	texture_graphics = nullptr;
	App->textures->Unload(texture_onhit);
	texture_onhit = nullptr;

	return ret;
}