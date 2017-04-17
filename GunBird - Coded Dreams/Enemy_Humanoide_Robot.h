#ifndef __HUMANOIDE_ROBOT_H__
#define __HUMANOIDE_ROBOT_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Enemy_Humanoide_Robot : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	Path path;
	iPoint original_pos;

	Animation anim;

public:

	Enemy_Humanoide_Robot(int x, int y);

	void Move();
};
#endif