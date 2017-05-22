#include "Enemy_LeftSide.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "p2Point.h"

Enemy_LeftSide::Enemy_LeftSide(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_left_side.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	moving.PushBack({ 0, 0, 58, 89 });
	moving.PushBack({ 72, 0, 58, 89 });
	moving.speed = 0.2f;
	moving.loop = true;

	//Set path
	path.PushBack({ 0.0f, 0.09f }, 670, &moving); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
	path.PushBack({ 0.0f, -0.9f }, 300, &moving);
	path.PushBack({ 0.0f, -0.3f }, 1000, &moving);

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = false;
	Shot_Total_time = (Uint32)(400.0f);

	collider = App->collision->AddCollider({ x, y, 0, 0 }, COLLIDER_NONE, (Module*)App->enemies);
}

Enemy_LeftSide::~Enemy_LeftSide()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_LeftSide::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	lower_level = true;
}