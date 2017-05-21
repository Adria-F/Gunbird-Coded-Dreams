#include "Enemy_CentralSide.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "p2Point.h"

Enemy_CentralSide::Enemy_CentralSide(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_central_side.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	//Vault Open
	vault_open.PushBack({ 0, 0, 48, 102 });

	vault_open.speed = 0.02f;
	vault_open.loop = false;


	//Boss Moving
	moving.PushBack({ 0, 103, 48, 102 });
	moving.PushBack({ 49, 103, 48, 102 });
	moving.PushBack({ 98, 103, 48, 102 });
	moving.PushBack({ 147, 103, 48, 102 });

	moving.PushBack({ 0, 206, 48, 102 });
	moving.PushBack({ 49, 206, 48, 102 });
	moving.PushBack({ 98, 206, 48, 102 });
	moving.PushBack({ 147, 206, 48, 102 });

	moving.speed = 0.02f;
	moving.loop = true;

	//Vault Closing
	vault_closing.PushBack({ 0, 0, 48, 102 });
	vault_closing.PushBack({ 49, 0, 48, 102 });
	vault_closing.PushBack({ 98, 0, 48, 102 });
	vault_closing.PushBack({ 147, 0, 48, 102 });

	vault_closing.speed = 0.2f;
	vault_closing.loop = false;

	//Set path
	path.PushBack({ 0.0f, 0.09f }, 600, &vault_open);
	path.PushBack({ 0.0f, 0.09f }, 30, &vault_closing);
	path.PushBack({ 0.0f, -0.9f }, 1000, &moving);

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = true;

	//collider
	collider = App->collision->AddCollider({ x, y, 0, 0 }, COLLIDER_NONE, (Module*)App->enemies);
}

Enemy_CentralSide::~Enemy_CentralSide()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_CentralSide::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	lower_level = true;
}