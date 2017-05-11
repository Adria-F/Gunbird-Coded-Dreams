#include "Enemy_Trump.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleRender.h"

Enemy_Trump::Enemy_Trump(int x, int y, int wave, int id) : Enemy(x, y)
{
	//Open all textures
	NormalSprite = App->textures->Load("assets/maps/Trump.png");
	RedSprite = nullptr;
	WhiteSprite = nullptr;
	//delete animations
	anim.PushBack({ 0, 0, 0, 0 });
	anim.speed = 0.01f;
	anim.loop = false;
	//confused pilot
	//right
	anim_pilot_confused.PushBack({ 0, 145, 16, 24 });
	anim_pilot_confused.PushBack({ 21, 145, 13, 25 });
	anim_pilot_confused.PushBack({ 39, 145, 15, 25 });
	anim_pilot_confused.PushBack({ 58, 145, 12, 24 });

	//down
	anim_pilot_confused.PushBack({ 0, 0, 15, 24 });
	anim_pilot_confused.PushBack({ 20, 0, 15, 25 });
	anim_pilot_confused.PushBack({ 40, 0, 15, 24 });
	anim_pilot_confused.PushBack({ 60, 0, 15, 25 });

	//left
	anim_pilot_confused.PushBack({ 0, 175, 12, 24 });
	anim_pilot_confused.PushBack({ 17, 175, 15, 24 });
	anim_pilot_confused.PushBack({ 36, 175, 15, 24 });
	anim_pilot_confused.PushBack({ 54, 175, 15, 24 });

	//down
	anim_pilot_confused.PushBack({ 0, 0, 15, 24 });
	anim_pilot_confused.PushBack({ 20, 0, 15, 25 });
	anim_pilot_confused.PushBack({ 40, 0, 15, 24 });
	anim_pilot_confused.PushBack({ 60, 0, 15, 25 });

	anim_pilot_confused.speed = 0.2f;
	anim_pilot_confused.loop = true;

	//left pilot
	anim_pilot_left.PushBack({ 0, 86, 12, 23 });
	anim_pilot_left.PushBack({ 17, 86, 11, 24 });
	anim_pilot_left.PushBack({ 33, 86, 12, 23 });
	anim_pilot_left.PushBack({ 50, 86, 11, 24 });
	anim_pilot_left.speed = 0.2f;
	anim_pilot_left.loop = true;
	
	
	//right pilot
	anim_pilot_right.PushBack({ 0, 58, 12, 23 });
	anim_pilot_right.PushBack({ 17, 58, 11, 24 });
	anim_pilot_right.PushBack({ 33, 58, 12, 23 });
	anim_pilot_right.PushBack({ 50, 58, 11, 24 });
	anim_pilot_right.speed = 0.2f;
	anim_pilot_right.loop = true;

	//idle pilot
	anim_pilot_idle.PushBack({ 0, 114, 15, 26 });
	anim_pilot_idle.PushBack({ 20, 113, 15, 25 });
	anim_pilot_idle.speed = 0.1f;
	anim_pilot_idle.loop = true;

	//turning pilot to the right
	anim_pilot_turning.PushBack({ 40, 114, 12, 24 });
	anim_pilot_turning.speed = 0.1f;
	anim_pilot_turning.loop = true;

	//up pilot
	anim_pilot_up.PushBack({ 0, 29, 14, 24 });
	anim_pilot_up.PushBack({ 19, 29, 15, 25 });
	anim_pilot_up.PushBack({ 39, 29, 14, 24 });
	anim_pilot_up.PushBack({ 58, 29, 15, 25 });
	anim_pilot_up.speed = 0.2f;
	anim_pilot_up.loop = true;
	
	/*---------------------------------------------------*/
	//confused boy
	anim_boy_confused.PushBack({ 121, 139, 14, 25 });
	anim_boy_confused.PushBack({ 140, 139, 14, 24 });
	anim_boy_confused.PushBack({ 121, 139, 14, 25 }); 
	anim_boy_confused.PushBack({ 140, 139, 14, 24 });

	anim_boy_confused.PushBack({ 85, 0, 15, 23 }); 
	anim_boy_confused.PushBack({ 105, 0, 15, 24 });
	anim_boy_confused.PushBack({ 125, 0, 15, 23 });
	anim_boy_confused.PushBack({ 145, 0, 15, 25 });

	anim_boy_confused.PushBack({ 102, 139, 14, 25 }); 
	anim_boy_confused.PushBack({ 85, 139, 12, 24 });
	anim_boy_confused.PushBack({ 102, 139, 14, 25 }); 
	anim_boy_confused.PushBack({ 85, 139, 12, 24 });

	anim_boy_confused.PushBack({ 85, 0, 15, 23 }); 
	anim_boy_confused.PushBack({ 105, 0, 15, 24 });
	anim_boy_confused.PushBack({ 125, 0, 15, 23 });
	anim_boy_confused.PushBack({ 145, 0, 15, 25 });

	anim_boy_confused.speed = 0.2f;
	anim_boy_confused.loop = true;

	//right boy
	anim_boy_right.PushBack({ 85, 83, 11, 22 });
	anim_boy_right.PushBack({ 102, 83, 12, 21 }); 
	anim_boy_right.PushBack({ 118, 83, 11, 22 }); 
	anim_boy_right.PushBack({ 134, 83, 11, 21 }); 
	anim_boy_right.speed = 0.2f;
	anim_boy_right.loop = true;

	//left boy
	anim_boy_left.PushBack({ 85, 56, 11, 21 });
	anim_boy_left.PushBack({ 101, 56, 11, 21 });
	anim_boy_left.PushBack({ 117, 56, 12, 21 });
	anim_boy_left.PushBack({ 134, 56, 11, 22 });
	anim_boy_left.speed = 0.2f;
	anim_boy_left.loop = true;

	//idle boy
	anim_boy_idle.PushBack({ 103, 109, 12, 23 });
	anim_boy_idle.PushBack({ 85, 110, 12, 23 });
	anim_boy_idle.speed = 0.1f;
	anim_boy_idle.loop = true;

	//turning boy
	anim_boy_turning.PushBack({ 85, 139, 11, 23 });
	anim_boy_turning.PushBack({ 134, 83, 10, 20 });
	anim_boy_turning.speed = 0.1f;
	anim_boy_turning.loop = true;
	//up boy
	anim_boy_up.PushBack({ 85, 28, 14, 22 });
	anim_boy_up.PushBack({ 105, 28, 13, 21 });
	anim_boy_up.PushBack({ 124, 28, 14, 22 });
	anim_boy_up.PushBack({ 144, 28, 13, 21 });
	anim_boy_up.speed = 0.2f;

	/*---------------------------------------------------*/

	//idle girl
	anim_girl_idle.PushBack({ 189, 165, 13, 23 });
	anim_girl_idle.PushBack({ 170, 166, 13, 23 });
	anim_girl_idle.speed = 0.1f;
	anim_girl_idle.loop = true;

	//turning girl
	anim_girl_turning.PushBack({ 170, 110, 11, 22 });
	anim_girl_turning.PushBack({ 185, 82, 10, 21 });
	anim_girl_turning.speed = 0.1f;
	anim_girl_turning.loop = true;

	//up girl
	anim_girl_up.PushBack({ 170, 27, 12, 21 });
	anim_girl_up.PushBack({ 188, 27, 14, 22 });
	anim_girl_up.PushBack({ 208, 27, 14, 22 });
	anim_girl_up.PushBack({ 228, 27, 13, 21 });
	anim_girl_up.speed = 0.2f;
	anim_girl_up.loop = true;

	//Set path

	//pilot
	if (wave == 1 && id == 1)
	{
		path.PushBack({ 0.0f, 0.09f }, 400, &anim_pilot_confused);
		path.PushBack({ -0.40f, 0.09f }, 500, &anim_pilot_left);

	}
	if (wave == 2 && id == 1)
	{
		path.PushBack({ 0.40f, 0.09f }, 305, &anim_pilot_right);
		path.PushBack({ 0.0f, 0.09f }, 180, &anim_pilot_idle);
		path.PushBack({ 0.40f, 0.09f }, 45, &anim_pilot_right);
		path.PushBack({ 0.00f, -0.31f }, 150, &anim_pilot_up);
		path.PushBack({ 0.0f, 0.09f }, 1000, &anim);
	}
	//boy
	if (wave == 1 && id == 2)
	{
		path.PushBack({ 0.0f, 0.09f }, 450, &anim_boy_confused);
		path.PushBack({ 0.40f, 0.09f }, 1000, &anim_boy_right);
	}
	if (wave == 2 && id == 2)
	{
		path.PushBack({ -0.40f, 0.09f }, 310, &anim_boy_left);
		path.PushBack({ 0.0f, 0.09f }, 150, &anim_boy_idle);
		path.PushBack({ -0.40f, 0.09f }, 40, &anim_boy_left);
		path.PushBack({ 0.00f, -0.31f }, 150, &anim_boy_up);
		path.PushBack({ 0.0f, 0.09f }, 1000, &anim);
	}

	//girl
	if (wave == 1 && id == 3)
	{
		path.PushBack({ 0.0f, 0.09f }, 450, &anim_girl_idle);
		path.PushBack({ 0.0f, 0.09f }, 15, &anim_girl_turning);
		path.PushBack({ 0.0f, -0.31f }, 172, &anim_girl_up);
		path.PushBack({ 0.0f, 0.09f }, 1000, &anim);

	}
	//set live;
	lives = 1;
	extra_anim = false;

}

Enemy_Trump::~Enemy_Trump()
{
	App->textures->Unload(NormalSprite);
}

void Enemy_Trump::Move()
{
	
	//if (App->render->camera.y <= -2293)
	position = original_pos + path.GetCurrentPosition(&animation);
}
