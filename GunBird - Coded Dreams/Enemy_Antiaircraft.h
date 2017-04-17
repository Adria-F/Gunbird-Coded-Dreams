#ifndef __ANTIAIRCRAFT_H__
#define __ANITAIRCRAFT_H__

#include "Enemy.h"

class Enemy_Antiaircraft : public Enemy
{
private:

	Animation anim;

public:

	Enemy_Antiaircraft(int x, int y);

	void Move();
};

#endif // !__ANTIAIRCRAFT_H__
