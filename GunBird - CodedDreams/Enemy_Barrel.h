#ifndef __BARREL_H__
#define __BARREL_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Barrel : public Enemy
{
public:

	Enemy_Barrel(int x, int y);
	~Enemy_Barrel();

	void Move();
	void DeadAnim();

public:

	Path path;
	Animation idle;
	Animation dead;

};

#endif // !__BARREL_H__
