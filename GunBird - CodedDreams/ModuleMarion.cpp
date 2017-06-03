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

	//highscores animation
	highscore_anim.PushBack({ 5, 64, 21, 32 });//x - y - w - h
	highscore_anim.PushBack({ 37, 64, 21, 32 });
	highscore_anim.PushBack({ 68, 64, 21, 32 });
	highscore_anim.PushBack({ 101, 64, 21, 32 });
	highscore_anim.PushBack({ 5, 129, 23, 32 });//x - y - w - h
	highscore_anim.PushBack({ 37, 129, 23, 32 });
	highscore_anim.PushBack({ 68, 129, 23, 32 });
	highscore_anim.PushBack({ 101, 129, 23, 32 });
	highscore_anim.PushBack({ 5, 97, 23, 32 });
	highscore_anim.PushBack({ 37, 97, 23, 32 });
	highscore_anim.PushBack({ 68, 97, 23, 32 });
	highscore_anim.PushBack({ 101, 97, 23, 32 });
	highscore_anim.PushBack({ 5, 129, 23, 32 });//x - y - w - h
	highscore_anim.PushBack({ 37, 129, 23, 32 });
	highscore_anim.PushBack({ 68, 129, 23, 32 });
	highscore_anim.PushBack({ 101, 129, 23, 32 });
	highscore_anim.PushBack({ 5, 64, 21, 32 });//x - y - w - h
	highscore_anim.PushBack({ 37, 64, 21, 32 });
	highscore_anim.PushBack({ 68, 64, 21, 32 });
	highscore_anim.PushBack({ 101, 64, 21, 32 });
	highscore_anim.PushBack({ 3, 33, 23, 32 });//x - y - w - h
	highscore_anim.PushBack({ 35, 33, 23, 32 });
	highscore_anim.PushBack({ 66, 33, 23, 32 });
	highscore_anim.PushBack({ 99, 33, 23, 32 });
	highscore_anim.PushBack({ 3, 0, 23, 32 });
	highscore_anim.PushBack({ 35, 0, 23, 32 });
	highscore_anim.PushBack({ 66, 0, 23, 32 });
	highscore_anim.PushBack({ 99, 0, 23, 32 });
	highscore_anim.PushBack({ 3, 33, 23, 32 });//x - y - w - h
	highscore_anim.PushBack({ 35, 33, 23, 32 });
	highscore_anim.PushBack({ 66, 33, 23, 32 });
	highscore_anim.PushBack({ 99, 33, 23, 32 });
	highscore_anim.speed = 0.1f;

	//Bomb animations
	{
		bomb_north.anim.PushBack({ 10, 466, 45, 46 });
		bomb_north.anim.PushBack({ 57, 466, 45, 46 });
		bomb_north.anim.PushBack({ 106, 466, 45, 46 });
		bomb_north.anim.speed = 0.2f;
		bomb_north.anim.loop = false;
		bomb_north.speed.y = -3;

		bomb_south.anim.PushBack({ 156, 466, 45, 46 });
		bomb_south.anim.PushBack({ 203, 466, 45, 46 });
		bomb_south.anim.PushBack({ 252, 466, 45, 46 });
		bomb_south.anim.speed = 0.2f;
		bomb_south.anim.loop = false;
		bomb_south.speed.y = 3;

		bomb_east.anim.PushBack({ 177, 381, 42, 46 });
		bomb_east.anim.PushBack({ 235, 381, 42, 46 });
		bomb_east.anim.PushBack({ 290, 381, 42, 46 });
		bomb_east.anim.speed = 0.2f;
		bomb_east.anim.loop = false;
		bomb_east.speed.x = -3;

		bomb_west.anim.PushBack({ 15, 381, 42, 46 });
		bomb_west.anim.PushBack({ 73, 381, 42, 46 });
		bomb_west.anim.PushBack({ 128, 381, 42, 46 });
		bomb_west.anim.speed = 0.2f;
		bomb_west.anim.loop = false;
		bomb_west.speed.x = 3;
	}

	//diagonals
	{
		//NORTH EAST
		bomb_north_east.anim.PushBack({ 19, 549, 45, 45 });
		bomb_north_east.anim.PushBack({ 70, 549, 45, 45 });
		bomb_north_east.anim.PushBack({ 121, 549, 45, 45 });

		bomb_north_east.anim.PushBack({ 26, 663, 45, 45 });
		bomb_north_east.anim.PushBack({ 77, 663, 45, 45 });
		bomb_north_east.anim.PushBack({ 128, 663, 45, 45 });
		bomb_north_east.anim.PushBack({ 178, 663, 45, 45 });
		bomb_north_east.anim.PushBack({ 229, 663, 45, 45 });
		bomb_north_east.anim.PushBack({ 280, 663, 45, 45 });
		bomb_north_east.anim.PushBack({ 330, 663, 45, 45 });
		bomb_north_east.anim.PushBack({ 380, 663, 45, 45 });
		bomb_north_east.anim.PushBack({ 430, 663, 45, 45 });
		bomb_north_east.anim.PushBack({ 480, 663, 45, 45 });
		bomb_north_east.anim.PushBack({ 530, 663, 45, 45 });
		bomb_north_east.anim.PushBack({ 580, 663, 45, 45 });

		bomb_north_east.anim.PushBack({ 26, 663, 45, 45 });
		bomb_north_east.anim.speed = 0.3f;
		bomb_north_east.anim.loop = false;
		bomb_north_east.speed.x = 2.12f;
		bomb_north_east.speed.y = -2.12f;

		//SOUTH EAST
		bomb_south_east.anim.PushBack({ 178, 549, 45, 45 });
		bomb_south_east.anim.PushBack({ 229, 549, 45, 45 });
		bomb_south_east.anim.PushBack({ 280, 549, 45, 45 });

		bomb_south_east.anim.PushBack({ 229, 663, 45, 45 });
		bomb_south_east.anim.PushBack({ 280, 663, 45, 45 });
		bomb_south_east.anim.PushBack({ 330, 663, 45, 45 });
		bomb_south_east.anim.PushBack({ 380, 663, 45, 45 });
		bomb_south_east.anim.PushBack({ 430, 663, 45, 45 });
		bomb_south_east.anim.PushBack({ 480, 663, 45, 45 });
		bomb_south_east.anim.PushBack({ 530, 663, 45, 45 });
		bomb_south_east.anim.PushBack({ 580, 663, 45, 45 });
		bomb_south_east.anim.PushBack({ 26, 663, 45, 45 });
		bomb_south_east.anim.PushBack({ 77, 663, 45, 45 });
		bomb_south_east.anim.PushBack({ 128, 663, 45, 45 });
		bomb_south_east.anim.PushBack({ 178, 663, 45, 45 });

		bomb_south_east.anim.PushBack({ 229, 663, 45, 45 });
		bomb_south_east.anim.speed = 0.3f;
		bomb_south_east.anim.loop = false;
		bomb_south_east.speed.x = 2.12f;
		bomb_south_east.speed.y = 2.12f;

		//SOUTH WEST
		bomb_south_west.anim.PushBack({ 337, 549, 45, 45 });
		bomb_south_west.anim.PushBack({ 388, 549, 45, 45 });
		bomb_south_west.anim.PushBack({ 439, 549, 45, 45 });

		bomb_south_west.anim.PushBack({ 330, 663, 45, 45 });
		bomb_south_west.anim.PushBack({ 380, 663, 45, 45 });
		bomb_south_west.anim.PushBack({ 430, 663, 45, 45 });
		bomb_south_west.anim.PushBack({ 480, 663, 45, 45 });
		bomb_south_west.anim.PushBack({ 530, 663, 45, 45 });
		bomb_south_west.anim.PushBack({ 580, 663, 45, 45 });
		bomb_south_west.anim.PushBack({ 26, 663, 45, 45 });
		bomb_south_west.anim.PushBack({ 77, 663, 45, 45 });
		bomb_south_west.anim.PushBack({ 128, 663, 45, 45 });
		bomb_south_west.anim.PushBack({ 178, 663, 45, 45 });
		bomb_south_west.anim.PushBack({ 229, 663, 45, 45 });
		bomb_south_west.anim.PushBack({ 280, 663, 45, 45 });

		bomb_south_west.anim.PushBack({ 330, 663, 45, 45 });
		bomb_south_west.anim.speed = 0.3f;
		bomb_south_west.anim.loop = false;
		bomb_south_west.speed.x = -2.12f;
		bomb_south_west.speed.y = 2.12f;

		//NORTH WEST
		bomb_north_west.anim.PushBack({ 496, 549, 45, 45});
		bomb_north_west.anim.PushBack({ 547, 549, 45, 45 });
		bomb_north_west.anim.PushBack({ 598, 549, 45, 45 });

		bomb_north_west.anim.PushBack({ 530, 663, 45, 45 });
		bomb_north_west.anim.PushBack({ 580, 663, 45, 45 });
		bomb_north_west.anim.PushBack({ 26, 663, 45, 45 });
		bomb_north_west.anim.PushBack({ 77, 663, 45, 45 });
		bomb_north_west.anim.PushBack({ 128, 663, 45, 45 });
		bomb_north_west.anim.PushBack({ 178, 663, 45, 45 });
		bomb_north_west.anim.PushBack({ 229, 663, 45, 45 });
		bomb_north_west.anim.PushBack({ 280, 663, 45, 45 });
		bomb_north_west.anim.PushBack({ 330, 663, 45, 45 });
		bomb_north_west.anim.PushBack({ 380, 663, 45, 45 });
		bomb_north_west.anim.PushBack({ 430, 663, 45, 45 });
		bomb_north_west.anim.PushBack({ 480, 663, 45, 45 });

		bomb_north_west.anim.PushBack({ 530, 663, 45, 45 });
		bomb_north_west.anim.speed = 0.3f;
		bomb_north_west.anim.loop = false;
		bomb_north_west.speed.x = -2.12f;
		bomb_north_west.speed.y = -2.12f;
	}
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
	shot_path2 = "assets/effects/gunbird_212 [EFFECT] MARION (Shoots Level 3 & 4).wav";
	upgrade_path = "assets/effects/upgrade_marion.wav";
	full_upgrade_path = "assets/effects/marion_full_upgrade.wav";
	bomb_path = "assets/effects/marion_bomb.wav";
	shot_lvl1 = particle_type::P_MARION_BULLET_P1;
	shot_lvl2 = particle_type::P_MARION_BULLET_P2;
	shot_lvl3_left = particle_type::P_MARION_BULLET_P3_LEFT;
	shot_lvl3_right = particle_type::P_MARION_BULLET_P3_RIGHT;
	shot_lvl4_left = particle_type::P_MARION_BULLET_P4_LEFT;
	shot_lvl4_right = particle_type::P_MARION_BULLET_P4_RIGHT;
	bomb = particle_type::P_MARION_BOMB;
	shot_particle_lvl1 = &App->particles->MARION_bullet_p1_particle;
	shot_particle_lvl2 = &App->particles->MARION_bullet_p2_particle;
	shot_particle_lvl3_left = &App->particles->MARION_bullet_p3_left_particle;
	shot_particle_lvl4 = &App->particles->MARION_bullet_p4_left_particle;
	
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