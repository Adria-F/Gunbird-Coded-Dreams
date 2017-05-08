#ifndef __ENEMY_MINERS_H__
#define __ENEMY_MINERS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Miners : public Enemy
{
public:

	Enemy_Miners(int x, int y, int wave, int id);
	~Enemy_Miners();

	void Move();

public:

	Path path;
	Animation left;
	Animation right;
	Animation look;

};

#endif // !__FLYING_MACHINE_H__


