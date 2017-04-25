#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Knights.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"
#include "Enemy_Building1.h"


Enemy_Knights::Enemy_Knights(int x, int y, int wave, int id) : Enemy(x, y, wave, id)
{
	NormalSprite = App->textures->Load("assets/maps/Castle Knights.png");
	texture_bg_upper = App->textures->Load("assets/maps/castle_bg_upper1.png");
	rect_background_upper.w = SCREEN_WIDTH;
	rect_background_upper.h = 2108;
	rect_background_upper.x = 0;
	rect_background_upper.y = 0;

	//left
	anim_left.PushBack({ 0, 29, 11, 25 }); //1
	anim_left.PushBack({ 16, 29, 12, 24 }); //2
	anim_left.PushBack({ 33, 29, 11, 25 }); //3
	anim_left.PushBack({ 49, 29, 11, 24 }); //4
	anim_left.speed = 0.2f;

	//up
	anim_up.PushBack({ 0, 0, 15, 24 });
	anim_up.PushBack({ 20, 0, 14, 24 });
	anim_up.PushBack({ 39, 0, 14, 24 });
	anim_up.PushBack({ 59, 0, 14, 24 });
	anim_up.speed = 0.2f;

	//down
	anim_down.PushBack({ 0, 86, 15, 23 });
	anim_down.PushBack({ 20, 86, 15, 24 });
	anim_down.PushBack({ 40, 86, 14, 23 });
	anim_down.PushBack({ 60, 86, 15, 24 });
	anim_down.speed = 0.2f;

	//confused
	anim_confused.PushBack({ 20, 0, 14, 23 }); //up
	anim_confused.PushBack({ 16, 58, 12, 24 }); //right
	anim_confused.PushBack({ 20, 86, 15, 24 }); //down
	anim_confused.PushBack({ 16, 29, 12, 24 }); //left
	anim_confused.speed = 0.2f;

	this->id = id;

	if (wave == 1)
	{
		
		path.PushBack({ -0.4f, 0.0f }, 140, &anim_left);
	}
	else if (wave == 2)
	{
	
		path.PushBack({ 0.0f, -0.4f }, 140, &anim_up);
	}
	else if (wave == 3)
	{
		
		path.PushBack({ 0.0f, 0.8f }, 100, &anim_down);
		path.PushBack({ 0.0f, 0.0f }, 1000, &anim_confused);
	}

	collider = App->collision->AddCollider({ 0, 0 }, COLLIDER_WALL);

	original_pos.x = x;
	original_pos.y = y;

	extra_anim = true;
	lives = 1;
}


Enemy_Knights::~Enemy_Knights()
{
}

void Enemy_Knights::Move()
{
	if (wave == 1)
	{
		position = original_pos + path.GetCurrentPosition(&animation);
	}
	if (wave == 2 && position.y >= 1590)
	{
		position = original_pos + path.GetCurrentPosition(&animation);
	}
	if (wave == 3)
	{
		position = original_pos + path.GetCurrentPosition(&animation);
	}
}

void Enemy_Knights::ExtraAnim(SDL_Texture* texture)
{
	if (id == 1)
	{

	}
	else
		App->render->Blit(texture_bg_upper, App->render->camera.x, App->render->camera.y, &rect_background_upper, 0.75f);
}