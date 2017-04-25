#ifndef __HUMANOIDE_ROBOT_H__
#define __HUMANOIDE_ROBOT_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

class Enemy_Humanoide_Robot : public Enemy
{
private:

	bool second_shot = false;
	bool step = false;
	bool killed = 0;
	fPoint vector;
	int distance[2];
	fPoint cannon_pos[2];
	int angle;

	Path path;
	iPoint original_pos;

	Uint32 move_start_time = 0;
	Uint32 move_total_time = (Uint32)(2.0f * 0.5f * 5000.0f);
	Uint32 move_now;

	Uint32 start_time = 0;
	Uint32 total_time = (Uint32)(2.0f * 0.5f * 2800.0f);
	Uint32 now;

	Animation anim_leftBack;
	Animation leftLeg;
	Animation anim_rightBack;
	Animation rightLeg;
	Animation sprint;
	Animation dead_robot;
	ModulePlayer* player;

	SDL_Rect angles[16];

public:

	Enemy_Humanoide_Robot(int x, int y);
	~Enemy_Humanoide_Robot();

	void Move();
	void ExtraAnim(SDL_Texture* texture);
	virtual void DeadAnim();
};
#endif