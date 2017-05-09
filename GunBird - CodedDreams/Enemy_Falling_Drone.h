#ifndef __FALLING_DRONE_H__
#define __FALLING_DRONE_H__

#include "Enemy.h"
#include "Path.h"

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
	Animation move_right;
	Animation right_idle;
	Animation move_left;
	Animation left_idle;
	Animation dead;

};

#endif // !__FALLING_DRONE_H__