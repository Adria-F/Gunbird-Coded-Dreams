#include "Enemy_Boss1_Base.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"

Enemy_Boss1_Base::Enemy_Boss1_Base(int x, int y, int wave, int id): Enemy(x, y)
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

	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = false;

	//Set path
	if (id == 1)
	{
		path.PushBack({ 0.0f, 0.09f }, 670, &base); //wait
		path.PushBack({ 0.0f, -0.9f }, 300, &base); //go to the top
		path.PushBack({ 0.0f, -0.3f }, 4000, &base); // hold position
	}
	if (id == 2)
	{
		path.PushBack({ 0.0f, 0.09f }, 670, &protection); //wait
		path.PushBack({ 0.0f, -0.9f }, 300, &protection); //go to the top
		path.PushBack({ 0.0f, -0.3f }, 350, &protection); //hold position
		path.PushBack({ 0.0f, 0.09f }, 125, &protection); //extend
		path.PushBack({ 0.0f, -0.3f }, 4000, &protection); //hold position
	}

	//Spawning all the parts
	if(wave == 1)
	{

		App->enemies->AddEnemy(BOSS1_BASE, 32, 3145, 0, 2);
		App->enemies->AddEnemy(ANTIAIRCRAFT, 33, 3165, 1); //left
		App->enemies->AddEnemy(ANTIAIRCRAFT, 70, 3165, 2); //right
		App->enemies->AddEnemy(RIGHTSIDE, 112, 3125);
		App->enemies->AddEnemy(LEFTSIDE, 38, 3125);
		App->enemies->AddEnemy(CENTRALSIDE, 88, 3110);

	}
	if (wave == 2)
	{
		App->enemies->AddEnemy(BOSS1_BASE, 32, 2332, 0, 2); //proctection
		App->enemies->AddEnemy(ANTIAIRCRAFT, 33, 2325, 1); // left
		App->enemies->AddEnemy(ANTIAIRCRAFT, 70, 2325, 2); // right
		App->enemies->AddEnemy(RIGHTSIDE, 112, 2310);
		App->enemies->AddEnemy(LEFTSIDE, 38, 2310);
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
	lower_level = true;
}