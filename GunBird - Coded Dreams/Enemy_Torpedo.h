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
	float modul;
	fPoint vector;
	fPoint speed;
	int distance[2];

public:

	Enemy_Torpedo(int x, int y, int wave, int id);
	~Enemy_Torpedo();

	void Move();
};

#endif // !__ANTIAIRCRAFT_H__
