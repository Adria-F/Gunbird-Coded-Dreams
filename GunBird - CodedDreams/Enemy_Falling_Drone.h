#ifndef __FALLING_DRONE_H__
#define __FALLING_DRONE_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_Faling_Drone : public Enemy
{
public:

	Enemy_Faling_Drone(int x, int y, int wave, int id);
	~Enemy_Faling_Drone();

	void Move();
	void ExtraAnim(SDL_Texture* texture);
	void DeadAnim();

public:

	Path path;
	Animation idle;
	Animation rotate_right;
	Animation going_right;
	Animation center_from_right;
	Animation rotate_left;
	Animation going_left;
	Animation center_from_left;
	Animation dead;

	char* shot_path;
	particle_type shoot;
	Particle* big_shoot;

};

#endif // !__FALLING_DRONE_H__