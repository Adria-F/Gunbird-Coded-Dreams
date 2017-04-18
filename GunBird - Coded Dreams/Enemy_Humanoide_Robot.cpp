#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Humanoide_Robot.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"
#include "Path.h"
#include "ModulePlayer.h"
#include <math.h>
#include "SDL/include/SDL_timer.h"

Enemy_Humanoide_Robot::Enemy_Humanoide_Robot(int x, int y) : Enemy(x, y)
{
	sprites = App->textures->Load("assets/enemies/Humanoide_Robot.png");

	anim.PushBack({ 152, 29, 75, 72 });//2
	anim.PushBack({ 259, 132, 76, 71 });//7
	anim.PushBack({ 258, 31, 75, 72 });//3
	anim.PushBack({ 152, 29, 75, 72 });//2
	anim.PushBack({ 46, 31, 75, 72 });//1
	anim.PushBack({ 154, 133, 76, 72 });//6
	anim.speed = 0.1f;
	path.PushBack({ 0.0f, -0.25f }, 100);

	lives = 88;
/*
	if (position.y >= 1370)//intent de que tiri endavant
	{
		path.PushBack({ 0.0f, -0.25f }, 100);
	}
	else if (position.y <= 1370)
	{
		path.PushBack({ 0.0f, 0.25f }, 20);
	}
	*/
	
	animation = &anim;

	collider = App->collision->AddCollider({ 70, 1505, 77, 77 }, COLLIDER_ENEMY, (Module*)App->enemies);

	
	
	//collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

Enemy_Humanoide_Robot::~Enemy_Humanoide_Robot()
{

}

void Enemy_Humanoide_Robot::Move()
{
	if (position.y >= 1370)
	{
		position = original_pos + path.GetCurrentPosition();
	}

	now = SDL_GetTicks() - start_time;

	if (now > total_time)
	{
		start_time = SDL_GetTicks();
		//App->particles->AddParticle(App->particles->small_shot, P_SMALL_SHOT, App->player->position.x, App->player->position.y, COLLIDER_ENEMY_SHOT);
		shots[0] = App->particles->AddParticle(App->particles->small_shot, P_SMALL_SHOT, App->render->camera.x + position.x + 15, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT);
		vector = (App->player->position.x + 15 - position.x - 37);
		vector /= 30;
		shots[0]->speed.x = vector;
		shots[0]->speed.y = sqrt(pow(3.5, 2.0) - pow(vector, 2.0));
		shots[1] = App->particles->AddParticle(App->particles->small_shot, P_SMALL_SHOT, App->render->camera.x + position.x + 53, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT);
		vector = (App->player->position.x + 50 - position.x - 37);
		vector /= 30;
		shots[1]->speed.x = vector;
		shots[1]->speed.y = sqrt(pow(3.5, 2.0) - pow(vector, 2.0));
	}

}