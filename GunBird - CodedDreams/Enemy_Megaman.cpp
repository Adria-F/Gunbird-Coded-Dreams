#include "Enemy_Megaman.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Megaman::Enemy_Megaman(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/spritesheetmegaman1.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	idle.PushBack({ 12, 16, 42, 48 });
	idle.PushBack({ 76, 16, 42, 48 });
	idle.speed = 0.02f;
	idle.loop = true;

	//Set path
	path.PushBack({0.0f, 0.09f}, 100, &idle); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = false;

	collider = App->collision->AddCollider({ x, y, 0, 0 }, COLLIDER_NONE, (Module*)App->enemies);
}

Enemy_Megaman::~Enemy_Megaman()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Megaman::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	lower_level = true;
}