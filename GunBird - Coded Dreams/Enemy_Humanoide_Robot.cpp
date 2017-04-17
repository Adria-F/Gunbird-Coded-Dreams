#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Humanoide_Robot.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"
#include "Path.h"

Enemy_Humanoide_Robot::Enemy_Humanoide_Robot(int x, int y) : Enemy(x, y)
{
	sprites = App->textures->Load("assets/enemies/Humanoide_Robot.png");

	anim.PushBack({ 152, 29, 75, 72 });//2
	anim.PushBack({ 259, 132, 76, 71 });//7
	anim.PushBack({ 258, 31, 75, 72 });//3
	anim.PushBack({ 152, 29, 75, 72 });//2
	anim.PushBack({ 46, 31, 75, 72 });//1
	anim.PushBack({ 154, 133, 76, 72 });//6
	anim.speed = 0.1f;

	if (position.y >= 1370)//intent de que tiri endavant
	{
		path.PushBack({ 0.0f, -0.25f }, 100);
	}
	else if (position.y <= 1370)
	{
		path.PushBack({ 0.0f, 0.25f }, 20);
	}

	
	animation = &anim;

	collider = App->collision->AddCollider({ 70, 1505, 77, 77 }, COLLIDER_DROPPING_ENEMY, App->scene_castle);

	
	
	//collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Humanoide_Robot::Move()
{
	if (position.y >= 1370)
	{
		position = original_pos + path.GetCurrentPosition();
	}
}