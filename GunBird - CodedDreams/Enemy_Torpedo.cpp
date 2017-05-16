#include "Enemy_Torpedo.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Torpedo::Enemy_Torpedo(int x, int y, int wave) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/torpedo.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_torpedo.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_torpedo.png");

	//Set animation steps, speed and loop
	idle.PushBack({ 0, 37, 28, 32 });
	idle.PushBack({ 29, 38, 28, 32 });
	idle.PushBack({ 57, 38, 28, 32 });
	idle.PushBack({ 84, 38, 28, 32 });
	idle.PushBack({ 0, 74, 28, 32 });
	idle.PushBack({ 29, 74, 28, 32 });
	idle.PushBack({ 57, 74, 28, 32 });
	idle.PushBack({ 84, 74, 28, 32 });
	idle.speed = 0.4f;
	idle.loop = true;

	//Set path
	if (wave == 1)
	{
		path.PushBack({ 1.6f, 2.0f }, 75, &idle);
		path.PushBack({ 1.35f, 2.75f }, 140, &idle);
	}

	else if (wave == 2)
	{
		path.PushBack({ -1.6f, 2.0f }, 60, &idle);
		path.PushBack({ -1.35f, 2.75f }, 140, &idle);
	}
	 //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

											   //Set lives, initial_hp, points adn extra_anim
	lives = 5;
	initial_hp = lives;
	points = 200;
	extra_anim = false;
	explosion_type = SMALL1;

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 23, 31 }, COLLIDER_AIR_ENEMY, (Module*)App->enemies);
}

Enemy_Torpedo::~Enemy_Torpedo()
{
}

void Enemy_Torpedo::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}
