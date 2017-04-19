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

	extra_anim = true;
	flag_anim.PushBack({ 13, 95, 69, 23 });
	flag_anim.PushBack({ 13, 121, 69, 23 });
	flag_anim.PushBack({ 13, 146, 69, 23 });
	flag_anim.PushBack({ 13, 171, 69, 23 });
	flag_anim.PushBack({ 13, 196, 69, 23 });
	flag_anim.PushBack({ 88, 98, 69, 23 });
	flag_anim.PushBack({ 89, 127, 65, 21 });
	flag_anim.PushBack({ 89, 154, 65, 21 });
	flag_anim.speed = 0.07f;
	

	collider = App->collision->AddCollider({ 145, 1415, 64, 86 }, COLLIDER_BUILDING, (Module*)App->enemies);
}

void Enemy_Building1::Move()
{
	
}

void Enemy_Building1::ExtraAnim()
{
	App->render->Blit(sprites, App->render->camera.x + position.x + 30, App->render->camera.y + position.y - 12, &(flag_anim.GetCurrentFrame()));
}
