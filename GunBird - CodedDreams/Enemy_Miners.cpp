#include "Enemy_Miners.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleRender.h"

Enemy_Miners::Enemy_Miners(int x, int y, int wave, int id) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Miners.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop

	//left
	left.PushBack({ 58, 83, 11, 23 });//standing still
	left.PushBack({ 58, 8, 11, 22 });//1
	left.PushBack({ 83, 8, 11, 23 });//2
	left.PushBack({ 107, 8, 11, 23 });//3
	left.speed = 0.2f;
	left.loop = true;

	//look									  

	look.PushBack({ 31, 8, 13, 22 });
	look.PushBack({ 7, 8, 15, 22 });
	look.PushBack({ 7, 8, 15, 22 });
	look.PushBack({ 7, 8, 15, 22 });
	look.PushBack({ 7, 8, 15, 22 });
	look.PushBack({ 7, 8, 15, 22 });
	look.PushBack({ 31, 8, 13, 22 });
	look.speed = 0.1f;
	look.loop = false;

	//right
	right.PushBack({ 9, 83, 11, 23 });
	right.PushBack({ 58, 45, 11, 22 });
	right.PushBack({ 84, 45, 11, 23 });
	right.PushBack({ 107, 45, 11, 22 });
	right.speed = 0.2f;
	right.loop = true;
	
	//Set path
	if (wave == 1)
	{
		path.PushBack({ -0.40f, 0.09f }, 50, &left);
	}
	if (wave == 2)
	{
		path.PushBack({ -0.40f, 0.09f }, 150, &left);
		path.PushBack({ 0.0f, 0.09f }, 70, &look);
		path.PushBack({ -0.40f, 0.09f }, 200, &left);
	}
	if (wave == 3)
	{
		path.PushBack({ -0.40f, 0.09f }, 100, &left);
		path.PushBack({ 0.0f, 0.09f }, 70, &look);
		path.PushBack({ -0.40f, 0.09f }, 200, &left);
	}
	if (wave == 4)
	{
		path.PushBack({ 0.40f, 0.09f }, 100, &right);
	}
	

	//set live;
	lives = 1;
	extra_anim = false;

}

Enemy_Miners::~Enemy_Miners()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Miners::Move()
{
		position = original_pos + path.GetCurrentPosition(&animation);

}