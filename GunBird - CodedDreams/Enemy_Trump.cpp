#include "Enemy_Trump.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleRender.h"

Enemy_Trump::Enemy_Trump(int x, int y, int wave, int id) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Miners.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop

	//left
	anim.PushBack({ 58, 83, 11, 23 });//standing still

	anim.speed = 0.2f;
	anim.loop = true;


	//Set path
	if (wave == 1)
	{
		path.PushBack({ -0.40f, 0.09f }, 50, &anim);
	}

	//set live;
	lives = 1;
	extra_anim = false;

}

Enemy_Trump::~Enemy_Trump()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Trump::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}
