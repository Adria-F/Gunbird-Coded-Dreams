#include "Enemy_Boss1_Base.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleEnemies.h"

Enemy_Boss1_Base::Enemy_Boss1_Base(int x, int y): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_base.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	base.PushBack({ 0, 0, 224, 185 });
	base.PushBack({ 225, 0, 224, 185 });
	base.PushBack({ 450, 0, 224, 185 });

	base.PushBack({ 0, 186, 224, 185 });
	base.PushBack({ 225, 186, 224, 185 });
	base.PushBack({ 450, 186, 224, 185 });

	base.PushBack({ 0, 371, 224, 185 });
	base.PushBack({ 225, 371, 224, 185 });
	base.speed = 0.2f;
	base.loop = true;

	//Set path
	path.PushBack({0.0f, 0.09f}, 100, &base); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = false;

	//Spawning all the parts
	App->enemies->AddEnemy(RIGHTSIDE, 133, 3164);
	App->enemies->AddEnemy(LEFTSIDE, 43, 3165);
	App->enemies->AddEnemy(CENTRALSIDE, 93, 3150);

	collider = App->collision->AddCollider({ x, y, 0, 0 }, COLLIDER_NONE, (Module*)App->enemies);
}

Enemy_Boss1_Base::~Enemy_Boss1_Base()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Boss1_Base::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	lower_level = false;
}