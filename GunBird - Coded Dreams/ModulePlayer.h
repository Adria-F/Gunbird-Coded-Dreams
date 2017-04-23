#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:

	virtual bool Start() = 0;
	virtual update_status Update() = 0;
	virtual bool CleanUp() = 0;

	virtual void OnCollision(Collider* c1, Collider* c2) = 0;

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation left;
	Animation right;
	iPoint position;

	Collider* Pcollider;
	int bullet_counter;
	bool shot;

	bool going_up;
	bool going_left;
	bool going_down;
	bool going_right;

protected:

	Uint32 start_time = 0;
	Uint32 total_time = (Uint32)(2.0f * 0.5f * 100.0f);
	Uint32 now;

	bool drop = true;
	Uint32 drop_timer_start = 0;
	Uint32 drop_timer_total = (Uint32)(2.0f * 0.5f * 1000.0f);
	Uint32 drop_timer_now;
};

#endif // !__MODULE_PLAYER_H__
