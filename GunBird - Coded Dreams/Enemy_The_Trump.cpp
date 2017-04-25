#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_The_Trump.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"


Enemy_The_Trump::Enemy_The_Trump(int x, int y, int wave, int id) : Enemy(x, y, wave, id)
{
	sprites = App->textures->Load("assets/maps/castle_the_trump.png");
	texture_bg_upper = App->textures->Load("assets/maps/castle_bg_upper.png");
	texture_bg_upper2 = App->textures->Load("assets/maps/castle_bg_upper2.png");
	rect_background_upper.w = SCREEN_WIDTH;
	rect_background_upper.h = 2108;
	rect_background_upper.x = 0;
	rect_background_upper.y = 0;
	//the_trump
	this->id = id;

		//Up pilot
		anim_pilot_up.PushBack({ 0, 29, 14, 24 }); //1
		anim_pilot_up.PushBack({ 19, 29, 15, 25 }); //2
		anim_pilot_up.PushBack({ 39, 29, 14, 24 }); //3
		anim_pilot_up.PushBack({ 58, 29, 15, 25 }); //4
		anim_pilot_up.speed = 0.2f;
		
		//Right pilot
		anim_pilot_right.PushBack({ 0, 58, 12, 23 });
		anim_pilot_right.PushBack({ 17, 58, 11, 24 });
		anim_pilot_right.PushBack({ 33, 58, 12, 23 });
		anim_pilot_right.PushBack({ 50, 58, 11, 24 });
		anim_pilot_right.speed = 0.2f;

		//idle pilot
		anim_pilot_idle.PushBack({ 0, 114, 15, 26 });
		anim_pilot_idle.PushBack({ 20, 113, 15, 25 });
		anim_pilot_idle.speed = 0.1f;

		//idle girl
		anim_girl_idle.PushBack({ 189, 165, 13 ,23 });
		anim_girl_idle.PushBack({ 170, 166, 13, 23 });
		anim_girl_idle.speed = 0.1f;

		//turning girl
		anim_girl_turning.PushBack({ 170, 110, 11, 22 });
		anim_girl_turning.PushBack({ 185, 82, 10, 21 });
		anim_girl_turning.speed = 0.1f;

		//Up girl
		anim_girl_up.PushBack({ 170, 27, 12, 21});
		anim_girl_up.PushBack({ 188, 27, 14, 22 });
		anim_girl_up.PushBack({ 208, 27, 14, 22 });
		anim_girl_up.PushBack({ 228, 27, 13, 21 });
		anim_girl_up.speed = 0.2f;

		//idle boy
		anim_boy_idle.PushBack({ 103, 109, 12, 23 });
		anim_boy_idle.PushBack({ 85, 110, 12, 23 });
		anim_boy_idle.speed = 0.1f;

		//turning boy
		anim_boy_turning.PushBack({ 85, 139, 11, 23 });
		anim_boy_turning.PushBack({ 134, 83, 10, 20 });
		anim_boy_turning.speed = 0.1f;

		//Up boy
		anim_boy_up.PushBack({ 85, 28, 14, 22 });
		anim_boy_up.PushBack({ 105, 28, 13, 21 });
		anim_boy_up.PushBack({ 124, 28, 14, 22 });
		anim_boy_up.PushBack({ 144, 28, 13, 21 });
		anim_boy_up.speed = 0.2f;

		//path
		if (wave == 1)
		{
			path.PushBack({ 0.0f, -0.6f }, 100, &anim_pilot_up);
			path.PushBack({ 0.6f, 0.0f }, 55, &anim_pilot_right);
			path.PushBack({ 0.0f, 0.0f }, 100, &anim_pilot_idle);
			path.PushBack({ 0.0f, -0.6f }, 10, &anim_pilot_up);
		}

		else if (wave == 2)
		{
			path.PushBack({ 0.0f, 0.0f }, 600, &anim_boy_idle);
			path.PushBack({ 0.0f, 0.0f }, 20, &anim_boy_turning);
			path.PushBack({ 0.0f, -0.6f }, 500, &anim_boy_up);
		}
		
		if (wave == 3)
		{
			path.PushBack({ 0.0f, 0.0f }, 600, &anim_girl_idle);
			path.PushBack({ 0.0f, 0.0f }, 20, &anim_girl_turning);
			path.PushBack({ 0.0f, -0.6f }, 500, &anim_girl_up);
		}


	collider = App->collision->AddCollider({ 0, 0 }, COLLIDER_WALL);

	original_pos.x = x;
	original_pos.y = y;

	extra_anim = true;
	lives = 1;
}


Enemy_The_Trump::~Enemy_The_Trump()
{
}

void Enemy_The_Trump::Move()
{
	if (id == 1 && position.y >= 725)
	{
		position = original_pos + path.GetCurrentPosition(&animation);
	}
	else if (id == 2 && position.y >= 600)
	{
		position = original_pos + path.GetCurrentPosition(&animation);
	}
}

void Enemy_The_Trump::ExtraAnim()
{
	if (id == 1)
	{
		App->render->Blit(texture_bg_upper, App->render->camera.x, App->render->camera.y, &rect_background_upper, 0.75f);
	}
	else
	{
		App->render->Blit(texture_bg_upper2, App->render->camera.x, App->render->camera.y, &rect_background_upper, 0.75f);
	}
}
