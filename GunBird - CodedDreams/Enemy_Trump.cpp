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

	//confused pilot
	//down
	anim_pilot_confused.PushBack({ 0, 0, 15, 24 });
	anim_pilot_confused.PushBack({ 0, 20, 15, 25 });
	anim_pilot_confused.PushBack({ 0, 40, 15, 24 });
	anim_pilot_confused.PushBack({ 0, 60, 15, 25 });

	anim_pilot_confused.PushBack({ 0, 145, 16, 24 });
	anim_pilot_confused.PushBack({ 21, 145, 13, 25 });
	anim_pilot_confused.PushBack({ 39, 145, 15, 25 });
	anim_pilot_confused.PushBack({ 58, 145, 12, 24 });

	anim_pilot_confused.PushBack({ 0, 0, 12, 24 });
	anim_pilot_confused.PushBack({ 0, 0, 15, 24 });
	anim_pilot_confused.PushBack({ 0, 0, 15, 24 });
	anim_pilot_confused.PushBack({ 0, 0, 15, 24 });

	anim_pilot_confused.speed = 0.2f;
	anim_pilot_confused.loop = true;

	//left pilot
	anim_pilot_left.PushBack({ 58, 83, 11, 23 });
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

	//confused boy
	//right boy
	//left boy


	//idle boy
	anim_boy_idle.PushBack({ 103, 109, 12, 23 });
	anim_boy_idle.PushBack({ 85, 110, 12, 23 });
	anim_boy_idle.speed = 0.1f;

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

	//idle girl
	anim_girl_idle.PushBack({ 189, 165, 13 ,23 });
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
	if (wave == 1)
	{
		path.PushBack({ -0.40f, 0.09f }, 50, &anim);
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
	position = original_pos + path.GetCurrentPosition(&animation);
}
