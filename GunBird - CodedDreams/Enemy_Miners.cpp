#include "Enemy_Miners.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Miners::Enemy_Miners(int x, int y) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Miners.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop

	//left
	anim.PushBack({ 57, 58, 49, 45 });
	anim.PushBack({ 168, 59, 49, 45 });
	anim.PushBack({ 273, 57, 49, 45 });
	anim.PushBack({ 383, 60, 49, 45 });
	anim.speed = 0.1f;
	anim.loop = true;

	//Death
	dead.PushBack({ 16, 132, 32, 58 });
	dead.PushBack({ 80, 132, 32, 58 });
	dead.speed = 0.1f;
	dead.loop = true;

	//Set path
	path.PushBack({ 0.0f, 0.75f }, 100, &anim); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

													//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	points = 5000;
	extra_anim = false;

}

Enemy_Miners::~Enemy_Miners()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Miners::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}

void Enemy_Miners::ExtraAnim(SDL_Texture* texture)
{
	//Si l'enemic no te extra animation no cal posar aquesta funció ni aqui ni al header
}

void Enemy_Miners::DeadAnim()
{
	animation = &dead;
	position.y += 0.2f; //Perque es mogui a la mateixa velocitat que l'overlay
}
