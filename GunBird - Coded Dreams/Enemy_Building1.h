#ifndef __BUILDING1_H__
#define __BUILDING1_H__

#include "Enemy.h"

class Enemy_Building1 : public Enemy
{
private:

	Animation anim;

public:

	Enemy_Building1(int x, int y);

	void Move();
};

#endif // !__BUILDING1_H__
