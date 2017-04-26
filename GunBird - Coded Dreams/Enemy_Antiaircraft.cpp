#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Antiaircraft.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleMarion.h"
#include "ModuleAsh.h"
#include <math.h>
#include "SDL/include/SDL_timer.h"


Enemy_Antiaircraft::Enemy_Antiaircraft(int x, int y): Enemy(x, y)
{
	NormalSprite = App->textures->Load("assets/enemies/General_Torpedo _ Castle mortar.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_General_Torpedo _ Castle mortar.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_General_Torpedo _ Castle mortar.png");

	extra_anim = true;
	//animation
	anim.PushBack({ 0, 0, 32, 32 });
	anim.PushBack({ 34, 0, 32, 32 });
	anim.PushBack({ 68, 0, 32, 32 });
	anim.PushBack({ 102, 0, 32, 32 });
	anim.speed = 0.1f;

	//open animation
	open_anim.PushBack({ 137, 0, 32, 32 });
	open_anim.loop = false;
	open_anim.speed = 0.06f;

	open2_anim.PushBack({ 174, 0, 32, 32 });
	open2_anim.PushBack({ 211, 0, 32, 32 });
	open2_anim.PushBack({ 212, 36, 32, 32 });
	open2_anim.loop = false;
	open2_anim.speed = 0.06f;

	path.PushBack({ 0.0f, 0.0f }, 1, &open_anim);
	path.PushBack({ 0.0f, 0.0f }, 30, &open2_anim);
	path.PushBack({ 0.0f, 0.0f }, 5000, &anim);

	original_pos.x = x;
	original_pos.y = y;


	lives = 24;
	initial_hp = 24;
	points = 600;

	collider = App->collision->AddCollider({162, 1596, 32, 32 }, COLLIDER_ENEMY, (Module*)App->enemies);
}

Enemy_Antiaircraft::~Enemy_Antiaircraft()
{
	if (NormalSprite != nullptr)
	{
		App->textures->Unload(NormalSprite);
		NormalSprite = nullptr;
	}

	if (RedSprite != nullptr)
	{
		App->textures->Unload(RedSprite);
		RedSprite = nullptr;
	}

	if (WhiteSprite != nullptr)
	{
		App->textures->Unload(WhiteSprite);
		WhiteSprite = nullptr;
	}
}

void Enemy_Antiaircraft::Move()
{
	vector.x = (App->marion->position.x - (App->render->camera.x + position.x));
	vector.y = (App->marion->position.y - (App->render->camera.y + position.y));
	distance[0] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
	vector.x = (App->ash->position.x - (App->render->camera.x + position.x));
	vector.y = (App->ash->position.y - (App->render->camera.y + position.y));
	distance[1] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
	if (distance[0] < distance[1])
		player = App->marion;
	else
		player = App->ash;
	
	if (App->render->camera.y >= -1590)
	{
		if (reload == false)
		{

			now = SDL_GetTicks() - start_time;
			if (now > total_time  && shot_sequ == 0 && player->position.y - 64 > this->collider->rect.y)
			{
				start_time = SDL_GetTicks();
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 45);
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 135);
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 225);
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 315);
				++shot_sequ;
			}
			else if (now > total_time  && shot_sequ == 1 && player->position.y - 64 > this->collider->rect.y)
			{
				start_time = SDL_GetTicks();
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 45 - 30);
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 135 - 30);
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 225 - 30);
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 315 - 30);

				++shot_sequ;
			}

			else if (now > total_time && shot_sequ == 2 && player->position.y - 64 > this->collider->rect.y)
			{
				start_time = SDL_GetTicks();
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 45 - 60);
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 135 - 60);
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 225 - 60);
				App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 315 - 60);
				shot_sequ = 0;
				reload = true;
				reload_start_time = SDL_GetTicks();	
			}
		}
		reload_now = SDL_GetTicks() - reload_start_time;

		if (reload && reload_now > reload_total_time)
		{
			reload = false;
		}
	}
	
	if (App->render->camera.y >= -1600)
	{
		position = original_pos + path.GetCurrentPosition(&animation);
	}
	else if (state == false)
	{
		state = true;
		position = original_pos + path.GetCurrentPosition(&animation);
	}
}

void Enemy_Antiaircraft::ExtraAnim(SDL_Texture* texture)
{
	App->render->Blit(texture, App->render->camera.x + position.x, App->render->camera.y + position.y, &(animation->GetCurrentFrame()));
}
