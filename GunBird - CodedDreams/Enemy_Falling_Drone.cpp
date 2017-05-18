#include "Enemy_Falling_Drone.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleRender.h"


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

	//Rotate Right
	rotate_right.PushBack({ 312, 150, 45, 45 });
	rotate_right.PushBack({ 252, 150, 45, 45 });
	//move_right.PushBack({ 306, 95, 45, 45 });
	//move_right.PushBack({ 144, 150, 45, 45 });
	rotate_right.PushBack({ 195, 150, 45, 45 });
	//move_right.PushBack({ 108, 91, 45, 45 });
	//move_right.PushBack({ 164, 92, 45, 45 });
	rotate_right.speed = 0.5f;
	rotate_right.loop = false;

	//Going Right
	going_right.PushBack({ 306, 95, 45, 45 });
	going_right.PushBack({ 142, 148, 45, 45 });
	going_right.PushBack({ 193, 149, 45, 45 });

	going_right.speed = 0.05f;
	going_right.loop = true;

	//Restore Right

	center_from_right.PushBack({ 195, 150, 45, 45 });
	center_from_right.PushBack({ 252, 150, 45, 45 });
	center_from_right.PushBack({ 312, 150, 45, 45 });

	center_from_right.speed = 0.5f;
	center_from_right.loop = false;

	//Move Left
	rotate_left.PushBack({ 33, 95, 45, 45 });
	rotate_left.PushBack({ 88, 95, 45, 45 });
	rotate_left.PushBack({ 247, 95, 45, 45 });
	
	rotate_left.speed = 0.5f;
	rotate_left.loop = false;

	//Left Idle
	going_left.PushBack({ 190, 95, 45, 45 });
	going_left.PushBack({ 247, 95, 45, 45 });
	//left_idle.PushBack({ 247, 95, 45, 45 });

	going_left.speed = 0.05f;
	going_left.loop = true;

	//Restore Left

	center_from_left.PushBack({ 247, 95, 45, 45 });
	center_from_left.PushBack({ 88, 95, 45, 45 });
	center_from_left.PushBack({ 33, 95, 45, 45 });

	center_from_left.speed = 0.5f;
	center_from_left.loop = false;

	//Wave1 Path

	if (wave == 1 && id == 1)
	{
		path.PushBack({ 0.0f, 0.0f }, 200, &going_right);
		path.PushBack({ 1.0f, 0.2f }, 125, &going_right);
		path.PushBack({ 0.8f, 0.2f }, 25, &center_from_right);
		path.PushBack({ 0.6f, 0.2f }, 20, &rotate_left);
		path.PushBack({ 0.3f, 0.2f }, 20, &rotate_left);
		path.PushBack({ -0.7f, 0.2f }, 25, &going_left);
		path.PushBack({ -1.0f, 0.2f }, 50, &going_left);
		path.PushBack({ -0.7f, 0.2f }, 25, &center_from_left);//Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ -0.7f, 0.2f }, 25, &rotate_right);
		path.PushBack({ 1.0f, 0.5f }, 25, &going_right);
		path.PushBack({ 2.5f, 0.8f }, 1000, &going_right);

	}
	else if (wave == 1 && id == 2) {
		path.PushBack({ 0.0f, 0.0f }, 335, &going_right);
		path.PushBack({ 1.0f, 0.2f }, 125, &going_right);
		path.PushBack({ 0.8f, 0.2f }, 25, &center_from_right);
		path.PushBack({ 0.6f, 0.2f }, 20, &rotate_left);
		path.PushBack({ 0.3f, 0.2f }, 20, &rotate_left);
		path.PushBack({ -0.7f, 0.2f }, 25, &going_left);
		path.PushBack({ -1.0f, 0.2f }, 50, &going_left);
		path.PushBack({ -0.7f, 0.2f }, 25, &center_from_left);//Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ -0.7f, 0.2f }, 25, &rotate_right);
		path.PushBack({ 1.0f, 0.5f }, 25, &going_right);
		path.PushBack({ 2.5f, 0.8f }, 1000, &going_right);
	}
	//Wave2 Path
	else if (wave == 2 && id == 1)
	{
		path.PushBack({ 0.0f, 0.0f }, 200, &going_left);
		path.PushBack({ -1.0f, 0.2f }, 125, &going_left);
		path.PushBack({ -0.8f, 0.2f }, 25, &center_from_left);
		path.PushBack({ -0.6f, 0.2f }, 20, &rotate_right);
		path.PushBack({ -0.3f, 0.2f }, 20, &rotate_right);
		path.PushBack({ 0.7f, 0.2f }, 25, &going_right);
		path.PushBack({ 1.0f, 0.2f }, 50, &going_right);
		path.PushBack({ 0.7f, 0.2f }, 25, &center_from_right);//Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.7f, 0.2f }, 25, &rotate_left);
		path.PushBack({ -1.0f, 0.5f }, 25, &going_left);
		path.PushBack({ -2.5f, 0.8f }, 1000, &going_left);
	}
	else if (wave == 2 && id == 2)
	{
		path.PushBack({ 0.0f, 0.0f }, 335, &going_left);
		path.PushBack({ -1.0f, 0.2f }, 125, &going_left);
		path.PushBack({ -0.8f, 0.2f }, 25, &center_from_left);
		path.PushBack({ -0.6f, 0.2f }, 20, &rotate_right);
		path.PushBack({ -0.3f, 0.2f }, 20, &rotate_right);
		path.PushBack({ 0.7f, 0.2f }, 25, &going_right);
		path.PushBack({ 1.0f, 0.2f }, 50, &going_right);
		path.PushBack({ 0.7f, 0.2f }, 25, &center_from_right);//Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.7f, 0.2f }, 25, &rotate_left);
		path.PushBack({ -1.0f, 0.5f }, 25, &going_left);
		path.PushBack({ -2.5f, 0.8f }, 1000, &going_left);
	}

	//Set lives, initial_hp, points adn extra_anim
	lives = 5;
	initial_hp = lives;
	points = 500;
	extra_anim = false;
	explosion_type = SMALL1;

	//Shooting

	shoot = particle_type::P_BIG_SHOT;
	big_shoot = &App->particles->big_shot_particle;
	Shot_Start_time= (Uint32)(3333.3f);
	Shot_Total_time = (Uint32)(2000.0f);

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 40, 40 }, COLLIDER_AIR_ENEMY, (Module*)App->enemies);
}

Enemy_Faling_Drone::~Enemy_Faling_Drone()
{
}

void Enemy_Faling_Drone::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);

	Shot_now = SDL_GetTicks() - Shot_Start_time;
	if (animation == &rotate_right || animation == &rotate_left)
	{
		if (Shot_now > Shot_Total_time)
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 18, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 0);
		}
	}
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
