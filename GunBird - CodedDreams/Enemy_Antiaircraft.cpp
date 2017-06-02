#include "Enemy_Antiaircraft.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"

Enemy_Antiaircraft::Enemy_Antiaircraft(int x, int y, int id): Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/enemies/first boss/B1_antiaircraft.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;

	//Set animation steps, speed and loop
	if (id == 1)
	{
		//left Pushbacks
		{
			left_closed.PushBack({ 1, 1, 58, 53 });
			left_closed.PushBack({ 71, 1, 58, 53 });
			left_closed.PushBack({ 211, 1, 58, 53 });
			left_closed.speed = 0.02f;
			left_closed.loop = true;

			left_opening.PushBack({ 1, 1, 59, 53 });
			left_opening.PushBack({ 71, 58, 59, 53 });
			left_opening.PushBack({ 141, 58, 61, 54 });
			left_opening.PushBack({ 211, 58, 61, 54 });
			left_opening.PushBack({ 281, 58, 66, 54 });
			left_opening.PushBack({ 351, 58, 67, 55 });
			left_opening.speed = 0.2f;
			left_opening.loop = false;

			left_idle.PushBack({ 1, 115, 67, 55 });
			left_idle.PushBack({ 71, 115, 67, 55 });
			left_idle.PushBack({ 141, 115, 67, 55 });
			left_idle.PushBack({ 211, 115, 67, 55 });
			left_idle.speed = 0.2f;
			left_idle.loop = true;
		}

		//path
		{
			//Set path
			path.PushBack({ 0.0f, 0.09f }, 670, &left_closed); //wait
			path.PushBack({ 0.0f, -0.9f }, 300, &left_closed); //go to the top
			path.PushBack({ 0.0f, -0.3f }, 475, &left_closed); //hold position
			path.PushBack({ 0.0f, 0.18f }, 140, &left_closed); //extend
			path.PushBack({ 0.0f, -0.3f }, 40, &left_opening); //opening
			path.PushBack({ 0.0f, 0.09f }, 55, &left_idle); //go bottom
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, -0.7f }, 75, &left_idle); //go top
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, 0.09f }, 75, &left_idle); //go bottom
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, -0.7f }, 75, &left_idle); //go top
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, 0.09f }, 75, &left_idle); //go bottom
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, -0.7f }, 75, &left_idle); //go top
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, 0.09f }, 75, &left_idle); //go bottom
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, -0.7f }, 75, &left_idle); //go top
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, 0.09f }, 75, &left_idle); //go bottom
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, -0.7f }, 75, &left_idle); //go top
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, 0.09f }, 75, &left_idle); //go bottom
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, -0.7f }, 75, &left_idle); //go top
			path.PushBack({ 0.0f, -0.3f }, 200, &left_idle); //hold position
			path.PushBack({ 0.0f, 0.09f }, 75, &left_idle); //go bottom
		}
	}

	if (id == 2)
	{
		//right Pushbacks
		{
			right_closed.PushBack({ 9, 292, 58, 53 });
			right_closed.PushBack({ 79, 292, 58, 53 });
			right_closed.PushBack({ 149, 292, 58, 53 });
			right_closed.PushBack({ 219, 292, 58, 53 });
			right_closed.speed = 0.2f;
			right_closed.loop = true;

			right_opening.PushBack({ 1, 349, 59, 53 });
			right_opening.PushBack({ 78, 349, 59, 53 });
			right_opening.PushBack({ 146, 349, 61, 54 });
			right_opening.PushBack({ 216, 349, 61, 54 });
			right_opening.PushBack({ 281, 349, 66, 55 });
			right_opening.PushBack({ 350, 349, 67, 55 });
			right_opening.speed = 0.2f;
			right_opening.loop = false;

			right_idle.PushBack({ 0, 406, 67, 55 });
			right_idle.PushBack({ 70, 406, 67, 55 });
			right_idle.PushBack({ 141, 406, 67, 55 });
			right_idle.PushBack({ 210, 406, 67, 55 });
			right_idle.speed = 0.2f;
			right_idle.loop = true;
		}

		//path
		{
			//Set path
			path.PushBack({ 0.0f, 0.09f }, 670, &right_closed); //wait
			path.PushBack({ 0.0f, -0.9f }, 300, &right_closed); //go to the top
			path.PushBack({ 0.0f, -0.3f }, 475, &right_closed); //hold position
			path.PushBack({ 0.0f, 0.18f }, 140, &right_closed); //extend
			path.PushBack({ 0.0f, -0.3f }, 40, &right_opening); //opening
			path.PushBack({ 0.0f, -0.7f }, 55, &right_idle); //go top
			path.PushBack({ 0.0f, -0.3f }, 200, &right_idle); //hold position
			path.PushBack({ 0.0f, 0.09f }, 75, &right_idle); //go bottom
			path.PushBack({ 0.0f, -0.3f }, 200, &right_idle); //hold position
			path.PushBack({ 0.0f, -0.7f }, 75, &right_idle); //go top
		}
	}



	//Set lives, initial_hp, points adn extra_anim
	lives = 1;
	initial_hp = lives;
	extra_anim = false;
	lower_level = false;
	collider = App->collision->AddCollider({ x, y, 0, 0 }, COLLIDER_NONE, (Module*)App->enemies);
}

Enemy_Antiaircraft::~Enemy_Antiaircraft()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Antiaircraft::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);

}