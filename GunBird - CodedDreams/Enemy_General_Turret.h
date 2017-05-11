#ifndef __GENERAL_TURRET_H__
#define __GENERAL_TURRET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_General_Turret : public Enemy
{
public:

	Enemy_General_Turret(int x, int y);
	~Enemy_General_Turret();

	void Move();
	void DeadAnim();

public:

	Path path;
	Animation idle;
	Animation dead;

};

#endif // !__BALLOON_H__