#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Building1.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"

Enemy_Building1::Enemy_Building1(int x, int y): Enemy(x, y)
{
	sprites = App->textures->Load("assets/maps/Castle_Sprites.png");
	anim.PushBack({ 0, 0, 64, 86 });
	anim.speed = 0.1f;
	animation = &anim;

	collider = App->collision->AddCollider({ 145, 1415, 64, 86 }, COLLIDER_BUILDING, (Module*)App->enemies);
}

void Enemy_Building1::Move()
{

}
