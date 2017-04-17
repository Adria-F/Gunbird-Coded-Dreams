#ifndef __HUMANOIDE_ROBOT_H__
#define __HUMANOIDE_ROBOT_H__

#include "Enemy.h"

class Enemy_Humanoide_Robot : public Enemy
{
private:

	Animation anim;

public:

	Enemy_Humanoide_Robot(int x, int y);

	void Move();
};
#endif 