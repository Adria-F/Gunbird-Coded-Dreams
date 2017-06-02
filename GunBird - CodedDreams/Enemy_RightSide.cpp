#include "Enemy_RightSide.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

Enemy_RightSide::Enemy_RightSide(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_right_side.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	moving.PushBack({ 304, 0, 74, 89 });
	moving.PushBack({ 228, 0, 74, 89 });
	moving.speed = 0.2f;
	moving.loop = true;

	//Death animation
	dead.PushBack({ 0, 89, 74, 89 });
	dead.PushBack({ 76, 89, 74, 89 });
	dead.PushBack({ 152, 89, 74, 89 });
	dead.PushBack({ 228, 89, 74, 89 });
	dead.PushBack({ 304, 89, 74, 89 });
	dead.PushBack({ 152, 178, 74, 89 });
	dead.PushBack({ 228, 178, 74, 89 });
	dead.PushBack({ 304, 178, 74, 89 });
	dead.speed = 0.1f;
	dead.loop = true;

	//Set path
	path.PushBack({0.0f, 0.09f}, 670, &moving); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
	path.PushBack({ 0.0f, -0.9f }, 300, &moving);
	path.PushBack({ 0.0f, -0.3f }, 5000, &moving);

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = false;
	lower_level = true;
	Shot_Total_time = (Uint32)(12000.0f);
	Shot_Total_time1 = (Uint32)(1500.0f);
	Shot_Total_time2 = (Uint32)(3500.0f);

	collider = App->collision->AddCollider({ x, y, 0, 0 }, COLLIDER_NONE, (Module*)App->enemies);
}

Enemy_RightSide::~Enemy_RightSide()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_RightSide::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	if (App->render->camera.y >= -2077) //-2146
	{
		Shot_now = SDL_GetTicks() - Shot_Start_time;
		if (Shot_now > Shot_Total_time || state >= 1) //Initial time
		{
			Shot_now = SDL_GetTicks() - Shot_Start_time;
			if (Shot_now > Shot_Total_time1 && state == 2) //First Shoot
			{
				Shot_Start_time = SDL_GetTicks();
				App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 31, position.y + App->render->camera.y + 60, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
				state = 1;
			}
			else if (Shot_now > Shot_Total_time2 && state == 1) //Second Shoot
			{
				Shot_Start_time = SDL_GetTicks();
				App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 31, position.y + App->render->camera.y + 60, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
				state = 2;
			}
			else if (state == 3)
			{
				state = 1;
			}

			state = 1;
		}
	}
	
}

void Enemy_RightSide::DeadAnim()
{
	animation = &dead;
	position.y += 0.09f; //Perque es mogui a la mateixa velocitat que l'overlay
}