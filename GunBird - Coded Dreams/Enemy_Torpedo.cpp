#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Torpedo.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleMarion.h"
#include "ModuleAsh.h"
#include <math.h>

Enemy_Torpedo::Enemy_Torpedo(int x, int y, int wave, int id) : Enemy(x, y, wave, id)
{
	NormalSprite = App->textures->Load("assets/enemies/General_Torpedo _ Castle mortar.png");
	RedSprite = App->textures->Load("assets/enemies/hittenhitten_red_General_Torpedo _ Castle mortar.png");
	WhiteSprite = App->textures->Load("assets/enemies/hittenhitten_white_General_Torpedo _ Castle mortar.png");


	anim.PushBack({ 0, 37, 28, 32 });
	anim.PushBack({ 29, 38, 28, 32 });
	anim.PushBack({ 57, 38, 28, 32 });
	anim.PushBack({ 84, 38, 28, 32 });
	anim.PushBack({ 0, 74, 28, 32 });
	anim.PushBack({ 29, 74, 28, 32 });
	anim.PushBack({ 57, 74, 28, 32 });
	anim.PushBack({ 84, 74, 28, 32 });
	anim.speed = 0.4f;
	
	//this->id = id;

	if (wave == 1)
	{
		path.PushBack({ 1.5f, 1.25f }, 140);
		path.PushBack({ 1.25f, 1.5f }, 140);
	}

	else if (wave == 2)
	{
		path.PushBack({ 0.0f, 0.0f }, 325);
		path.PushBack({ -3.0f,-(App->render->cam_speed) }, 15);
		path.PushBack({ -3.1f,-(App->render->cam_speed) },(10 * id));
		path.PushBack({ 0.0f, -(App->render->cam_speed) }, 100);
		path.PushBack({ 0.0f, 2.3f }, 200);
		
		
	}
	else if (wave == 3)
	{
		if (id == 2 || id == 3)
		{
			ModulePlayer* player;
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
			
			vector.x = player->position.x + 10 - x - 15;
			vector.y = player->position.y - 16 - y + 15;
			if (id == 3)
			{
				vector.x += (vector.x < 0) ? 30 : -30;
			}
			modul = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
			vector.x /= modul;
			vector.y /= modul;
			speed.x = vector.x * 2.3f;
			speed.y = vector.y * -2.3f;
			path.PushBack({ speed.x , speed.y }, 150);
		}
		else
			path.PushBack({ 0.0f, 2.3f }, 150);

	}
	lives = 12;
	initial_hp = 12;
	points = 200;
	animation = &anim;

	collider = App->collision->AddCollider({ 162, 1596, 22, 31 }, COLLIDER_DROPPING_ENEMY, (Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Torpedo::Move()
{
	position = original_pos + path.GetCurrentPosition();
}