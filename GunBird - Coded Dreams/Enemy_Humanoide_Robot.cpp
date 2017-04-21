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

	//3
	//7
	//1
	//6
	//1
	//2
	//3
	//4
	//5
	
	anim.PushBack({ 152, 29, 75, 72 });//2
	anim.PushBack({ 259, 132, 76, 71 });//7
	anim.PushBack({ 258, 31, 75, 72 });//3
	anim.PushBack({ 152, 29, 75, 72 });//2
	anim.PushBack({ 46, 31, 75, 72 });//1
	anim.PushBack({ 154, 133, 76, 72 });//6
	anim.speed = 0.1f;
	path.PushBack({ 0.0f, -0.25f }, 100);

	lives = 88;

	animation = &anim;

	collider = App->collision->AddCollider({ 150, 1505, 75, 50 }, COLLIDER_ENEMY, (Module*)App->enemies);

	

	original_pos.x = x;
	original_pos.y = y;
}

Enemy_Humanoide_Robot::~Enemy_Humanoide_Robot()
{

}

void Enemy_Humanoide_Robot::Move()
{
	move_now = SDL_GetTicks() - move_start_time;
	/*step*/if (position.y >= 1370 && move_now > move_total_time)
	{
		move_start_time = SDL_GetTicks();
		position = original_pos + path.GetCurrentPosition();
	}

	
	
	now = SDL_GetTicks() - start_time;

	if (now > total_time && App->player->position.y -64 > this->collider->rect.y + 50 && second_shot == false)
	{		
		second_shot = true;
		App->particles->AddParticle(App->particles->small_shot_particle, P_SMALL_SHOT, App->render->camera.x + position.x + 15, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, -22);
		App->particles->AddParticle(App->particles->small_shot_particle, P_SMALL_SHOT, App->render->camera.x + position.x + 53, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 22);
	}
	if (now > total_time + 150 && App->player->position.y - 64 > this->collider->rect.y + 50)
	{
		start_time = SDL_GetTicks();
		second_shot = false;
		App->particles->AddParticle(App->particles->small_shot_particle, P_SMALL_SHOT, App->render->camera.x + position.x + 15, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, -22);
		App->particles->AddParticle(App->particles->small_shot_particle, P_SMALL_SHOT, App->render->camera.x + position.x + 53, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 22);
	}

}