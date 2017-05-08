#ifndef __ENEMY_MINERS_H__
#define __ENEMY_MINERS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Trump : public Enemy
{
public:

	Enemy_Trump(int x, int y, int wave, int id);
	~Enemy_Trump();

	void Move();

public:

	Path path;
	Animation anim;
	//pilot
	Animation anim_pilot_confused;
	Animation anim_pilot_left;
	Animation anim_pilot_right;
	Animation anim_pilot_idle;
	Animation anim_pilot_turning;
	Animation anim_pilot_up;

	//punk
	Animation anim_boy_confused;
	Animation anim_boy_left;
	Animation anim_boy_right;
	Animation anim_boy_idle;
	Animation anim_boy_turning;
	Animation anim_boy_up;

	//girl
	Animation anim_girl_idle;
	Animation anim_girl_turning;
	Animation anim_girl_up;


};

#endif // !__FLYING_MACHINE_H__
