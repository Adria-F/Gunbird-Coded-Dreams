#include "Enemy_Tank.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Tank::Enemy_Tank(int x, int y, int wave) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/tank.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_tank.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_tank.png");

	//Set animation steps, speed and loop
	idle.PushBack({ 12, 16, 42, 48 });
	idle.PushBack({ 76, 16, 42, 48 });
	idle.speed = 0.1f;
	idle.loop = true;

	dead.PushBack({ 16, 132, 32, 58 });
	dead.speed = 0.1f;
	dead.loop = true;

	//Set path
	path.PushBack({ 0.0f, 0.2f }, 100, &idle); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

											   //Set lives, initial_hp, points adn extra_anim
	lives = 52;
	initial_hp = lives;
	points = 5000;
	extra_anim = false;
	explosion_type = BIG1; //Explosion type

						   //Add and save collider
	collider = App->collision->AddCollider({ x, y, 42, 48 }, COLLIDER_ENEMY, (Module*)App->enemies);
}

Enemy_Tank::~Enemy_Tank()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Tank::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}

void Enemy_Tank::ExtraAnim(SDL_Texture* texture)
{

}

void Enemy_Tank::DeadAnim()
{
	animation = &dead;
}