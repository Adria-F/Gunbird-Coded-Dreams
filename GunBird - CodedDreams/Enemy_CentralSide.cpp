#include "Enemy_CentralSide.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

Enemy_CentralSide::Enemy_CentralSide(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_central_side.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	//Vault Open
	vault_open.PushBack({ 0, 0, 48, 102 });

	vault_open.speed = 0.02f;
	vault_open.loop = false;


	//Boss Moving
	moving.PushBack({ 0, 103, 48, 102 });
	moving.PushBack({ 49, 103, 48, 102 });
	moving.PushBack({ 98, 103, 48, 102 });
	moving.PushBack({ 147, 103, 48, 102 });

	moving.PushBack({ 0, 206, 48, 102 });
	moving.PushBack({ 49, 206, 48, 102 });
	moving.PushBack({ 98, 206, 48, 102 });
	moving.PushBack({ 147, 206, 48, 102 });

	moving.speed = 0.02f;
	moving.loop = true;

	//Vault Closing
	vault_closing.PushBack({ 0, 0, 48, 102 });
	vault_closing.PushBack({ 49, 0, 48, 102 });
	vault_closing.PushBack({ 98, 0, 48, 102 });
	vault_closing.PushBack({ 147, 0, 48, 102 });

	vault_closing.speed = 0.2f;
	vault_closing.loop = false;

	//Death
	death.PushBack({ 0, 0, 0, 0, });
	death.speed = 0.02f;
	death.loop = false;

	//Set path
	path.PushBack({ 0.0f, 0.09f }, 640, &vault_open);
	path.PushBack({ 0.0f, 0.09f }, 30, &vault_closing);
	path.PushBack({ 0.0f, -0.9f }, 300, &moving);
	path.PushBack({ 0.0f, -0.3f }, 5000, &moving);

	//Set lives, initial_hp, points adn extra_anim
	lives = 50;
	initial_hp = lives;
	extra_anim = false;
	lower_level = true;
	explosion_type = MID1;
	Shot_Total_time = (Uint32)(400.0f);
	Shot_Total_time1 = (Uint32)(7000.0f);

	//collider
	collider = NULL;
}

Enemy_CentralSide::~Enemy_CentralSide()
{
	App->textures->Unload(NormalSprite);
}


void Enemy_CentralSide::Move()
{
	if (App->render->camera.y <= -1300 && lives > 0) //-1839
	{
		position = original_pos + path.GetCurrentPosition(&animation);
	}
	else
	{
		lives = 0;
	}

	if (moving.GetCurrentFrameNum() == 2 && collider_state == 0)
	{
		collider = App->collision->AddCollider({ (int)position.x, (int)position.y, 48, 80 }, COLLIDER_ENEMY, (Module*)App->enemies);
		collider_state = 1;
	}
	if (App->render->camera.y >= -2146) //-2146
	{
		Shot_now = SDL_GetTicks() - Shot_Start_time;
		
		if (state == 7)
		{
			state = 0;
		}
		if (Shot_now > Shot_Total_time1 && state == 6)
		{
			Shot_Start_time = SDL_GetTicks();
			state = 7;
		}
		if (Shot_now > Shot_Total_time && state == 5)
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 7, position.y + App->render->camera.y + 95, COLLIDER_ENEMY_SHOT, 0, 0, PLAYER);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 36, position.y + App->render->camera.y + 95, COLLIDER_ENEMY_SHOT, 0, 0, PLAYER);
			state = 6;
		}
		if (Shot_now > Shot_Total_time && state == 4)
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 22, position.y + App->render->camera.y + 62, COLLIDER_ENEMY_SHOT, 0, 247, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 22, position.y + App->render->camera.y + 62, COLLIDER_ENEMY_SHOT, 0, 292, ANGLE);
			state = 5;
		}
		if (Shot_now > Shot_Total_time && state == 3)
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 22, position.y + App->render->camera.y + 62, COLLIDER_ENEMY_SHOT, 0, 225, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 22, position.y + App->render->camera.y + 62, COLLIDER_ENEMY_SHOT, 0, 315, ANGLE);
			state = 4;
		}
		if (Shot_now > Shot_Total_time && state == 2)
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 22, position.y + App->render->camera.y + 62, COLLIDER_ENEMY_SHOT, 0, 202, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 22, position.y + App->render->camera.y + 62, COLLIDER_ENEMY_SHOT, 0, 337, ANGLE);
			state = 3;
		}
		if (Shot_now > Shot_Total_time && state == 1)
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 22, position.y + App->render->camera.y + 62, COLLIDER_ENEMY_SHOT, 0, 180, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 22, position.y + App->render->camera.y + 62, COLLIDER_ENEMY_SHOT, 0, 360, ANGLE);
			state = 2;
		}
		if (Shot_now > Shot_Total_time && state == 0)
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 22, position.y + App->render->camera.y + 62, COLLIDER_ENEMY_SHOT, 0, 157, ANGLE);
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 22, position.y + App->render->camera.y + 62, COLLIDER_ENEMY_SHOT, 0, 22, ANGLE);
			state = 1;
		}
	}
	
	
}

void Enemy_CentralSide::DeadAnim()
{
	animation = &death;
}
