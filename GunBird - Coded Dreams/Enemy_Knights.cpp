#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Knights.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"


Enemy_Knights::Enemy_Knights(int x, int y, int wave, int id) : Enemy(x, y, wave, id)
{
	sprites = App->textures->Load("assets/maps/Castle Knights.png");

	//knights
	this->id = id;

	if (wave == 1)
	{
		//left
		anim.PushBack({ 0, 29, 11, 25 }); //1
		anim.PushBack({ 16, 29, 12, 24 }); //2
		anim.PushBack({ 33, 29, 11, 25 }); //3
		anim.PushBack({ 49, 29, 11, 24 }); //4
		anim.speed = 0.2f;
		path.PushBack({ -0.4f, 0.0f }, -140);
	}
	else if (wave == 2)
	{
		//up
		anim.PushBack({ 0, 0, 15, 24 });
		anim.PushBack({ 20, 0, 14, 24 });
		anim.PushBack({ 39, 0, 14, 24 });
		anim.PushBack({ 59, 0, 14, 24 });
		anim.speed = 0.2f;
		path.PushBack({ 0.0f, -0.4f }, -140);
	}
	else if (wave == 3)
	{

	}

	animation = &anim;
	original_pos.x = x;
	original_pos.y = y;
}


Enemy_Knights::~Enemy_Knights()
{
}

void Enemy_Knights::Move()
{
	if (wave == 1)
	{
		position = original_pos + path.GetCurrentPosition();
	}
	else if (position.y >= 1610 && wave == 2)
	{
		position = original_pos + path.GetCurrentPosition();
	}
	else if (wave == 3)
	{
		position = original_pos + path.GetCurrentPosition();
	}

}
