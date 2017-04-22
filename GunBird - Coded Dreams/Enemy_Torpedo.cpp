#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Torpedo.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"

Enemy_Torpedo::Enemy_Torpedo(int x, int y, int wave, int id) : Enemy(x, y, wave, id)
{
	sprites = App->textures->Load("assets/enemies/General_Torpedo _ Castle mortar.png");

	anim.PushBack({ 0, 37, 19, 31 });
	anim.PushBack({ 23, 38, 15, 31 });
	anim.PushBack({ 42, 38, 21, 31});
	anim.PushBack({ 65, 38, 25, 31 });
	anim.PushBack({ 0, 74, 27, 31 });
	anim.PushBack({ 30, 74, 25, 31 });
	anim.PushBack({ 60, 74, 21, 31 });
	anim.PushBack({ 84, 74, 15, 31 });
	anim.speed = 0.15f;
	
	this->id = id;

	if (wave == 1)
	{
		path.PushBack({ 1.5f, 1.25f }, 140);
		path.PushBack({ 1.25f, 1.5f }, 140);
	}

	else if (wave == 2)
	{
		path.PushBack({ 0.0f, 0.0f }, 250);
		path.PushBack({ -1.25f,-(App->render->cam_speed) }, 40 + (25 * id));
		path.PushBack({ 0.0f, -(App->render->cam_speed) }, 500);
		
		/*if (6 < id < 14 )
		{
			if (id == 7)
			{
				path.PushBack({ -1.25f, 0.0f }, 65);
				path.PushBack({ 0.0f, 0.0f }, 500);
			}

			else if (id == 8)
			{
				path.PushBack({ -1.25f, 0.0f }, 90);
				path.PushBack({ 0.0f, 0.0f }, 500);
			}
			
			else if (id == 9)
			{
				path.PushBack({ -1.25f, 0.0f }, 115);
				path.PushBack({ 0.0f, 0.0f }, 500);
			}
			else if (id == 10)
			{
				path.PushBack({ -1.25f, 0.0f }, 140);
				path.PushBack({ 0.0f, 0.0f }, 500);
			}
			else if (id == 11)
			{
				path.PushBack({ -1.25f, 0.0f }, 165);
				path.PushBack({ 0.0f, 0.0f }, 500);
			}
			else if (id == 12)
			{
				path.PushBack({ -1.25f, 0.0f }, 190);
				path.PushBack({ 0.0f, 0.0f }, 500);
			}	
			else if (id == 13)
			{
				path.PushBack({ -1.25f, 0.0f }, 215);
				path.PushBack({ 0.0f, 0.0f }, 500);
			}
		}*/
		
	}
	else if (wave == 3)
	{

	}
	lives = 12;
	animation = &anim;

	collider = App->collision->AddCollider({ 162, 1596, 22, 31 }, COLLIDER_DROPPING_ENEMY, (Module*)App->enemies);
	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Torpedo::Move()
{
	position = original_pos + path.GetCurrentPosition();
}