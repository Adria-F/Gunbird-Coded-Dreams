#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Antiaircraft.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include <math.h>
#include "SDL/include/SDL_timer.h"


Enemy_Antiaircraft::Enemy_Antiaircraft(int x, int y): Enemy(x, y)
{
	sprites = App->textures->Load("assets/enemies/General_Torpedo _ Castle mortar.png");
	
	anim.PushBack({ 0, 0, 32, 32 });
	anim.PushBack({ 34, 0, 32, 32 });
	anim.PushBack({ 68, 0, 32, 32 });
	anim.PushBack({ 102, 0, 32, 32 });
	anim.speed = 0.1f;

	extra_anim = true;
	open_anim.PushBack({ 137, 0, 32, 32 });
	open_anim.PushBack({ 174, 0, 32, 32 });
	open_anim.PushBack({ 211, 0, 32, 32 });
	open_anim.PushBack({ 212, 36, 32, 32 });
	open_anim.loop = false;
	open_anim.speed = 0.05f;

	animation = &open_anim;

	lives = 24;
	points = 600;

	collider = App->collision->AddCollider({162, 1596, 32, 32 }, COLLIDER_DROPPING_ENEMY, (Module*)App->enemies);
}

void Enemy_Antiaircraft::Move()
{
	now2 = SDL_GetTicks() - start_time2;
	if (now2 > total_time2)
	{
		start_time2 = SDL_GetTicks();
		App->particles->AddParticle(App->particles->small_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 15, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 90);
		App->particles->AddParticle(App->particles->small_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 15, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 0);
		App->particles->AddParticle(App->particles->small_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 15, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 180);
		App->particles->AddParticle(App->particles->small_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 15, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 270);
	}
}

void Enemy_Antiaircraft::ExtraAnim()
{
	App->render->Blit(sprites, App->render->camera.x + position.x, App->render->camera.y + position.y, &(animation->GetCurrentFrame()));
	if (open_anim.Finished())
	{
		animation = &anim;
		animation->GetCurrentFrame();
	}
}
