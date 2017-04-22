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

	//the_trump
	this->id = id;

	if (wave == 1)
	{
		//Up
		anim_pilot.PushBack({ 0, 29, 14, 24 }); //1
		anim_pilot.PushBack({ 19, 29, 15, 25 }); //2
		anim_pilot.PushBack({ 39, 29, 14, 24 }); //3
		anim_pilot.PushBack({ 58, 29, 15, 25 }); //4
		anim_pilot.speed = 0.2f;
		path.PushBack({ 0.0f, -0.6f }, 70);
	}

	else if (wave == 2)
	{
		//Right
		anim_pilot.PushBack({ 0,58, 12,23 });
		anim_pilot.PushBack({ 17,58, 11,24 });
		anim_pilot.PushBack({ 33,58, 12,23 });
		anim_pilot.PushBack({ 50,58, 11,24 });
		anim_pilot.speed = 0.2f;
		path.PushBack({ 0.4f, 0.0f }, 70);
	}

	/*if (App->render->camera.y < 850 && App->render->camera.y <= 801)
	{
		animation = &anim_pilot;
	}
	else if (App->render->camera.y < 800)
	{
		animation = &anim_pilot;
	}
	*/

	animation = &anim_pilot;

	original_pos.x = x;
	original_pos.y = y;
}


Enemy_The_Trump::~Enemy_The_Trump()
{
}

void Enemy_The_Trump::Move()
{
	if (App->render->camera.y > -800 && App->render->camera.y < -735)
	{
		position = original_pos + path.GetCurrentPosition(); //goes up
	}
	else if (App->render->camera.y > -735 && App->render->camera.y < -718)
	{
		position.x = position.x + 1.0f; //goes to the right
	}
	else if (App->render->camera.y > -575 && App->render->camera.y < -550)
	{
		position.y -= 1.0f;
	}
}
