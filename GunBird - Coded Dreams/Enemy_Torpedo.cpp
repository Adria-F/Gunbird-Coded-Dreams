#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Torpedo.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"

Enemy_Torpedo::Enemy_Torpedo(int x, int y) : Enemy(x, y)
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

	/*path.PushBack({ 1.5f, 1.85f }, 250);
	path.PushBack({ 1.25f, 2.0f }, 50);*/
	path.PushBack({ 1.5f, 1.25f }, 140);
	path.PushBack({ 1.25f, 1.5f }, 140);

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