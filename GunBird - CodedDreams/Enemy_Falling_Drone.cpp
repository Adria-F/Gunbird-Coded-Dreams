#include "Enemy_Falling_Drone.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Faling_Drone::Enemy_Faling_Drone(int x, int y, int wave, int id) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Falling drone.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_Falling drone.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_Falling drone.png");

	//Idle

	idle.PushBack({ 33, 95, 45, 45 });
	idle.PushBack({ 31, 155, 45, 45 });
	idle.PushBack({ 88, 150, 45, 45 });
	idle.speed = 0.15f;

	//Move Right
	move_right.PushBack({ 312, 150, 45, 45 });
	move_right.PushBack({ 252, 150, 45, 45 });
	//move_right.PushBack({ 306, 95, 45, 45 });
	//move_right.PushBack({ 144, 150, 45, 45 });
	move_right.PushBack({ 195, 150, 45, 45 });
	//move_right.PushBack({ 108, 91, 45, 45 });
	//move_right.PushBack({ 164, 92, 45, 45 });
	move_right.speed = 0.1f;
	move_right.loop = false;

	//Right Idle
	right_idle.PushBack({ 306, 95, 45, 45 });
	right_idle.PushBack({ 142, 148, 45, 45 });
	right_idle.PushBack({ 193, 149, 45, 45 });

	right_idle.speed = 0.05f;
	right_idle.loop = true;

	//Move Left
	move_left.PushBack({ 33, 95, 45, 45 });
	move_left.PushBack({ 88, 95, 45, 45 });
	move_left.PushBack({ 247, 95, 45, 45 });
	
	move_left.speed = 0.1f;
	move_left.loop = false;

	//Left Idle
	left_idle.PushBack({ 190, 95, 45, 45 });
	left_idle.PushBack({ 247, 95, 45, 45 });
	//left_idle.PushBack({ 247, 95, 45, 45 });

	left_idle.speed = 0.05f;
	left_idle.loop = true;

	//Wave1 Path

	if (wave == 1 && id == 1)
	{
		path.PushBack({ 1.0f, 0.2f }, 75, &right_idle);
		path.PushBack({ 0.0f, 0.2f }, 25, &idle);
		path.PushBack({ 1.0f, 0.2f }, 25, &move_right);
		path.PushBack({ 0.0f, 0.2f }, 1000, &left_idle);//Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 25, &idle);
		path.PushBack({ -1.5f, 0.2f }, 25, &move_left);
		path.PushBack({ -1.5f, 0.2f }, 200, &left_idle);

	}
	else if (wave == 1 && id == 2) {
		path.PushBack({ 0.0f, 0.2f }, 217, &move_right);
		path.PushBack({ 1.0f, 0.0f }, 60, &move_right);
		path.PushBack({ 0.0f, 0.2f }, 100, &move_right);
		path.PushBack({ 0.5f, 1.5f }, 1000, &move_right);
	}
	//Wave2 Path
	else if (wave == 2 && id == 1)
	{
		path.PushBack({ 0.0f, 0.0f }, 50, &move_right);
		path.PushBack({ 0.0f, 2.0f }, 70, &move_right); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 15, &move_right);
		path.PushBack({ 0.0f, -2.0f }, 1000, &move_right);
	}
	else if (wave == 2 && id == 2)
	{
		path.PushBack({ 0.0f, 0.0f }, 50, &move_right);
		path.PushBack({ 0.0f, 0.0f }, 98, &move_right);
		path.PushBack({ 0.0f, 2.0f }, 70, &move_right); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 15, &move_right);
		path.PushBack({ 0.0f, -2.0f }, 1000, &move_right);
	}
	//Wave3 Path
	else if (wave == 3 && id == 1)
	{
		path.PushBack({ 0.0f, 0.0f }, 200, &move_right);
		path.PushBack({ -1.0f, 0.0f }, 100, &move_right); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.0f }, 100, &move_right);
		path.PushBack({ -0.5f, 1.5f }, 1000, &move_right);

	}
	else if (wave == 3 && id == 2) {
		path.PushBack({ 0.0f, 0.0f }, 300, &move_right);
		path.PushBack({ -1.0f, 0.0f }, 100, &move_right);
		path.PushBack({ 0.0f, 0.0f }, 100, &move_right);
		path.PushBack({ -0.5f, 1.5f }, 1000, &move_right);
	}

	//Set lives, initial_hp, points adn extra_anim
	lives = 5;
	initial_hp = lives;
	points = 500;
	extra_anim = false;

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 35, 35 }, COLLIDER_ENEMY, (Module*)App->enemies);
}

Enemy_Faling_Drone::~Enemy_Faling_Drone()
{
}

void Enemy_Faling_Drone::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}

void Enemy_Faling_Drone::ExtraAnim(SDL_Texture* texture)
{
	//Si l'enemic no te extra animation no cal posar aquesta funció ni aqui ni al header
}

void Enemy_Faling_Drone::DeadAnim()
{
	animation = &dead;
	position.y += 0.2f; //Perque es mogui a la mateixa velocitat que l'overlay
}
