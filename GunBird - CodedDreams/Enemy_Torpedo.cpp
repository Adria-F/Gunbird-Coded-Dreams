#include "Enemy_Torpedo.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Torpedo::Enemy_Torpedo(int x, int y) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Torpedo&Mortar.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_torpedo&mortar.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_torpedo&mortar.png");

	//Set animation steps, speed and loop
	idle.PushBack({ 5, 37, 17, 31 });
	idle.PushBack({ 35, 37, 15, 31 });
	idle.PushBack({ 60, 37, 21, 31 });
	idle.PushBack({ 85, 37, 25, 31 });
	idle.PushBack({ 0, 74, 27, 31 });
	idle.PushBack({ 30, 74, 25, 31 });
	idle.PushBack({ 60, 74, 21, 31 });
	idle.PushBack({ 90, 74, 15, 31 });
	idle.speed = 0.1f;
	idle.loop = true;

	//Set path
	path.PushBack({ -0.1f, -0.2f }, 100, &idle); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

											   //Set lives, initial_hp, points adn extra_anim
	lives = 12;
	initial_hp = lives;
	points = 400;
	extra_anim = false;

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 42, 48 }, COLLIDER_ENEMY, (Module*)App->enemies);
}

Enemy_Torpedo::~Enemy_Torpedo()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Torpedo::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}
