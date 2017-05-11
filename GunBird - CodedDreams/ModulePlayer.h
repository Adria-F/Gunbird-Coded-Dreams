#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "ModuleCharacter.h"

class Player : public Module
{
public:

	Player();
	~Player();

	bool Start();
	update_status Update();
	bool CleanUp();

	void setCharacter(ModuleCharacter* character);

public:

	ModuleCharacter* character = nullptr;
	
	iPoint position;

	Collider* Pcollider;
	int bullet_counter;
	bool shot;

	bool going_up;
	bool going_left;
	bool going_down;
	bool going_right;
	bool going_onhit = false; //named: hit
	bool going_onhit_check = false; //?
	bool dead;

	uint points = 0;
	int shot_lvl = 1;
	int lives = 3;

	Uint32 hit_timer_start = 0;
	Uint32 hit_timer_total = (Uint32)(2.0f * 0.5f * 100.0f);
	Uint32 hit_timer_now;

protected:

	//Time between bullets
	Uint32 start_time = 0;
	Uint32 total_time = (Uint32)(2.0f * 0.5f * 100.0f);
	Uint32 now;

	//Time between drops/collision animation
	bool drop = true;
	Uint32 drop_timer_start = 0;
	Uint32 drop_timer_total = (Uint32)(2.0f * 0.5f * 1000.0f);
	Uint32 drop_timer_now;

	//Duration of hit animation
	Uint32 onhit_start_time = 0;
	Uint32 onhit_total_time = (Uint32)(2.0f * 0.5f * 2000.0f);
	Uint32 onhit_now;
};

#endif // !__MODULE_PLAYER_H__
