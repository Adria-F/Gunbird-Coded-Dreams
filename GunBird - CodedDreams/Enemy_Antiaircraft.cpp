#include "Enemy_Antiaircraft.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Antiaircraft::Enemy_Antiaircraft(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_antiaircraft.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	left_closed.PushBack({ 1, 1, 58, 53 });
	left_closed.PushBack({ 71, 1, 58, 53 });
	left_closed.PushBack({ 211, 1, 58, 53 });
	left_closed.speed = 0.02f;
	left_closed.loop = true;

	left_opening.PushBack({ 1, 1, 59, 53 });
	left_opening.PushBack({ 71, 58, 59, 53 });
	left_opening.PushBack({ 141, 58, 61, 54 });
	left_opening.PushBack({ 211, 58, 61, 54 });
	left_opening.PushBack({ 281, 58, 66, 54 });
	left_opening.PushBack({ 351, 58, 67, 55 });
	left_opening.speed = 0.02f;
	left_opening.loop = true;

	left_idle.PushBack({ 1, 115, 67, 55 });
	left_idle.PushBack({ 71, 115, 67, 55 });
	left_idle.PushBack({ 141, 115, 67, 55 });
	left_idle.PushBack({ 211, 115, 67, 55 });
	left_idle.speed = 0.02f;
	left_idle.loop = true;

	

	//Set path
	path.PushBack({0.0f, 0.09f}, 100, &left_opening); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = false;
	lower_level = false;
	collider = App->collision->AddCollider({ x, y, 0, 0 }, COLLIDER_NONE, (Module*)App->enemies);
}

Enemy_Antiaircraft::~Enemy_Antiaircraft()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Antiaircraft::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);

}