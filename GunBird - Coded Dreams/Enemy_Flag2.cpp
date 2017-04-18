#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Flag2.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"

Enemy_Flag2::Enemy_Flag2(int x, int y) : Enemy(x, y)
{
	sprites = App->textures->Load("assets/maps/Castle_Sprites.png");
	anim.PushBack({ 13, 95, 69, 23 });
	anim.PushBack({ 13, 121, 69, 23 });
	anim.PushBack({ 13, 146, 69, 23 });
	anim.PushBack({ 13, 171, 69, 23 });
	anim.PushBack({ 13, 196, 69, 23 });
	anim.PushBack({ 88, 98, 69, 23 });
	anim.PushBack({ 89, 127, 65, 21 });
	anim.PushBack({ 89, 154, 65, 21 });
	anim.speed = 0.07f;
	animation = &anim;
}
