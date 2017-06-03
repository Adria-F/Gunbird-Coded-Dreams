#include "Enemy_General_Turret.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleSceneMine.h"
#include "ModuleEnemies.h"
#include "p2Point.h"
#include "ModulePowerUp.h"

#define PI 3.14159265

Enemy_General_Turret::Enemy_General_Turret(int x, int y, int wave, int id) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/General_Turret.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_General_Turret.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_General_Turret.png");

	//Set animation steps, speed and loop
	idle.PushBack({ 1, 235, 28, 35 });
	idle.PushBack({ 30, 235, 28, 35 });
	idle.PushBack({ 59, 235, 28, 35 });
	idle.PushBack({ 88, 235, 28, 35 });
	idle.PushBack({ 1, 271, 28, 35 });
	idle.PushBack({ 30, 271, 28, 35 });
	idle.PushBack({ 59, 271, 28, 35 });
	idle.PushBack({ 88, 271, 28, 35 });
	idle.PushBack({ 1, 307, 28, 35 });
	idle.PushBack({ 30, 307, 28, 35 });
	idle.PushBack({ 59, 307, 28, 35 });
	idle.PushBack({ 88, 307, 28, 35 });
	idle.speed = 0.4f;
	idle.loop = true;

	dead.PushBack({ 11, 156, 32, 33 });
	dead.PushBack({ 44, 156, 32, 33 });
	dead.PushBack({ 77, 156, 32, 33 });
	dead.PushBack({ 138, 156, 32, 33 });
	dead.PushBack({ 171, 156, 32, 33 });
	dead.PushBack({ 204, 156, 32, 33 });
	dead.PushBack({ 139, 190, 32, 33 });
	dead.PushBack({ 172, 190, 32, 33 });
	dead.speed = 0.1f;
	dead.loop = true;

	appear_anim.PushBack({ 133, 227, 16, 28 });
	appear_anim.PushBack({ 191, 227, 16, 28 });
	appear_anim.PushBack({ 258, 227, 16, 28 });
	appear_anim.PushBack({ 345, 227, 16, 28 });
	appear_anim.speed = 0.08f;
	appear_anim.loop = false;

	gate = {64, 100, 130, 98}; //104, 2448
	gate_pos.x = 104;
	gate_pos.y = 2589;

	//Set path
	path.PushBack({ 0.0f, 0.09f }, 100, &idle); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

	extra_anim = true;
	int i = 0;
	//All angles rect definition
	{
		angles[i++] = { 0, 0, 28, 29 };
		angles[i++] = { 29, 0, 28, 29 };
		angles[i++] = { 58, 0, 28, 29 };
		angles[i++] = { 87, 0, 28, 29 };
		angles[i++] = { 127, 0, 28, 29 };
		angles[i++] = { 156, 0, 28, 29 };
		angles[i++] = { 185, 0, 28, 29 };
		angles[i++] = { 214, 0, 28, 29 };
		angles[i++] = { 252, 0, 28, 29 };
		angles[i++] = { 281, 0, 28, 29 };
		angles[i++] = { 310, 0, 28, 29 };
		angles[i++] = { 339, 0, 28, 29 };
		angles[i++] = { 0, 52, 28, 29 };
		angles[i++] = { 29, 52, 28, 29 };
		angles[i++] = { 58, 52, 28, 29 };
		angles[i++] = { 87, 52, 28, 29 };
		angles[i++] = { 127, 52, 28, 29 };
		angles[i++] = { 156, 52, 28, 29 };
		angles[i++] = { 185, 52, 28, 29 };
		angles[i++] = { 214, 52, 28, 29 };
		angles[i++] = { 252, 52, 28, 29 };
		angles[i++] = { 281, 52, 28, 29 };
		angles[i++] = { 310, 52, 28, 29 };
		angles[i++] = { 339, 52, 28, 29 };
		angles[i++] = { 0, 104, 28, 29 };
		angles[i++] = { 29, 104, 28, 29 };
		angles[i++] = { 58, 104, 28, 29 };
		angles[i++] = { 87, 104, 28, 29 };
		angles[i++] = { 127, 104, 28, 29 };
		angles[i++] = { 156, 104, 28, 29 };
		angles[i++] = { 185, 104, 28, 29 };
		angles[i++] = { 214, 104, 28, 29 };
	}
	
	//Set lives, initial_hp, points and extra_anim
	lives = 2;
	initial_hp = lives;
	points = 400;
	explosion_type = MID1; //Explosion type
	Shot_Total_time = (Uint32)(5000.0f);
	this->wave = wave;
	this->id = id;

	//Add and save collider
	if (wave != 3)
		collider = App->collision->AddCollider({ x, y, 28, 35 }, COLLIDER_ENEMY, (Module*)App->enemies);
	collider_pos.y = -6;

	if (wave == 3)
	{
		if (id == 2)
		{
			App->enemies->AddEnemy(GENERAL_TURRET, 160, 2618, 3, 1);
			App->enemies->AddEnemy(GENERAL_TURRET, 194, 2618, 3, 1);
			App->enemies->AddEnemy(GENERAL_TURRET, 127, 2648, 3);
			App->enemies->AddEnemy(GENERAL_TURRET, 160, 2648, 3, 4);
			App->enemies->AddEnemy(GENERAL_TURRET, 194, 2648, 3, 3);
		}
		if (id == 3)
		{
			appear_Start_time = SDL_GetTicks();
		}
	}

	if (wave == 1)
	{
		if (id == 1)
		{
			path.PushBack({ 0.0f, 0.09f }, 50, &idle);
			path.PushBack({ -0.3f, 0.09f }, 1000, &idle);
		}
		else if (id == 2)
		{
			path.PushBack({ 0.0f, 0.09f }, 50, &idle);
			path.PushBack({ 0.3f, 0.09f }, 1000, &idle);
		}
	}
	else if (wave == 2)
	{
		path.PushBack({ 0.0f, 0.09f }, 50, &idle);
		path.PushBack({ -0.5f, 0.09f }, 244, &idle);
		path.PushBack({ 0.0f, 0.09f }, 1000, &idle);
	}

}

