#ifndef __ANTIAIRCRAFT_H__
#define __ANITAIRCRAFT_H__

#include "Enemy.h"
#include "ModulePlayer.h"


class Enemy_Antiaircraft : public Enemy
{
private:

	int shot_sequ = 0;
	Animation anim;
	Animation open_anim;
	fPoint vector;
	int distance[2];
	ModulePlayer* player;

	Uint32 start_time = 0;
	Uint32 total_time = (Uint32)(2.0f * 0.5f * 100.0f);
	Uint32 now;

	Uint32 reload_start_time = 0;
	Uint32 reload_total_time = (Uint32)(2.0f * 0.5f * 2000.0f);
	Uint32 reload_now;
	bool reload = false;


public:

	Enemy_Antiaircraft(int x, int y);

	void Move();
	void ExtraAnim(SDL_Texture* texture);
};

#endif // !__ANTIAIRCRAFT_H__
