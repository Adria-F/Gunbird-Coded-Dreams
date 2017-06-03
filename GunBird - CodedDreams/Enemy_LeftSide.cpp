#include "Enemy_LeftSide.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "p2Point.h"
#include "Enemy_CentralSide.h"
#include "ModulePowerUp.h"

Enemy_LeftSide::Enemy_LeftSide(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_left_side.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	moving.PushBack({ 0, 0, 74, 89 });
	moving.PushBack({ 76, 0, 74, 89 });
	moving.speed = 0.2f;
	moving.loop = true;

	//notmoving
	notmoving.PushBack({ 0, 0, 74, 89 });
	notmoving.PushBack({ 76, 0, 74, 89 });
	notmoving.speed = 0.2f;
	notmoving.loop = false;

	//Death animation
	dead.PushBack({ 0, 89, 74, 89 });
	dead.PushBack({ 76, 89, 74, 89 });
	dead.PushBack({ 152, 89, 74, 89 });
	dead.PushBack({ 228, 89, 74, 89 });
	dead.PushBack({ 304, 89, 74, 89 });
	dead.PushBack({ 0, 178, 74, 89 });
	dead.PushBack({ 76, 178, 74, 89 });
	dead.PushBack({ 152, 178, 74, 89 });
	dead.speed = 0.1f;
	dead.loop = true;

	//Set path
	path.PushBack({ 0.0f, 0.09f }, 670, &notmoving); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
	path.PushBack({ 0.0f, -0.9f }, 300, &moving);
	path.PushBack({ 0.0f, -0.3f }, 5000, &moving);

	//Set lives, initial_hp, points adn extra_anim
	lives = 50; //120
	initial_hp = lives;
	extra_anim = false;
	lower_level = true;
	explosion_type = BIG2;
	Shot_Total_time = (Uint32)(5000.0f);
	Shot_Total_time1 = (Uint32)(500.0f);
	Shot_Total_time3 = (Uint32)(2000.0f);
	Shot_Total_time2 = (Uint32)(4000.0f);

	
}

Enemy_LeftSide::~Enemy_LeftSide()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_LeftSide::Move()
{
	if (App->render->camera.y <= -1300) //-1839
	{
		position = original_pos + path.GetCurrentPosition(&animation);
	}
	else
	{
		lives = 0;
	}

	if (moving.GetCurrentFrameNum() == 2 && collider_state == 0)
	{
		collider = App->collision->AddCollider({ (int)position.x, (int)position.y, 64, 89 }, COLLIDER_ENEMY, (Module*)App->enemies);
		collider_state = 1;
	}

	if (App->render->camera.y >= -2146) //-2146
	{
		Shot_now = SDL_GetTicks() - Shot_Start_time;
		if (Shot_now > Shot_Total_time && state == 0 || Shot_now > Shot_Total_time && state == 4 || state >= 1) //Initial time 5000.0f
		{
			Shot_now = SDL_GetTicks() - Shot_Start_time;
			if (Shot_now > Shot_Total_time1 && state < 2) //Two consecutives shoots 500.0f + 500.0f 0->1 1->2
			{
				Shot_Start_time = SDL_GetTicks();
				App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 31, position.y + App->render->camera.y + 60, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
				App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 106, position.y + App->render->camera.y + 60, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
				state++;
			}
			if (Shot_now > Shot_Total_time2 && state == 3) //Second Shoot 2000.0f 3->4
			{
				Shot_Start_time = SDL_GetTicks();
				App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 31, position.y + App->render->camera.y + 60, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
				App->particles->AddParticle(App->particles->mid_shot_particle, particle_type::P_MID_SHOT, position.x + 33, position.y + App->render->camera.y + 30, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
				App->particles->AddParticle(App->particles->mid_shot_particle, particle_type::P_MID_SHOT, position.x + 33, position.y + App->render->camera.y + 30, COLLIDER_ENEMY_SHOT, 0, 280, ANGLE);
				state = 4;
			}
			if (Shot_now > Shot_Total_time3 && state == 2) //First Shoot 4000.0f state 2->3
			{
				Shot_Start_time = SDL_GetTicks();
				App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 31, position.y + App->render->camera.y + 60, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
				App->particles->AddParticle(App->particles->mid_shot_particle, particle_type::P_MID_SHOT, position.x + 33, position.y + App->render->camera.y + 30, COLLIDER_ENEMY_SHOT, 0, 270, ANGLE);
				App->particles->AddParticle(App->particles->mid_shot_particle, particle_type::P_MID_SHOT, position.x + 33, position.y + App->render->camera.y + 30, COLLIDER_ENEMY_SHOT, 0, 280, ANGLE);
				state = 3;
			}
			if (state == 4) //4->2
			{
				state = 2;
				Shot_now = SDL_GetTicks() - Shot_Start_time;
			}
		}
	}
}

void Enemy_LeftSide::DeadAnim()
{
	animation = &dead;
	if (App->render->camera.y <= -1300) //-1839
	{
		position.y += -0.3f; //Perque es mogui a la mateixa velocitat que l'overlay
	}
}

void Enemy_LeftSide::Drop()
{
	App->powerup->AddPowerUp(UPGRADE, App->render->camera.x + position.x + 37, App->render->camera.y + position.y + 44);
}