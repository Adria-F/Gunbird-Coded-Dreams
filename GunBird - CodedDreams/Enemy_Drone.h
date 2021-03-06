#ifndef __DRONE_H__
#define __DRONE_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_Drone : public Enemy
{
public:

	Enemy_Drone(int x, int y, int wave, int id);
	~Enemy_Drone();

	void Move();

public:

	Path path;
	Animation Looking_down;
	Animation Looking_right;
	Animation Totally_right;
	Animation Looking_left;
	Animation Totally_left;
	Animation dead;


	char* shot_path;
	particle_type shoot;
	Particle* big_shoot;
	

};

#endif // !__DRONE_H__

