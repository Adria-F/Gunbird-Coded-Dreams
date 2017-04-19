#ifndef __TORPEDO_H__
#define __TORPEDO_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_Torpedo : public Enemy
{
private:

	Path path;
	iPoint original_pos;
	Animation anim;

public:

	Enemy_Torpedo(int x, int y);

	void Move();
};

#endif // !__ANTIAIRCRAFT_H__
