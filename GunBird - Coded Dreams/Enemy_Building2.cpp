#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Building2.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"

Enemy_Building2::Enemy_Building2(int x, int y) : Enemy(x, y)
{
	sprites = App->textures->Load("assets/maps/Castle_Sprites.png");
	anim.PushBack({ 69, 0, 64, 86 });
	anim.speed = 0.1f;
	animation = &anim;

	collider = App->collision->AddCollider({ 75, 1165, 72, 83 }, COLLIDER_DROPPING_ENEMY, (Module*)App->enemies);
}

