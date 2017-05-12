#include "Enemy_Drone.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Drone::Enemy_Drone(int x, int y, int wave, int id) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/drone.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_drone.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_drone.png");
	

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

	//Death
	//Chavales es la medium explosion sencera, si algu la vol aqui esta guapas

	dead.PushBack({ 10, 131, 69, 69 });
	dead.PushBack({ 82, 131, 69, 69 });
	dead.PushBack({ 152, 131, 69, 69 });
	dead.PushBack({ 228, 131, 69, 69 });
	dead.PushBack({ 303, 131, 69, 69 });
	dead.PushBack({ 16, 215, 68, 68 });
	dead.PushBack({ 82, 215, 68, 68 });
	dead.PushBack({ 152, 215, 68, 68 });
	dead.PushBack({ 228, 215, 68, 68 });
	dead.PushBack({ 303, 215, 68, 68 });
	dead.PushBack({ 82, 313, 68, 68 });
	dead.PushBack({ 152, 313, 68, 68 });
	dead.PushBack({ 228, 313, 68, 68 });
	dead.PushBack({ 303, 313, 68, 68 });

	dead.speed = 0.5f;
	dead.loop = false;

	//Wave1 Path

	if (wave == 1 && id==1)
	{
		path.PushBack({ 0.0f, 0.2f }, 150, &dronewave);
		path.PushBack({ 1.0f, 0.0f }, 60, &dronewave); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 100, &dronewave);
		path.PushBack({ 0.5f, 1.5f }, 1000, &dronewave);
	
	}
	else if (wave==1 && id == 2) {
		path.PushBack({ 0.0f, 0.2f }, 217, &dronewave);
		path.PushBack({ 1.0f, 0.0f }, 60, &dronewave);
		path.PushBack({ 0.0f, 0.2f }, 100, &dronewave);
		path.PushBack({ 0.5f, 1.5f }, 1000, &dronewave);
	}
	//Wave2 Path
	else if (wave == 2 && id==1)
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
	lives = 2;
	initial_hp = lives;
	points = 500;
	extra_anim = false;
	explosion_type = SMALL1;


	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 35, 35 }, COLLIDER_ENEMY, (Module*)App->enemies);
}

Enemy_Drone::~Enemy_Drone()
{
}

void Enemy_Drone::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}


