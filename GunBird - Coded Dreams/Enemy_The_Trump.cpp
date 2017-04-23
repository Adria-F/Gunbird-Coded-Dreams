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

		//path
		path.PushBack({ 0.0f, -0.6f }, 100, &anim_pilot_up);
		path.PushBack({ 0.6f, 0.0f }, 55, &anim_pilot_right);
		path.PushBack({ 0.0f, 0.0f }, 100, &anim_pilot_idle);
		path.PushBack({ 0.0f, -0.6f }, 10, &anim_pilot_up);


	/*if (App->render->camera.y < 850 && App->render->camera.y <= 801)
	{
		animation = &anim_pilot;
	}
	else if (App->render->camera.y < 800)
	{
		animation = &anim_pilot;
	}
	*/

	collider = App->collision->AddCollider({ 0, 0 }, COLLIDER_WALL);

	original_pos.x = x;
	original_pos.y = y;
}


Enemy_The_Trump::~Enemy_The_Trump()
{
}

void Enemy_The_Trump::Move()
{
	if (false || App->render->camera.y > -800 && App->render->camera.y < -600)
	{
		position = original_pos + path.GetCurrentPosition(&animation);
	}
	/*else if (App->render->camera.y > -735 && App->render->camera.y < -718)
	{
		position.x = position.x + 1.0f; //goes to the right
	}
	else if (App->render->camera.y > -575 && App->render->camera.y < -550)
	{
		position.y -= 1.0f;
	}*/
}
