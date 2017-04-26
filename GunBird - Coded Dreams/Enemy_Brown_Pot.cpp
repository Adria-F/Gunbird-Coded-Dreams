#include "Application.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"
#include "Enemy_Brown_Pot.h"

Enemy_Brown_Pot::Enemy_Brown_Pot(int x, int y) : Enemy(x, y)
{
	NormalSprite = App->textures->Load("assets/enemies/pot.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_pot.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_pot.png");
	
	anim.PushBack({ 0, 0, 36, 53 });
	anim.speed = 0.2f;
	animation = &anim;

	lives = 3;
	initial_hp = 3;
	
	collider = App->collision->AddCollider({8, 840, 36, 53}, COLLIDER_BUILDING, (Module*)App->enemies);
}

Enemy_Brown_Pot::~Enemy_Brown_Pot()
{
	if (NormalSprite != nullptr)
	{
		App->textures->Unload(NormalSprite);
		NormalSprite = nullptr;
	}
	
	if (RedSprite != nullptr)
	{
		App->textures->Unload(RedSprite);
		RedSprite = nullptr;
	}

	if (WhiteSprite != nullptr)
	{
		App->textures->Unload(WhiteSprite);
		WhiteSprite = nullptr;
	}
}