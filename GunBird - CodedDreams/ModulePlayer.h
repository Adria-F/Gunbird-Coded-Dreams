#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "ModuleCharacter.h"
#include "ModuleCollision.h"

class Player : public Module
{
public:

	Player(int num);
	~Player();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);
	void setCharacter(ModuleCharacter* character);

public:

	ModuleCharacter* character = nullptr;
	COLLIDER_TYPE collider_type;
	
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
	int bombs = 2;
	int shooting_count;

	Uint32 hit_timer_start = 0;
	Uint32 hit_timer_total = (Uint32)(2.0f * 0.5f * 100.0f);
	Uint32 hit_timer_now;

	//Time between drops/collision animation
	bool drop = true;
	Uint32 drop_timer_start = 0;
	Uint32 drop_timer_total = (Uint32)(2.0f * 0.5f * 750.0f);
	Uint32 drop_timer_now;

	//Time of the bomb attack
	bool bomb_attacking;
	int bomb_count;
	Particle* ash_bomb = nullptr;
	iPoint bomb_pos;
	Uint32 bomb_timer_start = 0;
	Uint32 bomb_timer_total = (Uint32)(2.0f * 0.5f * 150.0f);
	Uint32 bomb_timer_now;

protected:

	//Time between bullets
	Uint32 start_time = 0;
	Uint32 total_time = (Uint32)(2.0f * 0.5f * 100.0f);
	Uint32 now;

	//Duration of hit animation
	Uint32 onhit_start_time = 0;
	Uint32 onhit_total_time = (Uint32)(2.0f * 0.5f * 2000.0f);
	Uint32 onhit_now;
};

#endif // !__MODULE_PLAYER_H__
