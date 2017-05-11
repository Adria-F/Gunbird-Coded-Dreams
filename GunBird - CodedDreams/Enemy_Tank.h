#ifndef __TANK_H__
#define __TANK_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Tank : public Enemy
{
public:

	Enemy_Tank(int x, int y, int wave);
	~Enemy_Tank();

	void Move();
	void DeadAnim();
	void ExtraAnim(SDL_Texture* texture);

public:

	Path path;
	Animation open;
	Animation shooting;
	Animation dead;

};

#endif // !__TANK_H__
