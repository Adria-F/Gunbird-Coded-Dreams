#include "Enemy_General_Turret.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleSceneMine.h"
#include "p2Point.h"

#define PI 3.14159265

Enemy_General_Turret::Enemy_General_Turret(int x, int y) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/General_Turret.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_General_Turret.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_General_Turret.png");;

	//Set animation steps, speed and loop
	idle.PushBack({ 1, 235, 28, 35 });
	idle.PushBack({ 30, 235, 28, 35 });
	idle.PushBack({ 59, 235, 28, 35 });
	idle.PushBack({ 88, 235, 28, 35 });
	idle.PushBack({ 1, 271, 28, 35 });
	idle.PushBack({ 30, 271, 28, 35 });
	idle.PushBack({ 59, 271, 28, 35 });
	idle.PushBack({ 88, 271, 28, 35 });
	idle.PushBack({ 1, 307, 28, 35 });
	idle.PushBack({ 30, 307, 28, 35 });
	idle.PushBack({ 59, 307, 28, 35 });
	idle.PushBack({ 88, 307, 28, 35 });
	idle.speed = 0.07f;
	idle.loop = true;

	dead.PushBack({ 11, 156, 32, 33 });
	dead.PushBack({ 44, 156, 32, 33 });
	dead.PushBack({ 77, 156, 32, 33 });
	dead.PushBack({ 138, 156, 32, 33 });
	dead.PushBack({ 171, 156, 32, 33 });
	dead.PushBack({ 204, 156, 32, 33 });
	dead.PushBack({ 139, 190, 32, 33 });
	dead.PushBack({ 172, 190, 32, 33 });
	dead.speed = 0.1f;
	dead.loop = true;

	//Set path
	path.PushBack({ 0.0f, 0.09f }, 100, &idle); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay

	extra_anim = true;
	int i = 0;
	//All angles rect definition
	{
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
		angles[i++] = { 0, 0, 0, 0 };
	}
	
	//Set lives, initial_hp, points adn extra_anim
	lives = 12;
	initial_hp = lives;
	points = 400;
	explosion_type = BIG1; //Explosion type

	original_pos = position;

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 28, 35 }, COLLIDER_ENEMY, (Module*)App->enemies);
}

Enemy_General_Turret::~Enemy_General_Turret()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_General_Turret::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}

void Enemy_General_Turret::ExtraAnim(SDL_Texture* texture)
{
	vector.x = (App->player1->position.x - (App->render->camera.x + position.x));
	vector.y = (App->player1->position.y - (App->render->camera.y + position.y));
	distance[0] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
	vector.x = (App->player2->position.x - (App->render->camera.x + position.x));
	vector.y = (App->player2->position.y - (App->render->camera.y + position.y));
	distance[1] = sqrt(pow(vector.x, 2.0) + pow(vector.y, 2.0));
	if (distance[0] < distance[1])
		player = App->player1;
	else
		player = App->player2;
	//---------------------------------------------------------------------------------------
	for (int i = 0; i < 2; i++)
	{
		vector.x = (player->position.x - (App->render->camera.x + position.x + cannon_pos[i].x));
		vector.y = (player->position.y - (App->render->camera.y + position.y + cannon_pos[i].y));
		angle = atan(vector.x / vector.y) * 180 / PI;
		if (vector.y > 0) angle = 360 - 90 + angle;
		else angle = 90 + angle;
		
		if (angle >= 0 && angle < 30)
		{
			App->render->Blit(texture, App->render->camera.x + position.x + cannon_pos[i].x, App->render->camera.y + position.y + cannon_pos[i].y, &angles[0]);
		}
		else
		{
			App->render->Blit(texture, (App->render->camera.x + position.x + cannon_pos[i].x), (App->render->camera.y + position.y + cannon_pos[i].y) - ((vector.y < 0) ? (angles[angle / 30 + (angle / 100) + 1].h - 16) : 0), &angles[(int)((float)angle / 11.25f)]);
		}
	}
}

void Enemy_General_Turret::DeadAnim()
{
	animation = &dead;
	position.y += 0.09f; //Perque es mogui a la mateixa velocitat que l'overlay
}