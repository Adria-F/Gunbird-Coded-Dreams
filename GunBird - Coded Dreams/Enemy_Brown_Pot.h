#ifndef __ENEMY_BROWN_POT_H__
#define __ENEMY_BROWN_POT_H__

#include "Enemy.h"

class Enemy_Brown_Pot : public Enemy
{
private:

	Animation anim;
	Animation dead_pot;

	

public:

	Enemy_Brown_Pot(int x, int y);
	~Enemy_Brown_Pot();
	
};

#endif // !__POT_H__
