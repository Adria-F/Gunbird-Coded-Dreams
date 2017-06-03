#include "Enemy_Antiaircraft_right.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

Enemy_Antiaircraft_right::Enemy_Antiaircraft_right(int x, int y, int id): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_antiaircraft.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop

	//right Pushbacks
	
	right_closed.PushBack({ 0, 292, 67, 53 });
	right_closed.PushBack({ 70, 292, 67, 53 });
	right_closed.PushBack({ 140, 292, 67, 53 });
	right_closed.PushBack({ 210, 292, 67, 53 });
	right_closed.speed = 0.2f;
	right_closed.loop = true;

	right_opening.PushBack({ 0, 349, 67, 53 });
	right_opening.PushBack({ 70, 349, 67, 53 });
	right_opening.PushBack({ 140, 349, 67, 54 });
	right_opening.PushBack({ 210, 349, 67, 54 });
	right_opening.PushBack({ 280, 349, 67, 55 });
	right_opening.PushBack({ 350, 349, 67, 55 });
	right_opening.speed = 0.2f;
	right_opening.loop = false;

	right_idle.PushBack({ 0, 406, 67, 55 });
	right_idle.PushBack({ 70, 406, 67, 55 });
	right_idle.PushBack({ 140, 406, 67, 55 });
	right_idle.PushBack({ 210, 406, 67, 55 });
	right_idle.speed = 0.2f;
	right_idle.loop = true;

	//right death animation
	right_death.PushBack({ 6, 463, 61, 46 });
	right_death.PushBack({ 76, 463, 61, 46 });
	right_death.PushBack({ 146, 463, 61, 46 });
	right_death.PushBack({ 216, 463, 61, 46 });
	right_death.PushBack({ 286, 463, 61, 46 });
	right_death.PushBack({ 356, 463, 61, 46 });

	right_death.PushBack({ 6, 520, 61, 46 });
	right_death.PushBack({ 76, 520, 61, 46 });
	right_death.speed = 0.2f;
	right_death.loop = true;
	

		
	//Set path
	path.PushBack({ 0.0f, 0.09f }, 670, &right_closed); //wait
	path.PushBack({ 0.0f, -0.9f }, 300, &right_closed); //go to the top
	path.PushBack({ 0.0f, -0.3f }, 475, &right_closed); //hold position
	path.PushBack({ 0.0f, 0.18f }, 155, &right_closed); //extend
	path.PushBack({ 0.0f, -0.3f }, 40, &right_opening); //opening
	path.PushBack({ 0.0f, -0.6f }, 55, &right_idle); //go top
	path.PushBack({ 0.0f, -0.3f }, 200, &right_idle); //hold position
	path.PushBack({ 0.0f, 0.11f }, 75, &right_idle); //go bottom
	path.PushBack({ 0.0f, -0.3f }, 200, &right_idle); //hold position
	path.PushBack({ 0.0f, -0.7f }, 75, &right_idle); //go top
	path.PushBack({ 0.0f, -0.3f }, 200, &right_idle); //hold position
	path.PushBack({ 0.0f, 0.11f }, 75, &right_idle); //go bottom
	path.PushBack({ 0.0f, -0.3f }, 200, &right_idle); //hold position
	path.PushBack({ 0.0f, -0.7f }, 75, &right_idle); //go top
	path.PushBack({ 0.0f, -0.3f }, 200, &right_idle); //hold position
	path.PushBack({ 0.0f, 0.11f }, 75, &right_idle); //go bottom
	path.PushBack({ 0.0f, -0.3f }, 200, &right_idle); //hold position
	path.PushBack({ 0.0f, -0.7f }, 75, &right_idle); //go top
	path.PushBack({ 0.0f, -0.3f }, 200, &right_idle); //hold position
	path.PushBack({ 0.0f, 0.11f }, 75, &right_idle); //go bottom
	path.PushBack({ 0.0f, -0.3f }, 200, &right_idle); //hold position
	path.PushBack({ 0.0f, -0.7f }, 75, &right_idle); //go top
	path.PushBack({ 0.0f, -0.3f }, 200, &right_idle); //hold position
	path.PushBack({ 0.0f, 0.11f }, 75, &right_idle); //go bottom			



	//Set lives, initial_hp, points adn extra_anim
	lives = 25;
	initial_hp = lives;
	extra_anim = false;
	lower_level = true;
	explosion_type = MID1;
	Shot_Total_time = (Uint32)(4000.0f);
	Shot_Total_time1 = (Uint32)(200.0f);
	collider = NULL;
}

Enemy_Antiaircraft_right::~Enemy_Antiaircraft_right()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Antiaircraft_right::Move()
{
	if (App->render->camera.y <= -1300) //-1839
	{
		position = original_pos + path.GetCurrentPosition(&animation);
	}
	else
	{
		lives = 0;
	}
	if (right_idle.GetCurrentFrameNum() == 2 && collider_state == 0)
	{
		collider = App->collision->AddCollider({ (int)position.x, (int)position.y, 67, 55 }, COLLIDER_ENEMY, (Module*)App->enemies);
		collider_state = 1;
	}
	if (App->render->camera.y >= -1839) //-1839
	{
			Shot_now = SDL_GetTicks() - Shot_Start_time;
			if (Shot_now > Shot_Total_time1)
			{
				Shot_now = SDL_GetTicks() - Shot_Start_time;
				if (state == 2)
				{
					state = 0;
				}
				if (Shot_now > Shot_Total_time && state == 1)
				{
					Shot_Start_time = SDL_GetTicks();
					App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 28, position.y + App->render->camera.y + 22, COLLIDER_ENEMY_SHOT, 0, 0, PLAYER);
					state = 2;
				}
				if (Shot_now > Shot_Total_time && state == 0)
				{
					Shot_Start_time = SDL_GetTicks();
					App->particles->AddParticle(App->particles->big_shot_particle, particle_type::P_BIG_SHOT, position.x + 28, position.y + App->render->camera.y + 22, COLLIDER_ENEMY_SHOT, 0, 0, PLAYER);
					state = 1;
				}
			}		
	}
}

void Enemy_Antiaircraft_right::DeadAnim()
{
	animation = &right_death;
	if (App->render->camera.y <= -1300) //-1839
	{
		position.y += -0.3f; //Perque es mogui a la mateixa velocitat que l'overlay
	}
	
}