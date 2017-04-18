#ifndef __HUMANOIDE_ROBOT_H__
#define __HUMANOIDE_ROBOT_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_Humanoide_Robot : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	Path path;
	iPoint original_pos;
	float vector;

	Uint32 start_time = 0;
	Uint32 total_time = (Uint32)(2.0f * 0.5f * 1000.0f);
	Uint32 now;

	Particle* shots[2];

	Animation anim;

public:

	Enemy_Humanoide_Robot(int x, int y);
	~Enemy_Humanoide_Robot();

	void Move();
};
#endif