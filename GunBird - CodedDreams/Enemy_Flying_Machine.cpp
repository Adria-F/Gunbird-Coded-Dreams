#include "Enemy_Flying_Machine.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Flying_Machine::Enemy_Flying_Machine(int x, int y) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Flying Machine.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop

	//Low level
	idle_low.PushBack({ 57, 58, 49, 45 });
	idle_low.PushBack({ 168, 59, 49, 45 });
	idle_low.PushBack({ 273, 57, 49, 45 });
	idle_low.PushBack({ 383, 60, 49, 45 });
	idle_low.speed = 0.1f;
	idle_low.loop = true;

	//Death
	dead.PushBack({ 16, 132, 32, 58 });
	dead.PushBack({ 80, 132, 32, 58 });
	dead.speed = 0.1f;
	dead.loop = true;

	//Set path
	path.PushBack({ 0.0f, 0.75f }, 100, &idle_low); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

											   //Set lives, initial_hp, points adn extra_anim
	lives = 90;
	initial_hp = lives;
	points = 5000;
	extra_anim = false;

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 42, 48 }, COLLIDER_AIR_ENEMY, (Module*)App->enemies);
}

Enemy_Flying_Machine::~Enemy_Flying_Machine()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Flying_Machine::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}

void Enemy_Flying_Machine::ExtraAnim(SDL_Texture* texture)
{
	//Si l'enemic no te extra animation no cal posar aquesta funció ni aqui ni al header
}

void Enemy_Flying_Machine::DeadAnim()
{
	animation = &dead;
	position.y += 0.2f; //Perque es mogui a la mateixa velocitat que l'overlay
}
