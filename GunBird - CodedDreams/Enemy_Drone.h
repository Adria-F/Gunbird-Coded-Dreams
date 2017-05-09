#ifndef __DRONE_H__
#define __DRONE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Drone : public Enemy
{
public:

	Enemy_Drone(int x, int y, int wave, int id);
	~Enemy_Drone();

	void Move();

public:

	Path path;
	Animation dronewave;
	Animation dead;

};

#endif // !__DRONE_H__

