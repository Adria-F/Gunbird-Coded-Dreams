#include "Application.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"
#include "Enemy_Brown_Pot.h"

Enemy_Brown_Pot::Enemy_Brown_Pot(int x, int y) : Enemy(x, y)
{
	NormalSprite = App->textures->Load("assets/maps/pot.png");
	
	anim.PushBack({ 342, 202, 36, 53 });
	anim.speed = 0.2f;
	animation = &anim;

	lives = 3;
	initial_hp = 3;
	
	collider = App->collision->AddCollider({8, 840, 36, 53}, COLLIDER_BUILDING, (Module*)App->enemies);
}
