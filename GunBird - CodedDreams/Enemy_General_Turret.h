#ifndef __GENERAL_TURRET_H__
#define __GENERAL_TURRET_H__

#include "Enemy.h"
#include "Path.h"
#include "p2Point.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

class Enemy_General_Turret : public Enemy
{
public:

	Enemy_General_Turret(int x, int y, int wave, int id);
	~Enemy_General_Turret();

	void Move();
	void DeadAnim();
	void ExtraAnim(SDL_Texture* texture);
	void Drop();

public:

	Path path;
	Animation idle;
	Animation dead;
	Animation appear_anim;
	SDL_Rect gate;

private:

	fPoint vector;
	int distance[2];
	int angle;
	Player* player;
	SDL_Rect angles[32];
	bool appearing = false;
	bool gate_opened = false;
	fPoint gate_pos;

	Uint32 appear_now;
	Uint32 appear_Start_time;
	Uint32 appear_Total_time = (Uint32)(6000.0f);

};

#endif // !__BALLOON_H__