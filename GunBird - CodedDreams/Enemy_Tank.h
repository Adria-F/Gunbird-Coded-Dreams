#ifndef __TANK_H__
#define __TANK_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_Tank : public Enemy
{
public:

	Enemy_Tank(int x, int y, int wave);
	~Enemy_Tank();

	void Move();
	void DeadAnim();

public:

	Path path;
	Animation idle_motor;
	Animation open_tur;
	Animation open_cent;
	Animation idle;
	Animation close_tur; 
	Animation close_cent;
	Animation dead;
	Uint32 Shot2_now;
	Uint32 Shot2_start_time;
	char* shot_path;
	particle_type shoot;
	Particle* big_shoot;
};

#endif // !__TANK_H__
