#ifndef __ENEMY_MINERS_H__
#define __ENEMY_MINERS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Trump : public Enemy
{
public:

	Enemy_Trump(int x, int y, int wave, int id);
	~Enemy_Trump();

	void Move();

public:

	Path path;
	Animation anim;


};

#endif // !__FLYING_MACHINE_H__
