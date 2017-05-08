#include "Enemy_Miners.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Miners::Enemy_Miners(int x, int y, int wave, int id) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Miners.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop

	//left
	left.PushBack({ 58, 83, 11, 23 });//standing still
	left.PushBack({ 58, 8, 11, 22 });//1
	left.PushBack({ 83, 8, 11, 23 });//2
	left.PushBack({ 107, 8, 11, 23 });//3


	left.speed = 0.2f;
	left.loop = true;

	/*
	right.PushBack({ 57, 58, 49, 45 });
	right.PushBack({ 168, 59, 49, 45 });
	right.PushBack({ 273, 57, 49, 45 });
	right.PushBack({ 383, 60, 49, 45 });
	right.PushBack({ 107, 8, 12, 22 });//staying still
	right.speed = 0.1f;
	right.loop = true;
	*/
	//right

	//Set path
	path.PushBack({ -0.25f, 0.0f }, 100, &left); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
	//set live;
	lives = 1;
	extra_anim = false;

}

Enemy_Miners::~Enemy_Miners()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Miners::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	position.y = position.y -0.2;
}