Enemy_General_Turret::~Enemy_General_Turret()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_General_Turret::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	if (App->scene_mine->turret_appeared == true && wave == 3 || wave != 3)
	{
		Shot_now = SDL_GetTicks() - Shot_Start_time;
		if (Shot_now > Shot_Total_time)
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 5, position.y + App->render->camera.y + 10, COLLIDER_ENEMY_SHOT, 0, 0);
		}
	}

}

void Enemy_General_Turret::ExtraAnim(SDL_Texture* texture)
{
	if (wave == 3 && App->scene_mine->turret_appeared == false)
	{
		if (id == 3)
		{
			appear_now = SDL_GetTicks() - appear_Start_time;
			if (appear_now > appear_Total_time)
			{
				if (appear_now > appear_Total_time + 1300)
				{
					App->scene_mine->turret_appearing = true;
				}
				appearing = true;
			}
			if (appearing)
			{
				gate_pos.x += 1.5f;
			}
			gate_pos.y += 0.09f;
			App->render->Blit(App->scene_mine->graphics_above_background_anims_text, App->render->camera.x + gate_pos.x, App->render->camera.y + gate_pos.y, &gate); // 2448 | 141
		}
	}
	if (wave == 3 && App->scene_mine->turret_appearing && App->scene_mine->turret_appeared == false)
	{
		App->render->Blit(texture, App->render->camera.x + position.x + 5, App->render->camera.y + position.y - 9, &appear_anim.GetCurrentFrame());
		if (appear_anim.Finished())
		{
			if (collider == nullptr)
				collider = App->collision->AddCollider({ (int)position.x, (int)position.y, 28, 35 }, COLLIDER_ENEMY, (Module*)App->enemies);
			if (id == 4)
				App->scene_mine->turret_appeared = true;
		}
	}
	if (wave == 3 && App->scene_mine->turret_appeared || wave != 3)
	{
		if (App->player1->IsEnabled() && App->player2->IsEnabled())
		{
			vector.x = (App->player1->position.x - (App->render->camera.x + position.x));
			vector.y = (App->player1->position.y - (App->render->camera.y + position.y));
			distance[0] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
			vector.x = (App->player2->position.x - (App->render->camera.x + position.x));
			vector.y = (App->player2->position.y - (App->render->camera.y + position.y));
			distance[1] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
			if (distance[0] <= distance[1])
				player = App->player1;
			else
				player = App->player2;
		}
		else if (App->player1->IsEnabled() == false)
		{
			player = App->player2;
		}
		else
		{
			player = App->player1;
		}
		//---------------------------------------------------------------------------------------
		for (int i = 0; i < 2; i++)
		{
			vector.x = (player->position.x - (App->render->camera.x + position.x + 13));
			vector.y = (player->position.y - (App->render->camera.y + position.y));
			angle = atan(vector.x / vector.y) * 180 / PI;
			if (vector.y > 0) angle = 360 - 90 + angle;
			else angle = 90 + angle;

			if (angle >= 0 && angle < 34)
			{
				App->render->Blit(texture, App->render->camera.x + position.x - 1, App->render->camera.y + position.y - 9, &angles[0]);
			}
			else
			{
				App->render->Blit(texture, (App->render->camera.x + position.x - 1), (App->render->camera.y + position.y - ((angle < 125 && angle > 34) ? 9 : 8)), &angles[(int)((float)angle / 11.25f)]);
			}
		}
	}
}

void Enemy_General_Turret::DeadAnim()
{
	animation = &dead;
	position.y += 0.09f; //Perque es mogui a la mateixa velocitat que l'overlay
}

void Enemy_General_Turret::Drop()
{
	if (wave == 3)
	{
		App->powerup->AddPowerUp(COIN, App->render->camera.x + position.x + 8, App->render->camera.y + position.y + 9);
	}
}