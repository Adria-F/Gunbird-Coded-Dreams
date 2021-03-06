#ifndef __FLYING_MACHINE_H__
#define __FLYING_MACHINE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Flying_Machine : public Enemy
{
public:

	Enemy_Flying_Machine(int x, int y);
	~Enemy_Flying_Machine();

	void Move();
	void Drop();
	
public:

	Path path;
	Animation idle_low;
	Animation idle_grow;
	Animation idle_grow_gun;
	Animation idle_up;
	Animation dead;
	int state = 0;
};

#endif // !__FLYING_MACHINE_H__
