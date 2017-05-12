#include "Enemy_Barrel.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Barrel::Enemy_Barrel(int x, int y) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Flying Machine.png");
	RedSprite = App->textures->Load("assets/enemies//hitten/hitten_red_Flying Machine.png");
	WhiteSprite = App->textures->Load("assets/enemies//hitten/hitten_white_Flying Machine.png");

	//Set animation steps, speed and loop

	//Low level
	idle.PushBack({ 0, 0, 50, 25 });
	idle.speed = 0.1f;
	idle.loop = false;

	//Death
	dead.PushBack({ 0, 0, 50, 30 });
	dead.speed = 0.1f;
	dead.loop = false;

	//Set lives, initial_hp, points adn extra_anim
	lives = 16;
	initial_hp = lives;
	points = 1000;
	extra_anim = false;
	explosion_type = MID1;

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 50, 25 }, COLLIDER_ENEMY, (Module*)App->enemies);
}

Enemy_Barrel::~Enemy_Barrel()
{
}

void Enemy_Barrel::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}