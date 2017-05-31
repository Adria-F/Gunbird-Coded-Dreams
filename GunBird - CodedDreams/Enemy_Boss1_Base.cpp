#include "Enemy_Boss1_Base.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"

Enemy_Boss1_Base::Enemy_Boss1_Base(int x, int y, int wave): Enemy(x, y)
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


	protection.PushBack({ 482, 408, 160, 111 });
	protection.speed = 0.2f;
	protection.loop = false;


	//Set path
	path.PushBack({ 0.0f, 0.09f }, 670, &base);
	path.PushBack({ 0.0f, -0.9f }, 300, &base);
	path.PushBack({ 0.0f, -0.3f }, 1000, &base);

	path.PushBack({ 0.0f, 0.09f }, 670, &protection);
	//path.PushBack({ 0.0f, -0.9f }, 670, &protection);
	//path.PushBack({ 0.0f, -0.3f }, 670, &protection);

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = false;

	//Spawning all the parts
	if(wave == 1)
	{
		App->enemies->AddEnemy(ANTIAIRCRAFT, 33, 3180 );
		App->enemies->AddEnemy(RIGHTSIDE, 128, 3164);
		App->enemies->AddEnemy(LEFTSIDE, 38, 3165);
		App->enemies->AddEnemy(CENTRALSIDE, 88, 3150);

	}
	if (wave == 2)
	{
		App->enemies->AddEnemy(ANTIAIRCRAFT, 33, 2300);
		App->enemies->AddEnemy(RIGHTSIDE, 128, 2314);
		App->enemies->AddEnemy(LEFTSIDE, 38, 2313);
		App->enemies->AddEnemy(CENTRALSIDE, 88, 2300);
	}


	collider = App->collision->AddCollider({ x, y, 0, 0 }, COLLIDER_NONE, (Module*)App->enemies);
}

Enemy_Boss1_Base::~Enemy_Boss1_Base()
{
	App->textures->Unload(NormalSprite);
}
void Enemy_Boss1_Base::ExtraAnim(SDL_Texture* texture)
{

	App->render->Blit(texture, App->render->camera.x + position.x + 5, App->render->camera.y + position.y - 9, &protection.GetCurrentFrame());
}
void Enemy_Boss1_Base::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
	lower_level = false;
}