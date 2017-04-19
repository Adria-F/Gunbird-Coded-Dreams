#ifndef __TORPEDO_H__
#define __TORPEDO_H__

#include "Enemy.h"

class Enemy_Torpedo : public Enemy
{
private:

	Animation anim;

public:

	Enemy_Torpedo(int x, int y);

	void Move();
};

#endif // !__ANTIAIRCRAFT_H__
