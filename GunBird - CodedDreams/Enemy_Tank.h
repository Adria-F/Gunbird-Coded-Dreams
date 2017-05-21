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
	void ExtraAnim(SDL_Texture* texture);

public:

	Path path;
	Animation idle_motor;
	Animation open_tur;
	Animation open_cent;
	Animation idle;
	Animation close_tur; 
	Animation close_cent;
	Animation dead;

	char* shot_path;
	particle_type shoot;
	Particle* big_shoot;
};

#endif // !__TANK_H__
