#include "Enemy_Falling_Drone.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Faling_Drone::Enemy_Faling_Drone(int x, int y, int wave, int id) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/Falling drone.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;


	//Wave1
	dronewave.PushBack({ 12, 37, 38, 38 });
	dronewave.PushBack({ 59, 39, 38, 38 });
	dronewave.PushBack({ 107, 40, 38, 38 });
	dronewave.PushBack({ 164, 39, 38, 38 });
	dronewave.PushBack({ 56, 90, 38, 38 });
	dronewave.PushBack({ 108, 91, 38, 38 });
	dronewave.PushBack({ 164, 92, 38, 38 });
	dronewave.speed = 1.0f;
	dronewave.loop = true;



	//Wave1 Path

	if (wave == 1 && id == 1)
	{
		path.PushBack({ 0.0f, 0.2f }, 150, &dronewave);
		path.PushBack({ 1.0f, 0.0f }, 60, &dronewave); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 100, &dronewave);
		path.PushBack({ 0.5f, 1.5f }, 1000, &dronewave);

	}
	else if (wave == 1 && id == 2) {
		path.PushBack({ 0.0f, 0.2f }, 217, &dronewave);
		path.PushBack({ 1.0f, 0.0f }, 60, &dronewave);
		path.PushBack({ 0.0f, 0.2f }, 100, &dronewave);
		path.PushBack({ 0.5f, 1.5f }, 1000, &dronewave);
	}
	//Wave2 Path
	else if (wave == 2 && id == 1)
	{
		path.PushBack({ 0.0f, 0.0f }, 50, &dronewave);
		path.PushBack({ 0.0f, 2.0f }, 70, &dronewave); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 15, &dronewave);
		path.PushBack({ 0.0f, -2.0f }, 1000, &dronewave);
	}
	else if (wave == 2 && id == 2)
	{
		path.PushBack({ 0.0f, 0.0f }, 50, &dronewave);
		path.PushBack({ 0.0f, 0.0f }, 98, &dronewave);
		path.PushBack({ 0.0f, 2.0f }, 70, &dronewave); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 15, &dronewave);
		path.PushBack({ 0.0f, -2.0f }, 1000, &dronewave);
	}
	//Wave3 Path
	else if (wave == 3 && id == 1)
	{
		path.PushBack({ 0.0f, 0.0f }, 200, &dronewave);
		path.PushBack({ -1.0f, 0.0f }, 100, &dronewave); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.0f }, 100, &dronewave);
		path.PushBack({ -0.5f, 1.5f }, 1000, &dronewave);

	}
	else if (wave == 3 && id == 2) {
		path.PushBack({ 0.0f, 0.0f }, 300, &dronewave);
		path.PushBack({ -1.0f, 0.0f }, 100, &dronewave);
		path.PushBack({ 0.0f, 0.0f }, 100, &dronewave);
		path.PushBack({ -0.5f, 1.5f }, 1000, &dronewave);
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
	App->textures->Unload(NormalSprite);
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
