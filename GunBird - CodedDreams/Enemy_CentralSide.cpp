#include "Enemy_CentralSide.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_CentralSide::Enemy_CentralSide(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_central_side.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	idle.PushBack({ 0, 103, 48, 91 });
	idle.PushBack({ 49, 103, 48, 91 });
	idle.PushBack({ 98, 103, 48, 91 });
	idle.PushBack({ 147, 103, 48, 91 });

	idle.PushBack({ 0, 195, 48, 91 });
	idle.PushBack({ 49, 195, 48, 91 });
	idle.PushBack({ 98, 195, 48, 91 });
	idle.PushBack({ 147, 195, 48, 91 });

	idle.speed = 0.02f;
	idle.loop = true;

	vault.PushBack({ 0, 0, 48, 91 });
	vault.PushBack({ 49, 0, 48, 91 });
	vault.PushBack({ 98, 0, 48, 91 });
	vault.PushBack({ 147, 0, 48, 91 });

	vault.speed = 0.02f;
	vault.loop = false;

	//Set path
	path.PushBack({ 0.0f, 0.9f }, 400, &vault);
	path.PushBack({0.0f, 0.09f}, 100, &idle); 

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = true;

	collider = App->collision->AddCollider({ x, y, 0, 0 }, COLLIDER_NONE, (Module*)App->enemies);
}

Enemy_CentralSide::~Enemy_CentralSide()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_CentralSide::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	//lower_level = true;
}