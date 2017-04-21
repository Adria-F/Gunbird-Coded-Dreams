#ifndef __HUMANOIDE_ROBOT_H__
#define __HUMANOIDE_ROBOT_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_Humanoide_Robot : public Enemy
{
private:
	
	bool second_shot = false;

	Path path;
	iPoint original_pos;

	Uint32 move_start_time = 0;
	Uint32 move_total_time = (Uint32)(2.0f * 0.5f * 2800.0f);
	Uint32 move_now;

	Uint32 start_time = 0;
	Uint32 total_time = (Uint32)(2.0f * 0.5f * 2800.0f);
	Uint32 now;

	Animation anim;

public:

	Enemy_Humanoide_Robot(int x, int y);
	~Enemy_Humanoide_Robot();

	void Move();
};
#endif