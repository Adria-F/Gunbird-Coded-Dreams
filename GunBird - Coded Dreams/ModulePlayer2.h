#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation left;
	Animation right;
	iPoint position;
	Collider* Pcollider;
	int bullet_counter;
	bool shot;

	bool going_ASH_up;
	bool going_ASH_left;
	bool going_ASH_down;
	bool going_ASH_right;

private:

	Uint32 start_time = 0;
	Uint32 total_time = (Uint32)(2.0f * 0.5f * 100.0f);
	Uint32 now;

	bool drop = true;
	Uint32 drop_timer_start = 0;
	Uint32 drop_timer_total = (Uint32)(2.0f * 0.5f * 1000.0f);
	Uint32 drop_timer_now;
};

#endif