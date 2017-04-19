#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation left;
	Animation right;
	Animation stele1;
	Animation stele2;
	Animation stele3;
	iPoint position;
	Collider* Pcollider;
	int bullet_counter;
	bool shot;

	bool going_MARION_up;
	bool going_MARION_left;
	bool going_MARION_down;
	bool going_MARION_right;

private:

	Uint32 start_time = 0;
	Uint32 total_time = (Uint32)(2.0f * 0.5f * 1000.0f);
	Uint32 now;

	bool drop = true;
	Uint32 drop_timer_start = 0;
	Uint32 drop_timer_total = (Uint32)(2.0f * 0.5f * 300.0f);
	Uint32 drop_timer_now;
};

#endif