#include "Enemy_LeftSide.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "p2Point.h"
#include "Enemy_CentralSide.h"

Enemy_LeftSide::Enemy_LeftSide(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_left_side.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	moving.PushBack({ 0, 0, 58, 89 });
	moving.PushBack({ 72, 0, 58, 89 });
	moving.speed = 0.2f;
	moving.loop = true;

	//Set path
	path.PushBack({ 0.0f, 0.09f }, 670, &moving); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
	path.PushBack({ 0.0f, -0.9f }, 300, &moving);
	path.PushBack({ 0.0f, -0.3f }, 1000, &moving);

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = false;
	Shot_Total_time = (Uint32)(5000.0f);
	Shot_Total_time1 = (Uint32)(500.0f);
	Shot_Total_time3 = (Uint32)(2000.0f);
	Shot_Total_time2 = (Uint32)(4000.0f);

	collider = App->collision->AddCollider({ x, y, 0, 0 }, COLLIDER_NONE, (Module*)App->enemies);
}

Enemy_LeftSide::~Enemy_LeftSide()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_LeftSide::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	Shot_now = SDL_GetTicks() - Shot_Start_time;
	if (Shot_now > Shot_Total_time && state == 0 || state >= 1) //Initial time
	{
		Shot_now = SDL_GetTicks() - Shot_Start_time;
		if (Shot_now > Shot_Total_time1 && state < 2) //Two consecutives shoots
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 31, position.y + App->render->camera.y + 60, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
			App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 106, position.y + App->render->camera.y + 60, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
			state++;
		}
		if (Shot_now > Shot_Total_time2 && state == 3) //Second Shoot
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 31, position.y + App->render->camera.y + 60, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
			state = 2;
		}
		else if (Shot_now > Shot_Total_time3 && state == 2) //First Shoot
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 31, position.y + App->render->camera.y + 60, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
			state = 3;
		}
	}
	lower_level = true;
}