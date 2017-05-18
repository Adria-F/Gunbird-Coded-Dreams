#include "Enemy_Barrel.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Barrel::Enemy_Barrel(int x, int y) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/barrel.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_barrel.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_barrel.png");

	//Set animation steps, speed and loop

	//Low level
	idle.PushBack({ 0, 0, 44, 30 });
	idle.speed = 0.1f;
	idle.loop = false;

	//Death
	dead.PushBack({ 0, 33, 53, 39 });
	dead.PushBack({ 54, 33, 53, 39 });
	dead.PushBack({ 108, 33, 53, 39 });

	dead.PushBack({ 0, 73, 53, 39 });
	dead.PushBack({ 54, 73, 53, 39 });
	dead.PushBack({ 108, 73, 53, 39 });

	dead.PushBack({ 0, 113, 53, 39 });
	dead.PushBack({ 54, 113, 53, 39 });
	dead.speed = 0.1f;
	dead.loop = true;

	path.PushBack({ 0.0f, 0.09f }, 100, &idle);

	//Set lives, initial_hp, points adn extra_anim
	lives = 20;
	initial_hp = lives;
	points = 1000;
	extra_anim = false;
	explosion_type = BIG1;

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 44, 30 }, COLLIDER_ENEMY, (Module*)App->enemies);
}

Enemy_Barrel::~Enemy_Barrel()
{
}

void Enemy_Barrel::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}

void Enemy_Barrel::DeadAnim()
{
	animation = &dead;
	position.y += 0.09f;
}