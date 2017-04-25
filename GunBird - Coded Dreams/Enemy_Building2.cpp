#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Building2.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"


Enemy_Building2::Enemy_Building2(int x, int y) : Enemy(x, y)
{
	NormalSprite = App->textures->Load("assets/maps/Castle_Sprites.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_Castle_Sprites.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_Castle_Sprites.png");

	anim.PushBack({ 69, 0, 72, 86 });
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

	dead_build2.PushBack({145, 0, 66,  62});
	dead_build2.speed = 0.1f;

	lives = 25;
	initial_hp = 25;
	points = 3000;

	collider = App->collision->AddCollider({ 75, 1165, 72, 83 }, COLLIDER_BUILDING, (Module*)App->enemies);
}
void Enemy_Building2::Move()
{

}
void Enemy_Building2::ExtraAnim(SDL_Texture* texture)
{
	App->render->Blit(texture, App->render->camera.x + position.x + 34, App->render->camera.y + position.y - 12, &(flag_anim.GetCurrentFrame()));
}

void Enemy_Building2::DeadAnim()
{
	animation = &dead_build2;
	position.y = 1190;
	position.x = 80;
}
