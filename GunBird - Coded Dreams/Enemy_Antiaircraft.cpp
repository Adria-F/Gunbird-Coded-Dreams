#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Antiaircraft.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"

Enemy_Antiaircraft::Enemy_Antiaircraft(int x, int y): Enemy(x, y)
{
	sprites = App->textures->Load("assets/enemies/General_Torpedo _ Castle mortar.png");
	
	anim.PushBack({ 0, 0, 32, 32 });
	anim.PushBack({ 34, 0, 32,32 });
	anim.PushBack({ 68, 0, 32, 32 });
	anim.PushBack({ 102, 0, 32, 32 });
	anim.speed = 0.1f;

	animation = &anim;

	lives = 24;

	collider = App->collision->AddCollider({162, 1596, 32, 32 }, COLLIDER_DROPPING_ENEMY, (Module*)App->enemies);
}

void Enemy_Antiaircraft::Move()
{

}

void Enemy_Antiaircraft::DeadAnim()
{

}