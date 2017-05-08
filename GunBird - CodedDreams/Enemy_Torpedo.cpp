#include "Enemy_Torpedo.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Torpedo::Enemy_Torpedo(int x, int y) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Torpedo&Mortar.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	idle.PushBack({ 12, 16, 42, 48 });
	idle.PushBack({ 76, 16, 42, 48 });
	idle.speed = 0.1f;
	idle.loop = true;

	dead.PushBack({ 16, 132, 32, 58 });
	dead.PushBack({ 80, 132, 32, 58 });
	dead.speed = 0.1f;
	dead.loop = true;

	//Set path
	path.PushBack({ 0.0f, 0.2f }, 100, &idle); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

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

void Enemy_Torpedo::ExtraAnim(SDL_Texture* texture)
{
	//Si l'enemic no te extra animation no cal posar aquesta funci� ni aqui ni al header
}

void Enemy_Torpedo::DeadAnim()
{
	animation = &dead;
	position.y += 0.2f; //Perque es mogui a la mateixa velocitat que l'overlay
}