#include "Enemy_Boss1_Base.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Boss1_Base::Enemy_Boss1_Base(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_base.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	base.PushBack({ 0, 0, 125, 137 });
	base.speed = 0.02f;
	base.loop = true;

	//Set path
	path.PushBack({0.0f, 0.09f}, 100, &base); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = false;

	collider = App->collision->AddCollider({ x, y, 0, 0 }, COLLIDER_NONE, (Module*)App->enemies);
}

Enemy_Boss1_Base::~Enemy_Boss1_Base()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Boss1_Base::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	lower_level = true;
}