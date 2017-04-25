#include "Application.h"
#include "ModuleRender.h"
#include "Enemy_Humanoide_Robot.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleSceneCastle.h"
#include "ModuleTextures.h"
#include "Path.h"
#include "ModuleMarion.h"
#include "ModuleAsh.h"
#include <math.h>
#include "SDL/include/SDL_timer.h"

#define PI 3.14159265

Enemy_Humanoide_Robot::Enemy_Humanoide_Robot(int x, int y) : Enemy(x, y)
{
	sprites = App->textures->Load("assets/enemies/Humanoide_Robot.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_Humanoide_Robot.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_Humanoide_Robot.png");

	
	anim_rightBack.PushBack({ 257, 31, 76, 73 });//3
	anim_rightBack.PushBack({ 258, 132, 76, 73 });//7
	anim_rightBack.PushBack({ 46, 31, 76, 73 });//1
	anim_rightBack.speed = 0.15f;
	anim_rightBack.loop = false;

	rightLeg.PushBack({ 257, 31, 76, 73 });//3

	anim_leftBack.PushBack({ 154, 132, 76, 73 });//6
	anim_leftBack.PushBack({ 46, 31, 76, 73 });//1
	anim_leftBack.PushBack({ 258, 132, 76, 73 });//7
	anim_leftBack.speed = 0.15f;
	anim_leftBack.loop = false;

	dead_robot.PushBack({ 262, 363, 62, 54 });
	dead_robot.speed = 0.1f;
	dead_robot.loop = false;

	sprint.PushBack({ 154, 132, 76, 73 });//6
	sprint.PushBack({ 46, 31, 76, 73 });//1
	sprint.PushBack({ 258, 132, 76, 73 });//7
	sprint.PushBack({ 257, 31, 76, 73 });//3
	sprint.PushBack({ 257, 31, 76, 73 });//3
	sprint.PushBack({ 257, 31, 76, 73 });//3
	sprint.PushBack({ 257, 31, 76, 73 });//3
	sprint.PushBack({ 257, 31, 76, 73 });//3
	sprint.PushBack({ 258, 132, 76, 73 });//7
	sprint.PushBack({ 46, 31, 76, 73 });//1
	sprint.PushBack({ 154, 132, 76, 73 });//6
	sprint.PushBack({ 154, 132, 76, 73 });//6
	sprint.PushBack({ 154, 132, 76, 73 });//6
	sprint.PushBack({ 154, 132, 76, 73 });//6
	sprint.speed = 0.30f;

	leftLeg.PushBack({ 154, 132, 76, 73 });//6

	path.PushBack({ 0.0f, 0.0f }, 200, &rightLeg); //right leg in front
	path.PushBack({ 0.0f, -0.65f }, 18, &anim_rightBack); //move right leg to the back
	path.PushBack({ 0.0f, 0.0f }, 200, &leftLeg); //left leg in front
	path.PushBack({ 0.0f, -0.65f }, 18, &anim_leftBack); //move left leg to the back
	path.PushBack({ 0.0f, 0.0f }, 200, &rightLeg);
	path.PushBack({ 0.0f, -0.65f }, 18, &anim_rightBack);
	path.PushBack({ 0.0f, 0.0f }, 200, &leftLeg);
	path.PushBack({ 0.0f, -0.65f }, 225, &sprint);
	path.PushBack({ 0.0f, 0.0f }, 200, &leftLeg); //left leg in front
	path.PushBack({ 0.0f, 0.65f }, 18, &anim_leftBack); //move left leg to the back
	path.PushBack({ 0.0f, 0.0f }, 200, &rightLeg); //right leg in front
	path.PushBack({ 0.0f, -0.65f }, 18, &anim_rightBack); //move right leg to the back
	path.PushBack({ 0.0f, 0.0f }, 200, &leftLeg); //left leg in front
	path.PushBack({ 0.0f, 0.65f }, 18, &anim_leftBack); //move left leg to the back
	path.PushBack({ 0.0f, 0.0f }, 200, &rightLeg); //right leg in front
	path.PushBack({ 0.0f, -0.65f }, 18, &anim_rightBack); //move right leg to the back

	extra_anim = true;
	angles[0] = { 134, 242, 18, 16 }; // 0
	angles[1] = { 157, 242, 17, 16 }; // 30
	angles[2] = { 179, 242, 16, 16 }; // 45
	angles[3] = { 203, 241, 16, 17 }; // 60
	angles[4] = { 226, 240, 16, 18 }; // 90
	angles[5] = { 247, 241, 16, 17 }; // 120
	angles[6] = { 269, 242, 16, 16 }; // 135
	angles[7] = { 292, 242, 17, 16 }; // 150
	angles[8] = { 316, 242, 18, 16 }; // 180
	angles[9] = { 339, 242, 17, 16 }; // 210
	angles[10] = { 362, 242, 16, 16 }; // 225
	angles[11] = { 386, 242, 16, 17 }; // 240
	angles[12] = { 51, 242, 16, 18 }; // 270
	angles[13] = { 71, 242, 16, 17 }; // 300
	angles[14] = { 91, 242, 16, 16 }; // 315
	angles[15] = { 113, 242, 17, 16 }; // 330

	cannon_pos[0].x = 12;
	cannon_pos[0].y = 15;
	cannon_pos[1].x = 48;
	cannon_pos[1].y = 15;

	lives = 88;
	points = 4000;

	collider = App->collision->AddCollider({ 150, 1505, 75, 50 }, COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

Enemy_Humanoide_Robot::~Enemy_Humanoide_Robot()
{

}

void Enemy_Humanoide_Robot::Move()
{
	vector.x = (App->marion->position.x - (App->render->camera.x + position.x));
	vector.y = (App->marion->position.y - (App->render->camera.y + position.y));
	distance[0] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
	vector.x = (App->ash->position.x - (App->render->camera.x + position.x));
	vector.y = (App->ash->position.y - (App->render->camera.y + position.y));
	distance[1] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
	if (distance[0] < distance[1])
		player = App->marion;
	else
		player = App->ash;
	
	position = original_pos + path.GetCurrentPosition(&animation);

	now = SDL_GetTicks() - start_time;

		if (now > total_time && player->position.y -64 > this->collider->rect.y + 50 && second_shot == false)
	{		
		second_shot = true;
		App->particles->AddParticle(App->particles->small_shot_particle, P_SMALL_SHOT, App->render->camera.x + position.x + 15, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, -22);
		App->particles->AddParticle(App->particles->small_shot_particle, P_SMALL_SHOT, App->render->camera.x + position.x + 53, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 22);
	}
	if (now > total_time + 150 && player->position.y - 64 > this->collider->rect.y + 50)
	{
		start_time = SDL_GetTicks();
		second_shot = false;
		App->particles->AddParticle(App->particles->small_shot_particle, P_SMALL_SHOT, App->render->camera.x + position.x + 15, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, -22);
		App->particles->AddParticle(App->particles->small_shot_particle, P_SMALL_SHOT, App->render->camera.x + position.x + 53, App->render->camera.y + position.y + 10, COLLIDER_ENEMY_SHOT, 0, 22);
	}

}

void Enemy_Humanoide_Robot::ExtraAnim()
{	
	for (int i = 0; i < 2; i++)
	{
		vector.x = (player->position.x - (App->render->camera.x + position.x + cannon_pos[i].x));
		vector.y = (player->position.y - (App->render->camera.y + position.y + cannon_pos[i].y));
		angle = atan(vector.x / vector.y) * 180 / PI;
		if (vector.y > 0) angle = 360 - 90 + angle;
		else angle = 90 + angle;
		if (angle >= 0 && angle < 30)
		{
			App->render->Blit(sprites, App->render->camera.x + position.x + cannon_pos[i].x, App->render->camera.y + position.y + cannon_pos[i].y, &angles[0]);
		}
		else
		{
			App->render->Blit(sprites, (App->render->camera.x + position.x + cannon_pos[i].x), (App->render->camera.y + position.y + cannon_pos[i].y) - ((vector.y < 0) ? (angles[angle / 30 + (angle / 100) + 1].h - 16) : 0), &angles[angle / 30 + (angle / 100) + 1]);
		}
	}
}

void Enemy_Humanoide_Robot::DeadAnim()
{

	animation = &dead_robot;
	if (killed == 0)
	{
		position.y = position.y + 25;
		position.x = position.x + 7;
		killed = 1;
	}
	collider->to_delete = true;
}
