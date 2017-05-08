#include "Enemy_Drone.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Drone::Enemy_Drone(int x, int y) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/drone.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop

	//Low level
	idle.PushBack({ 12, 37, 38, 38 });
	idle.PushBack({ 58, 37, 38, 38 });
	idle.PushBack({ 106, 39, 38, 38 });
	idle.PushBack({ 163, 39, 38, 38 });
	idle.PushBack({ 55, 90, 38, 38 });
	idle.PushBack({ 107, 90, 38, 38 });
	idle.PushBack({ 163, 90, 38, 38 });
	idle.speed = 0.15f;
	idle.loop = true;

	//Death
	dead.PushBack({ 16, 132, 32, 58 });
	dead.PushBack({ 80, 132, 32, 58 });
	dead.speed = 0.1f;
	dead.loop = true;

	//Set path
	path.PushBack({ 1.0f, 0.0f }, 100, &idle); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

													 //Set lives, initial_hp, points adn extra_anim
	lives = 10;
	initial_hp = lives;
	points = 500;
	extra_anim = false;

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 38, 38 }, COLLIDER_ENEMY, (Module*)App->enemies);
}

Enemy_Drone::~Enemy_Drone()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Drone::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}

void Enemy_Drone::ExtraAnim(SDL_Texture* texture)
{
	//Si l'enemic no te extra animation no cal posar aquesta funció ni aqui ni al header
}

void Enemy_Drone::DeadAnim()
{
	animation = &dead;
	position.y += 0.2f; //Perque es mogui a la mateixa velocitat que l'overlay
}
