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
	//ja ho calcularás tu, norman!
	if (App->render->camera.y >= -1590)
	{
		now = SDL_GetTicks() - start_time;
		if (now > total_time  && shot_sequ == 0)
		{
			start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 45);
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 135);
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 225);
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 315);
			++shot_sequ;
		}
		else if (now > total_time + 200 && shot_sequ == 1)
		{
			start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 45 + 30);
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 135 + 30);
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 225 + 30);
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 315 + 30);

			++shot_sequ;
		}

		else if (now > total_time + 200 && shot_sequ == 2)
		{
			start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 45 + 60);
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 135 + 60);
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 225 + 30);
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 315 + 60);


			++shot_sequ;
		}
		else if (now > total_time + 200 && shot_sequ == 3)
		{
			start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->big_shot_particle, P_BIG_SHOT, App->render->camera.x + position.x + 10, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 45 + 90);


			shot_sequ = 0;
		}
	}
}

void Enemy_Antiaircraft::ExtraAnim()
{
	if (App->render->camera.y >= -1590)
	{
		App->render->Blit(sprites, App->render->camera.x + position.x, App->render->camera.y + position.y, &(animation->GetCurrentFrame()));
		if (open_anim.Finished())
		{
			animation = &anim;
			animation->GetCurrentFrame();
		}
	}
	
}
