#include "Enemy_Drone.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleRender.h"

Enemy_Drone::Enemy_Drone(int x, int y, int wave, int id) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/drone.png");
	RedSprite = App->textures->Load("assets/enemies/hitten/hitten_red_drone.png");
	WhiteSprite = App->textures->Load("assets/enemies/hitten/hitten_white_drone.png");
	

	//Looking Down
	Looking_down.PushBack({ 14, 4, 35, 35 });
	Looking_down.PushBack({ 52, 4, 35, 35 });
	Looking_down.PushBack({ 91, 4, 35, 35 });
	Looking_down.PushBack({ 128, 4, 35, 35 });
	Looking_down.PushBack({ 166, 4, 35, 35 });
	Looking_down.PushBack({ 203, 4, 35, 35 });
	Looking_down.speed = 1.0f;
	Looking_down.loop = true;

	//Looking Right
	Looking_right.PushBack({ 14, 40, 35, 35 });
	Looking_right.PushBack({ 52, 40, 35, 35 });
	Looking_right.PushBack({ 91, 40, 35, 35 });
	Looking_right.PushBack({ 128, 40, 35, 35 });
	Looking_right.PushBack({ 166, 40, 35, 35 });
	Looking_right.PushBack({ 203, 40, 35, 35 });
	
	Looking_right.speed = 1.0f;
	Looking_right.loop = true;


	//Totally_right
	Totally_right.PushBack({ 14, 86, 35, 35 });
	Totally_right.PushBack({ 52, 86, 35, 35 });
	Totally_right.PushBack({ 91, 86, 35, 35 });
	Totally_right.PushBack({ 128, 86, 35, 35 });
	Totally_right.PushBack({ 166, 86, 35, 35 });
	Totally_right.PushBack({ 203, 86, 35, 35 });

	Totally_right.speed = 1.0f;
	Totally_right.loop = true;

	//Looking_left 
	Looking_left.PushBack({ 14, 126, 35, 35 });
	Looking_left.PushBack({ 52, 126, 35, 35 });
	Looking_left.PushBack({ 91, 126, 35, 35 });
	Looking_left.PushBack({ 128, 126, 35, 35 });
	Looking_left.PushBack({ 166, 126, 35, 35 });
	Looking_left.PushBack({ 203, 126, 35, 35 });

	Looking_left.speed = 1.0f;
	Looking_left.loop = true;


	//Totally_right
	Totally_right.PushBack({ 14, 86, 35, 35 });
	Totally_right.PushBack({ 52, 86, 35, 35 });
	Totally_right.PushBack({ 91, 86, 35, 35 });
	Totally_right.PushBack({ 128, 86, 35, 35 });
	Totally_right.PushBack({ 166, 86, 35, 35 });
	Totally_right.PushBack({ 203, 86, 35, 35 });

	Totally_right.speed = 1.0f;
	Totally_right.loop = true;

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
		path.PushBack({ 0.0f, 0.2f }, 150, &Looking_down);
		path.PushBack({ 1.0f, 0.0f }, 60, &Looking_down); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 50, &Looking_down);
		path.PushBack({ 0.0f, 0.2f }, 50, &Looking_right);
		path.PushBack({ 0.5f, 1.5f }, 70, &Looking_right);
		path.PushBack({ 0.5f, 1.5f }, 1000, &Totally_right);
	
	}
	else if (wave==1 && id == 2) {
		path.PushBack({ 0.0f, 0.2f }, 217, &Looking_down);
		path.PushBack({ 1.0f, 0.0f }, 60, &Looking_down);
		path.PushBack({ 0.0f, 0.2f }, 50, &Looking_down);
		path.PushBack({ 0.0f, 0.2f }, 50, &Looking_right);
		path.PushBack({ 0.5f, 1.5f }, 1000, &Looking_right);
	}
	//Wave2 Path
	else if (wave == 2 && id==1)
	{
		path.PushBack({ 0.0f, 0.0f }, 50, &Looking_down);
		path.PushBack({ 0.0f, 2.0f }, 30, &Looking_down);
		path.PushBack({ 0.0f, 2.0f }, 40, &Looking_left); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 15, &Looking_left);
		path.PushBack({ 0.0f, -2.0f }, 1000, &Looking_left);
	}
	else if (wave == 2 && id == 2)
	{
		path.PushBack({ 0.0f, 0.0f }, 50, &Looking_down);
		path.PushBack({ 0.0f, 0.0f }, 98, &Looking_down);
		path.PushBack({ 0.0f, 2.0f }, 30, &Looking_down);
		path.PushBack({ 0.0f, 2.0f }, 40, &Looking_left); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 15, &Looking_left);
		path.PushBack({ 0.0f, -2.0f }, 1000, &Looking_left);
	}
	//Wave3 Path
	else if (wave == 3 && id == 1)
	{
		path.PushBack({ 0.0f, 0.0f }, 200, &Looking_down);
		path.PushBack({ -1.0f, 0.0f }, 100, &Looking_down); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 50, &Looking_down);
		path.PushBack({ 0.0f, 0.2f }, 50, &Looking_left);
		path.PushBack({ -0.5f, 1.5f }, 70, &Looking_left);
		path.PushBack({ -0.5f, 1.5f }, 1000, &Looking_down);

	}
	else if (wave == 3 && id == 2) {
		path.PushBack({ 0.0f, 0.0f }, 300, &Looking_down);
		path.PushBack({ -1.0f, 0.0f }, 100, &Looking_down);
		path.PushBack({ 0.0f, 0.2f }, 50, &Looking_down);
		path.PushBack({ 0.0f, 0.2f }, 50, &Looking_left);
		path.PushBack({ -0.5f, 1.5f }, 70, &Looking_left);
		path.PushBack({ -0.5f, 1.5f }, 1000, &Looking_down);
	}
	//Wave4 Path
	else if (wave == 4 && id == 1)
	{
		path.PushBack({ 0.0f, 0.0f }, 50, &Looking_down);
		path.PushBack({ 0.0f, 2.0f }, 30, &Looking_down);
		path.PushBack({ 0.0f, 2.0f }, 40, &Looking_right); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 15, &Looking_right);
		path.PushBack({ 0.0f, -2.0f }, 1000, &Looking_right);
	}
	else if (wave == 4 && id == 2)
	{
		path.PushBack({ 0.0f, 0.0f }, 50, &Looking_down);
		path.PushBack({ 0.0f, 0.0f }, 98, &Looking_down);
		path.PushBack({ 0.0f, 2.0f }, 30, &Looking_down);
		path.PushBack({ 0.0f, 2.0f }, 40, &Looking_right); //Si esta quiet en un punt ha de tenir velocitat y = 0.2 per moures a la mateixa velocitat que l'overlay
		path.PushBack({ 0.0f, 0.2f }, 15, &Looking_right);
		path.PushBack({ 0.0f, -2.0f }, 1000, &Looking_right);
	}

	//Set lives, initial_hp, points adn extra_anim
	lives = 2;
	initial_hp = lives;
	points = 500;
	extra_anim = false;
	explosion_type = SMALL1;

	//Shooting

	shoot = particle_type::P_BIG_SHOT;
	big_shoot = &App->particles->big_shot_particle;
	Shot_Start_time = (Uint32)(3333.3f);
	Shot_Total_time = (Uint32)(2000.0f);

	//Add and save collider
	collider = App->collision->AddCollider({ x, y, 35, 35 }, COLLIDER_AIR_ENEMY, (Module*)App->enemies);
}

Enemy_Drone::~Enemy_Drone()
{
}

void Enemy_Drone::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);

	Shot_now = SDL_GetTicks() - Shot_Start_time;
	if (animation == &Looking_right || animation == &Looking_left)
	{
		if (Shot_now > Shot_Total_time)
		{
			Shot_Start_time = SDL_GetTicks();
			App->particles->AddParticle(App->particles->small_shot_particle, particle_type::P_SMALL_SHOT, position.x + 18, position.y + App->render->camera.y + 40, COLLIDER_ENEMY_SHOT, 0, 0);
		}
	}
}


