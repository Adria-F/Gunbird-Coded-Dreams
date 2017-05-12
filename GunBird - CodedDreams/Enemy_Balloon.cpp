#include "Enemy_Balloon.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Balloon::Enemy_Balloon(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Balloon.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_Balloon.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_Balloon.png");

	//Set animation steps, speed and loop
	anim.PushBack({ 11, 6, 42, 53 });
	anim.PushBack({ 64, 6, 42, 53 });
	anim.PushBack({ 116, 6, 42, 53 });
	anim.PushBack({ 168, 6, 42, 53 });
	anim.PushBack({ 219, 6, 42, 53 });
	anim.speed = 2.0f;
	anim.loop = true;

	//Set path
	path.PushBack({ 0.0f, 0.9f}, 40, &anim); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
	path.PushBack({ 0.0f, -0.3f }, 240, &anim);
	path.PushBack({ 0.0f, 0.9f }, 60, &anim);
	path.PushBack({ 0.0f, -0.3f }, 350, &anim);
	path.PushBack({ 0.0f, 0.9f }, 600, &anim);

	//Set lives, initial_hp, points adn extra_anim
	lives = 12;
	initial_hp = lives;
	points = 400;
	extra_anim = false;
	explosion_type = BIG1; //Explosion type

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 42, 48 }, COLLIDER_AIR_ENEMY, (Module*)App->enemies);
}

Enemy_Balloon::~Enemy_Balloon()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Balloon::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}

void Enemy_Balloon::DeadAnim()
{
	animation = &dead;
	position.y += 0.2f; //Perque es mogui a la mateixa velocitat que l'overlay
}