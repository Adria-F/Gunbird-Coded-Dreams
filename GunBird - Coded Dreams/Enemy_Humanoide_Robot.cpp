#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Humanoide_Robot.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"

Enemy_Humanoide_Robot::Enemy_Humanoide_Robot(int x, int y) : Enemy(x, y)
{
	sprites = App->textures->Load("assets/enemies/Humanoide_Robot.png");

	anim.PushBack({ 0, 0, 32, 32 });
	anim.PushBack({ 34, 0, 32,32 });
	anim.PushBack({ 68, 0, 32, 32 });
	anim.PushBack({ 102, 0, 32, 32 });
	anim.speed = 0.1f;

	animation = &anim;

	collider = App->collision->AddCollider({ 162, 1596, 32, 32 }, COLLIDER_DROPPING_ENEMY, App->scene_castle);
}

void Enemy_Humanoide_Robot::Move()
{

}